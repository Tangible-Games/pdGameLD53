#!/usr/bin/env python3

import sys
import subprocess
import time
import os
import platform

VID = '1331'
PID_SERIAL = '5740'
PID_DRIVE = '5741'

TTY_BRED = "\x1b[31;1m"
TTY_RESET = "\x1b[0m"

ERROR_STR = TTY_BRED + 'ERROR: ' + TTY_RESET

def cmd_run(cmd, error_msg = None, **kwargs):
    cmd_out = None
    try:
        cmd_out = subprocess.check_output(cmd, **kwargs)
    except subprocess.CalledProcessError as err:
        sys.exit(ERROR_STR + '{} : {}'.format(error_msg, err))
    return cmd_out


def device_pid_linux(timeout):
    lsusb_out = ''
    while True:
        try:
            lsusb_out = subprocess.check_output(['lsusb', '-d 1331:'])
        except subprocess.CalledProcessError as err:
            pass
        if timeout == 0:
            break
        timeout -= 1
        time.sleep(1)

    if lsusb_out == '':
        return None

    vid_str = '1331:'
    lsusb_out = lsusb_out.strip().decode('UTF-8')
    vid_pos = lsusb_out.find(vid_str)
    if vid_pos == -1:
        sys.exit(ERROR_STR + 'Unable to parse VID from lsusb output')
    pid_pos = vid_pos + len(vid_str)
    pid = lsusb_out[pid_pos:pid_pos + 4]
    return pid

def device_pid_mac(timeout):
    usb_out = ''
    while True:
        out = ''
        try:
            out = subprocess.check_output(['ioreg', '-p', 'IOUSB', '-l', '-w0', '-x'])
        except subprocess.CalledProcessError as err:
            pass
        out = out.strip().decode('UTF-8')
        pd_pos = out.find('Playdate@')
        if pd_pos != -1:
            usb_out = out[pd_pos:]
            break
        if timeout == 0:
            break
        timeout -= 1
        time.sleep(1)

    if usb_out == '':
        return None

    product_str = '"idProduct" = 0x'

    id_product_pos = usb_out.find(product_str)
    if id_product_pos == -1:
        sys.exit(ERROR_STR + 'Unable to parse ioreg output')
    pid_pos = id_product_pos + len(product_str)
    pid = usb_out[pid_pos:pid_pos + 4]
    return pid

def device_pid(timeout = 0):
    pid = None
    if platform.system() == 'Linux':
        pid = device_pid_linux(timeout)
    elif platform.system() == 'Darwin':
        pid = device_pid_mac(timeout)
    else:
        sys.exit(ERROR_STR + 'platform `{}` is not supported'.format(platform.system()))

    if pid is None:
        sys.exit(ERROR_STR + 'PlayDate device not found. Check that the device is plugged in and unlocked.')

    return pid

def get_serial_device_path_linux():
    return cmd_run(['find', '/dev/serial/by-id/', '-name', '*Playdate*'],
                   'Unable to find Playdate device in /dev/serial/by-id/')

def get_serial_device_path_mac():
    return cmd_run('ls /dev/cu.*PD*',
                'Unable to find Playdate device in /dev', shell=True)


def get_serial_device_path():
    tty_dev = None
    if platform.system() == 'Linux':
        tty_dev = get_serial_device_path_linux()
    elif platform.system() == 'Darwin':
        tty_dev = get_serial_device_path_mac()

    if tty_dev is None:
        sys.exit(ERROR_STR + 'serial device not found')

    tty_dev = tty_dev.strip().decode('UTF-8')
    print('Found Playdate serial device in', tty_dev)
    return tty_dev

def get_disk_device_path():
    disk_dev = None
    if platform.system() == 'Linux':
        disk_dev = cmd_run(['find', '/dev/disk/by-id/', '-name', '*Playdate*-part1'],
                           'Unable to find Playdate device in /dev/disk/by-id/')

    if disk_dev is None:
        sys.exit(ERROR_STR + 'disk device not found')

    disk_dev = disk_dev.strip().decode('UTF-8')
    print('Found Playdate block device in', disk_dev)
    return disk_dev

