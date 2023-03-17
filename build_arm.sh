mkdir -p build_arm
cd build_arm
cmake -DCMAKE_TOOLCHAIN_FILE=$PLAYDATE_SDK_PATH/C_API/buildsupport/arm.cmake ..
make
cd ..

pdc Source ./pdGameLD53_arm.pdx
