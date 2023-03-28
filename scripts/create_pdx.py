import sys
import os
import shutil
import tempfile

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
            shutil.copy(bin, os.path.join(tmp, 'pdex.so'))
            os.system('touch {}'.format(os.path.join(tmp, 'pdex.bin')))
        if resources_dir is not None:
            os.system('cp -r {}/* {}/'.format(resources_dir, tmp))
        os.system('{} -sdkpath {} {} {}'.format(os.path.join(pd_sdk, 'bin', 'pdc'), pd_sdk, tmp, dest))


if __name__ == "__main__":
    if len(sys.argv) == 4 or len(sys.argv) == 5:
        create_sim(sys.argv[1], sys.argv[2], sys.argv[3], sys.argv[4] if len(sys.argv) == 5 else None)
    else:
        sys.exit('Usage: {} <pd_sdk> <input_file> <output_dir> [<resources_dir>]'.format(sys.argv[0]))