subdir('PdSymphony')

python = find_program('python3')

generated_srcs = [custom_target('generate_stations',
    input : 'ST01_Central_Station.json',
    output : 'ST01.cpp',
    command : [python,
                [meson.project_source_root() / 'Lib/build_station.py',
                '--json_input=@INPUT@',
                '--cpp_output=@OUTPUT@',
                '--var_name=ST01CentralStation',
                '--name=Central Station',
                '--desc=Guten Tag, Hola, Hello! Welcome to Central! Travellers, businessmen and diplomats just love coming here. Feel at home and make sure to visit once in a while. Remember: Central is THE place.',
                '--difficulty=0',
                '--difficulty_str=moderate',
                '--jump_distance=1800']])]

exe_srcs += files(
    'asteroid.cpp',
    'game.cpp',
    'main.c',
    'space_craft.cpp',
    'space_station.cpp',
    'stars.cpp',
    'static_random_generator.cpp',
    'ui_game_interface.cpp',
    'ui_station.cpp',
)

exe_srcs += generated_srcs

exe_incs += include_directories('.')
