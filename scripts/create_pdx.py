import sys
import os
import shutil
import tempfile

def touch(path):
    with open(path, 'a'):
        os.utime(path, None)

def copy_dir_content(src, dest):
    for path in os.listdir(src):
        s = os.path.join(src, path)
        d = os.path.join(dest, path)
        if os.path.isfile(s):
            shutil.copy2(s, d)
        else:
            shutil.copytree(s, d)

def create_sim(pd_sdk, bin, dest, resources_dir):
    print("Creating {}...".format(dest))
    try:
        os.rmdir(dest)
    except:
        pass
    with tempfile.TemporaryDirectory() as tmp:
        if os.path.basename(bin) == "pdex.bin":
            shutil.copy(bin, os.path.join(tmp, 'pdex.bin'))
        else:
            ext = os.path.splitext(bin)[1]
            shutil.copy(bin, os.path.join(tmp, 'pdex' + ext))
            touch(os.path.join(tmp, 'pdex.bin'))
            touch(os.path.join(tmp, 'main.pdz'))
        if resources_dir is not None:
            copy_dir_content(resources_dir, tmp) 
        os.system('{} -sdkpath {} {} {}'.format(os.path.join(pd_sdk, 'bin', 'pdc'), pd_sdk, tmp, dest))


if __name__ == "__main__":
    if len(sys.argv) == 4 or len(sys.argv) == 5:
        create_sim(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4] if len(sys.argv) == 5 else None)
    else:
        sys.exit('Usage: {} <pd_sdk> <input_file> <output_dir> [<resources_dir>]'.format(sys.argv[0]))