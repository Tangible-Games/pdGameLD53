lib_incs = include_directories('.')

tests = ['point2d', 'segment2d', 'vector2d']
foreach t : tests
    texe = executable(
        t + '_test',
        files(t + '_test.cpp'),
        include_directories: include_directories('.'),
        native: true)
    test(t + '_test', texe)
endforeach