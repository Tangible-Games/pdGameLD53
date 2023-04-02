project('pdGameLD53',
    'c', 'cpp',
    version: '0.1',
    meson_version : '>= 0.60',
    default_options : [
        'warning_level=3',
        'c_std=gnu11', 'cpp_std=c++2a',
        'build.c_std=c11', 'build.cpp_std=c++2a',
        'werror=true',
        'default_library=static',
        'buildtype=custom',
        'debug=false',
        'optimization=plain'
    ]
)

exe_srcs_cross = []
exe_srcs = []
exe_incs = []

lib_srcs = []
lib_incs = []

subdir('scripts')
subdir('Lib')

targets = ['cross', 'native']
targets_dep = {}
foreach t : targets
    dep = []
    if lib_srcs.length() != 0
      lib = static_library(
          meson.project_name() + '_' + t,
          lib_srcs,
          include_directories: lib_incs,
          native: t == 'native'
      )
      dep = declare_dependency(link_with: lib, include_directories: lib_incs)
    endif
    targets_dep += {t : dep}
endforeach


sim_bin = shared_library(
    meson.project_name() + '_sim',
    exe_srcs,
    include_directories: exe_incs,
    dependencies: [
        targets_dep['native'],
        pdsdk_dep_host
    ],
    native: true
)

resources_dir = meson.current_source_dir() / 'Source'

python = find_program('python3')
sim_pdx_dir = meson.project_name() + '_host.pdx'
sim_pdx = custom_target(meson.project_name() + '_host.pdx',
  output : meson.project_name() + '_host.pdx',
  command : [python,
                [meson.project_source_root() / 'scripts' / 'create_pdx.py',
                pd_sdk,
                sim_bin.full_path(),
                meson.current_build_dir() / sim_pdx_dir,
                resources_dir]],
  depends : sim_bin,
  build_always_stale: true)

message('sim pdx: ', sim_pdx.full_path())

pd_simulator = ''
if build_machine.system() == 'darwin'
  pd_simulator += pd_sdk / 'bin' / 'Playdate Simulator.app' / 'Contents' / 'MacOS' / 'Playdate Simulator'
elif build_machine.system() == 'linux'
  pd_simulator += pd_sdk / 'bin' / 'PlaydateSimulator'
endif

if pd_simulator == ''
  error('Build on ' + build_machine.system() + ' is not supported')
endif

run_target('sim',
  command : [pd_simulator, sim_pdx.full_path()],
  depends: sim_pdx)

pd_exe = executable(
    meson.project_name() + '_exe',
    exe_srcs + exe_srcs_cross,
    include_directories: exe_incs,
    link_args: pdsdk_link_args,
    dependencies: [
        targets_dep['cross'],
        pdsdk_dep_cross
    ]
)

objcopy = find_program('arm-none-eabi-objcopy')
pd_bin = custom_target('pdex.bin',
  output : 'pdex.bin',
  command : [objcopy, ['-O', 'binary', '-S', pd_exe.full_path(), 'pdex.bin']],
  depends : pd_exe)

pd_pdx_dir = meson.project_name() + '_cross.pdx'
pd_pdx = custom_target(meson.project_name() + '_cross.pdx',
  output : meson.project_name() + '_cross.pdx',
  command : [python,
                [meson.project_source_root() / 'scripts' / 'create_pdx.py',
                pd_sdk,
                pd_bin.full_path(),
                meson.current_build_dir() / pd_pdx_dir,
                resources_dir]],
  depends : pd_bin,
  build_always_stale: true)

message('cross pdx: ', pd_pdx.full_path())

