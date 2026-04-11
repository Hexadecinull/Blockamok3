export VITASDK=/usr/local/vitasdk
export PATH=$VITASDK/bin:$PATH
export PKG_CONFIG_PATH=$VITASDK/arm-vita-eabi/lib/pkgconfig
# arm-vita-eabi-pkg-config is the cross-compiling pkg-config for the Vita sysroot.
# We must pass it explicitly to cmake; otherwise cmake uses the host pkg-config
# which knows nothing about vitasdk and fails PKG_SEARCH_MODULE for SDL2_mixer/ttf.
export PKG_CONFIG=$VITASDK/bin/arm-vita-eabi-pkg-config
rm -rf build_vita
mkdir build_vita
cd build_vita
cmake ../ \
  -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake \
  -DVITA=ON \
  -DFORCE_DRAW_BG=ON \
  -DFORCE_DRAW_OVERLAY=ON \
  -DCMAKE_PREFIX_PATH=$VITASDK/arm-vita-eabi \
  -DPKG_CONFIG_EXECUTABLE=$VITASDK/bin/arm-vita-eabi-pkg-config
make
