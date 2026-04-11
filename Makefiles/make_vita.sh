export VITASDK=/usr/local/vitasdk
export PKG_CONFIG_PATH=$VITASDK/arm-vita-eabi/lib/pkgconfig
rm -rf build_vita
mkdir build_vita
cd build_vita
cmake ../ \
  -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake \
  -DVITA=ON \
  -DFORCE_DRAW_BG=ON \
  -DFORCE_DRAW_OVERLAY=ON \
  -DCMAKE_PREFIX_PATH=$VITASDK/arm-vita-eabi
make