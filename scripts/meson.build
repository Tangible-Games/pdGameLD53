fs = import('fs')

# Try env first, it not set try default install dir
pd_sdk = run_command('sh', '-c', 'echo $PLAYDATE_SDK_PATH', check: true).stdout().strip()
if pd_sdk == ''
    default_path = fs.expanduser('~/Developer/PlaydateSDK')
    message('Try to use default path: ' + default_path)
    if fs.is_dir(default_path)
        pd_sdk = default_path
    endif
endif

if pd_sdk == ''
    error('PlayDate SDK is not found. Set the pd_sdk option or PLAYDATE_SDK_PATH env variable')
endif

if not fs.is_dir(pd_sdk)
    error('Directory `' + pd_sdk + '` doesn\'t exist')
endif

message('SDK Path: ' + pd_sdk)
pdsdk_inc = include_directories(pd_sdk / 'C_API')

add_project_arguments('-DTARGET_EXTENSION=1', language: ['c', 'cpp'])
add_project_arguments('-DTARGET_EXTENSION=1', language: ['c', 'cpp'], native: true)

# Arguments don't apply properly from project default options
add_project_arguments('-std=c++2a', language: 'cpp', native: true)
add_project_arguments('-std=gnu11', language: 'c', native: true)

# host only
add_project_arguments('-DTARGET_SIMULATOR=1', language: ['c', 'cpp'], native: true)
add_project_arguments('-Wno-unknown-pragmas', language: ['c', 'cpp'], native: true)
add_project_arguments('-Wdouble-promotion', language: ['c', 'cpp'], native: true)
# always debug for the host
add_project_arguments('-O0', language: ['c', 'cpp'], native: true)
add_project_arguments('-ggdb', language: ['c', 'cpp'], native: true)

# cross build
if meson.is_cross_build()
add_project_arguments('-DTARGET_PLAYDATE=1', language: ['c', 'cpp'])
add_project_arguments('-Wno-unknown-pragmas', language: ['c', 'cpp'])
add_project_arguments('-Wdouble-promotion', language: ['c', 'cpp'])
# always optimized
add_project_arguments('-O2', language: ['c', 'cpp'])
add_project_arguments('-gdwarf-2', language: ['c', 'cpp'])
add_project_arguments('-mthumb', language: ['c', 'cpp'])
add_project_arguments('-mcpu=cortex-m7', language: ['c', 'cpp'])
add_project_arguments('-mfloat-abi=hard', language: ['c', 'cpp'])
add_project_arguments('-mfpu=fpv5-sp-d16', language: ['c', 'cpp'])
add_project_arguments('-D__FPU_USED=1', language: ['c', 'cpp'])
add_project_arguments('-falign-functions=16', language: ['c', 'cpp'])
add_project_arguments('-fomit-frame-pointer', language: ['c', 'cpp'])
add_project_arguments('-fverbose-asm', language: ['c', 'cpp'])
add_project_arguments('-ffunction-sections', language: ['c', 'cpp'])
add_project_arguments('-fdata-sections', language: ['c', 'cpp'])
add_project_arguments('-fno-exceptions', language: ['cpp'])
add_project_arguments('-fno-rtti', language: ['cpp'])
add_project_arguments('-fno-use-cxa-atexit', language: ['cpp'])
add_project_arguments('-fno-threadsafe-statics', language: ['cpp'])
add_project_arguments('-fms-extensions', language: ['cpp'])

pdsdk_link_args = [
    '-T@0@'.format(meson.current_source_dir() / 'link_map.ld'),
    '-Wl,-Map=game.map,--cref,--gc-sections,--no-warn-mismatch',
    '-mthumb', '-mcpu=cortex-m7', '-mfloat-abi=hard', '-mfpu=fpv5-sp-d16',
    '--specs=nosys.specs'
]

# Glue code
exe_srcs_cross += files([pd_sdk / 'C_API' / 'buildsupport' / 'setup.c'])
endif

pdsdk_dep = declare_dependency(include_directories: pdsdk_inc)

# gtest enable
gtest = subproject('gtest')
gtest_dep = gtest.get_variable('gtest_main_dep')
