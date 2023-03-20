mkdir -p build_arm
cd build_arm
cmake -DCMAKE_TOOLCHAIN_FILE=/Users/dmitriitokarev/Developer/PlaydateSDK/C_API/buildsupport/arm.cmake ..
make
cd ..

pdc Source ./pdGameLD53_arm.pdx
