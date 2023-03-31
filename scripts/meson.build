fs = import('fs')

if not meson.is_cross_build()
    error('Should be configured for cross build')
endif

pd_sdk = get_option('pd_sdk')
if pd_sdk == ''
    pd_sdk = run_command('sh', '-c', 'echo $PLAYDATE_SDK_PATH', check: true).stdout().strip()
endif

if pd_sdk == ''
    error('Set the pd_sdk option or PLAYDATE_SDK_PATH env variable')
endif

if not fs.is_dir(pd_sdk)
    error('Directory `' + pd_sdk + '` doesn\'t exist')
endif

message('SDK Path: ' + pd_sdk)
pdsdk_inc = include_directories(pd_sdk / 'C_API')

add_project_arguments('-DTARGET_EXTENSION=1', language: ['c', 'cpp'])
add_project_arguments('-DTARGET_EXTENSION=1', language: ['c', 'cpp'], native: true)

# Arguments don't apply properly from project default options
add_project_arguments('-std=c++17', language: 'cpp', native: true)
add_project_arguments('-std=gnu11', language: 'c', native: true)

# host only
add_project_arguments('-DTARGET_SIMULATOR=1', language: ['c', 'cpp'], native: true)
add_project_arguments('-Wno-unknown-pragmas', language: ['c', 'cpp'], native: true)
add_project_arguments('-Wdouble-promotion', language: ['c', 'cpp'], native: true)
# always debug for the host
add_project_arguments('-O0', language: ['c', 'cpp'], native: true)
add_project_arguments('-ggdb', language: ['c', 'cpp'], native: true)

# cross build
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
    '-mthumb', '-mcpu=cortex-m7', '-mfloat-abi=hard', '-mfpu=fpv5-sp-d16'
]

# Glue code
exe_srcs_cross += files([pd_sdk / 'C_API' / 'buildsupport' / 'setup.c'])

pdsdk_dep_cross = declare_dependency(include_directories: pdsdk_inc)
pdsdk_dep_host = declare_dependency(include_directories: pdsdk_inc)
