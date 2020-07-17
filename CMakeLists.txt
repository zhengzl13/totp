# vim: syntax=cmake
cmake_minimum_required(VERSION 2.8.11)
add_compile_options(-g -rdynamic -ldl -funwind-tables -fPIC -O0)

# set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
# set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

include_directories(.)
include_directories(./include)
set(TOTP_DEMO_SRC
      main.c
      include/sha/sha1.c
      include/hmac/hmac_sha1.c
      totp.c
    )

add_executable(totp_demo ${TOTP_DEMO_SRC})
