lib_incs = include_directories('.')

tests = ['point2d', 'segment2d', 'vector2d', 'transformation_matrix3d', 'ray_casting_projection']
foreach t : tests
    texe = executable(
        t + '_test',
        files(t + '_test.cpp'),
        include_directories: include_directories('.'),
        dependencies: [ gtest_dep ],
        native: true)
    test(t + '_test', texe)
endforeach