def drive_mount_linux():
    # find drive device name
    disk_dev = get_disk_device_path()

    # mount drive
    mount_out = cmd_run(['udisksctl', 'mount', '-b', disk_dev], 'Unable to mount device')
    mount_out = mount_out.strip().decode('UTF-8')

    # find mount point
    mount_pos = mount_out.find('/media/')
    if mount_pos == -1:
        sys.exit(ERROR_STR + 'Unable to parse mount point')

    return mount_out[mount_pos:]

def drive_mount_point_mac():
    mount_point = '/Volumes/PLAYDATE'
    timeout = 30
    while timeout > 0:
        if os.path.exists(mount_point + '/Games'):
            return mount_point
        timeout -= 1
        time.sleep(1)
    sys.exit(ERROR_STR + 'Mount point not found')

def drive_unmount_linux():
    disk_dev = get_disk_device_path()
    try:
        mount_out = subprocess.check_output(['udisksctl', 'unmount', '-b', disk_dev])
    except subprocess.CalledProcessError as err:
        print(ERROR_STR + 'Unable to unmount device:', err)

    # eject
    cmd_run(['eject', disk_dev], 'Unable to eject device')

def drive_unmount_mac():
    cmd_run('diskutil unmount PLAYDATE', shell=True)
    cmd_run('diskutil eject PLAYDATE', shell=True)

def drive_unmount():
    if platform.system() == 'Linux':
        drive_unmount_linux()
    elif platform.system() == 'Darwin':
        drive_unmount_mac()

def install(pd_sdk, game_dir):
    game_name = os.path.basename(game_dir)
    if game_name == '':
        sys.exit(ERROR_STR + 'Unable to find game name')

    pid = device_pid()
    if pid == PID_SERIAL:
        # find serial port device name
        tty_dev = get_serial_device_path()

        # switch to drive mode
        cmd_run([pd_sdk + '/bin/pdutil', tty_dev, 'datadisk'], 'Unable to switch to drive mode')
        time.sleep(2)

        # wait for drive to be ready
        print('Waiting for drive to be ready...')
        pid = device_pid(25)

    if pid != PID_DRIVE:
        sys.exit(ERROR_STR + 'Unable to find PlayDate drive')

    mount_point = None
    if platform.system() == 'Linux':
        mount_point = drive_mount_linux()
    elif platform.system() == 'Darwin':
        mount_point = drive_mount_point_mac()

    print('Mount point:', mount_point)

    # copy files
    try:
        os.system('rm -rf {}'.format(mount_point +  '/Games/' + game_name))
        os.system('cp -r {} {}'.format(game_dir, mount_point + '/Games/'))
    except Exception as err:
        # Don't exit here, try to unmount the drive
        print(ERROR_STR + 'Failed to install files:', err)

    # unmount drive
    drive_unmount()


def run(pd_sdk, game_dir, debug = False, stats = False):
    pid = device_pid()
    if pid != PID_SERIAL:
        sys.exit(ERROR_STR + 'Unable to find Playdate device in serial mode')
    tty_dev = get_serial_device_path()
    game_name = os.path.basename(game_dir)

    dbg = None
    if debug:
        dbg = subprocess.Popen(['cat', tty_dev], stdout=subprocess.PIPE)

    cmd_run([pd_sdk + '/bin/pdutil', tty_dev, 'run', '/Games/' + game_name], 'Failed to run game {}'.format(game_name))

    if dbg:
        try:
            while dbg.poll() is None:
                dbg_out = dbg.stdout.readline()
                print(dbg_out.strip().decode('UTF-8'))
        except KeyboardInterrupt:
            sys.exit()
    if stats:
        try:
            while True:
                mount_out = cmd_run([pd_sdk + '/bin/pdutil', tty_dev, 'stats'], 'Unable to run stats')
                print(mount_out.strip().decode('UTF-8'))
                print('----')
                time.sleep(1)
        except KeyboardInterrupt:
            sys.exit()


def usage():
    print('Usage: {} <install|run|rundbg|runstats> <pd_sdk> <game_dir>'.format(sys.argv[0]))

if __name__ == "__main__":
    if len(sys.argv) == 4:
        if sys.argv[1] == 'install':
            install(sys.argv[2], sys.argv[3])
        elif sys.argv[1] == 'run':
            run(sys.argv[2], sys.argv[3])
        elif sys.argv[1] == 'rundbg':
            run(sys.argv[2], sys.argv[3], True)
        elif sys.argv[1] == 'runstats':
            run(sys.argv[2], sys.argv[3], stats=True)
        else:
            usage()
    else:
        usage()