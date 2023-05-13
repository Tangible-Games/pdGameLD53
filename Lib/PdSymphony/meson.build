lib_incs = include_directories('.')

tests = [
    'aa_rect2d',
    'pd_animations',
    'point2d',
    'ray_casting_projection',
    'segment2d',
    'transformation_matrix3d',
    'vector2d',
]
foreach t : tests
    texe = executable(
        t + '_test',
        files(t + '_test.cpp'),
        include_directories: include_directories('.'),
        dependencies: [ gtest_dep, pdsdk_dep ],
        native: true)
    test(t + '_test', texe)
endforeach
