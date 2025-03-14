mkdir build && cd build
CC=/usr/bin/x86_64-w64-mingw32-gcc cmake .. -DHTTPS_EXFILTRATION=1 -DDEBUG=1 -DROGUE_PASSWORD="ChevaloReviensStp"
make -j8 2>&1
