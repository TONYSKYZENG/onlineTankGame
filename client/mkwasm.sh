mkdir wasm
cd wasm
source emsdk_env.sh
/home/tony/qt5/5_14/qt-everywhere-src-5.14.2/qtbase/bin/qmake ..
make -j8
