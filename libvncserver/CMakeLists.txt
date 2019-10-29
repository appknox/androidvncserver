cmake_minimum_required(VERSION 3.4.1)
project(libvncserver VERSION 0.9.12 LANGUAGES C)
include(CheckFunctionExists)
include(CheckSymbolExists)
include(CheckIncludeFile)
include(CheckTypeSize)
include(TestBigEndian)
include(CheckCSourceCompiles)
include(CheckCSourceRuns)

set(PACKAGE_NAME           "LibVNCServer")
set(FULL_PACKAGE_NAME      "LibVNCServer")
set(VERSION_SO             "1")
set(LIBVNCSERVER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libvncserver)
set(COMMON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/common)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/libvncserver ${CMAKE_CURRENT_SOURCE_DIR}/common)

# all the build configuration switches
option(WITH_ZLIB "Search for the zlib compression library to support additional encodings" ON)
option(WITH_LZO "Search for the LZO compression library to omit internal miniLZO implementation" ON)
option(WITH_JPEG "Search for the libjpeg compression library to support additional encodings" ON)
option(WITH_PNG "Search for the PNG compression library to support additional encodings" ON)
option(WITH_SDL "Search for the Simple Direct Media Layer library to build an example SDL vnc client" OFF)
option(WITH_THREADS "Search for a threading library to build with multithreading support" OFF)
option(WITH_GNUTLS "Search for the GnuTLS secure communications library to support encryption" OFF)
option(WITH_OPENSSL "Search for the OpenSSL cryptography library to support encryption" ON)
option(WITH_SYSTEMD "Search for libsystemd to build with systemd socket activation support" OFF)
option(WITH_GCRYPT "Search for libgcrypt to support additional authentication methods in LibVNCClient" OFF)
option(WITH_FFMPEG "Search for FFMPEG to build an example VNC to MPEG encoder" OFF)
option(WITH_TIGHTVNC_FILETRANSFER "Enable filetransfer if there is pthreads support" OFF)
option(WITH_24BPP "Allow 24 bpp" ON)
option(WITH_IPv6 "Enable IPv6 Support" ON)
option(WITH_WEBSOCKETS "Build with websockets support" OFF)
option(WITH_SASL "Build with SASL support" OFF)

if(WITH_ZLIB)
  find_package(ZLIB)
endif(WITH_ZLIB)

if(WITH_LZO)
  find_package(LZO)
endif()

if(WITH_JPEG)
  ADD_SUBDIRECTORY(libjpeg-turbo)
  set(JPEG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/libjpeg-turbo)
  set(JPEG_LIBRARIES jpeg-static)
  set(JPEG_FOUND TRUE)
endif(WITH_JPEG)

if(WITH_PNG)
  ADD_SUBDIRECTORY(libpng)
  set(PNG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/libpng)
  set(PNG_LIBRARIES png_static)
  set(PNG_FOUND TRUE)
endif(WITH_PNG)

if(WITH_SDL)
  find_package(SDL2)
endif(WITH_SDL)


if(WITH_THREADS)
  find_package(Threads)
endif(WITH_THREADS)


if(WITH_GNUTLS)
  find_package(GnuTLS)
endif(WITH_GNUTLS)


if(WITH_OPENSSL)
  find_package(OpenSSL)
endif(WITH_OPENSSL)


if(WITH_SYSTEMD AND NOT ANDROID)
  find_package(PkgConfig)
  pkg_check_modules(SYSTEMD "libsystemd")
endif(WITH_SYSTEMD AND NOT ANDROID)


if(WITH_GCRYPT)
  find_library(LIBGCRYPT_LIBRARIES gcrypt)
endif(WITH_GCRYPT)

if(WITH_FFMPEG)
  find_package(FFMPEG 3.1.0)
endif(WITH_FFMPEG)


check_include_file("endian.h"      LIBVNCSERVER_HAVE_ENDIAN_H)
check_include_file("fcntl.h"       LIBVNCSERVER_HAVE_FCNTL_H)
check_include_file("netinet/in.h"  LIBVNCSERVER_HAVE_NETINET_IN_H)
check_include_file("sys/endian.h"  LIBVNCSERVER_HAVE_SYS_ENDIAN_H)
check_include_file("sys/socket.h"  LIBVNCSERVER_HAVE_SYS_SOCKET_H)
check_include_file("sys/stat.h"    LIBVNCSERVER_HAVE_SYS_STAT_H)
check_include_file("sys/time.h"    LIBVNCSERVER_HAVE_SYS_TIME_H)
check_include_file("sys/types.h"   LIBVNCSERVER_HAVE_SYS_TYPES_H)
check_include_file("sys/wait.h"    LIBVNCSERVER_HAVE_SYS_WAIT_H)
check_include_file("unistd.h"      LIBVNCSERVER_HAVE_UNISTD_H)
check_include_file("sys/uio.h"     LIBVNCSERVER_HAVE_SYS_UIO_H)
check_include_file("sys/resource.h"     LIBVNCSERVER_HAVE_SYS_RESOURCE_H)


# headers needed for check_type_size()
check_include_file("vfork.h"       LIBVNCSERVER_HAVE_VFORK_H)
check_include_file("ws2tcpip.h"    LIBVNCSERVER_HAVE_WS2TCPIP_H)
check_include_file("arpa/inet.h"   HAVE_ARPA_INET_H)
check_include_file("stdint.h"      HAVE_STDINT_H)
check_include_file("stddef.h"      HAVE_STDDEF_H)
check_include_file("sys/types.h"   HAVE_SYS_TYPES_H)

# error out if required headers not found
if(NOT HAVE_STDINT_H)
  message(FATAL_ERROR "Could NOT find required header stdint.h")
endif()

check_function_exists(gettimeofday    LIBVNCSERVER_HAVE_GETTIMEOFDAY)
check_function_exists(vfork           LIBVNCSERVER_HAVE_VFORK)
check_function_exists(vprintf         LIBVNCSERVER_HAVE_VPRINTF)
check_function_exists(mmap            LIBVNCSERVER_HAVE_MMAP)
check_function_exists(fork            LIBVNCSERVER_HAVE_FORK)
check_function_exists(ftime           LIBVNCSERVER_HAVE_FTIME)
check_function_exists(gethostbyname   LIBVNCSERVER_HAVE_GETHOSTBYNAME)
check_function_exists(gethostname     LIBVNCSERVER_HAVE_GETHOSTNAME)
check_function_exists(inet_ntoa       LIBVNCSERVER_HAVE_INET_NTOA)
check_function_exists(memmove         LIBVNCSERVER_HAVE_MEMMOVE)
check_function_exists(memset          LIBVNCSERVER_HAVE_MEMSET)
check_function_exists(mkfifo          LIBVNCSERVER_HAVE_MKFIFO)
check_function_exists(select          LIBVNCSERVER_HAVE_SELECT)
check_function_exists(socket          LIBVNCSERVER_HAVE_SOCKET)
check_function_exists(strchr          LIBVNCSERVER_HAVE_STRCHR)
check_function_exists(strcspn         LIBVNCSERVER_HAVE_STRCSPN)
check_function_exists(strdup          LIBVNCSERVER_HAVE_STRDUP)
check_function_exists(strerror        LIBVNCSERVER_HAVE_STRERROR)
check_function_exists(strstr          LIBVNCSERVER_HAVE_STRSTR)

check_symbol_exists(htobe64 "endian.h" LIBVNCSERVER_HAVE_HTOBE64)
check_symbol_exists(OSSwapHostToBigInt64 "libkern/OSByteOrder.h" LIBVNCSERVER_HAVE_OSSWAPHOSTTOBIGINT64)

if(Threads_FOUND)
  set(ADDITIONAL_LIBS ${ADDITIONAL_LIBS} ${CMAKE_THREAD_LIBS_INIT})
endif(Threads_FOUND)
if(ZLIB_FOUND)
  set(LIBVNCSERVER_HAVE_LIBZ 1)
else()
  unset(ZLIB_LIBRARIES) # would otherwise contain -NOTFOUND, confusing target_link_libraries()
endif(ZLIB_FOUND)
if(LZO_FOUND)
  set(LIBVNCSERVER_HAVE_LZO 1)
else()
  unset(LZO_LIBRARIES CACHE) # would otherwise contain -NOTFOUND, confusing target_link_libraries()
endif()
if(JPEG_FOUND)
  set(LIBVNCSERVER_HAVE_LIBJPEG 1)
else()
  unset(JPEG_LIBRARIES) # would otherwise confuse target_link_libraries()
endif(JPEG_FOUND)
if(PNG_FOUND)
  set(LIBVNCSERVER_HAVE_LIBPNG 1)
else()
  unset(PNG_LIBRARIES) # would otherwise contain -NOTFOUND, confusing target_link_libraries()
endif(PNG_FOUND)
if(NOT OPENSSL_FOUND)
    unset(OPENSSL_LIBRARIES) # would otherwise contain -NOTFOUND, confusing target_link_libraries()
endif()
if(SYSTEMD_FOUND)
  add_definitions(-DLIBVNCSERVER_WITH_SYSTEMD)
  include_directories(${SYSTEMD_INCLUDE_DIRS})
  set(ADDITIONAL_LIBS ${ADDITIONAL_LIBS} ${SYSTEMD_LIBRARIES})
endif(SYSTEMD_FOUND)

if(LIBVNCSERVER_HAVE_SYS_UIO_H)
  if(WITH_GCRYPT AND LIBGCRYPT_LIBRARIES)
    message(STATUS "Building crypto with Libgcrypt")
    set(CRYPTO_LIBRARIES ${LIBGCRYPT_LIBRARIES})
    set(CRYPTO_SOURCES ${COMMON_DIR}/rfbcrypto_libgcrypt)
  elseif(OPENSSL_FOUND)
    message(STATUS "Building crypto with OpenSSL")
    set(CRYPTO_LIBRARIES ${OPENSSL_LIBRARIES})
    set(CRYPTO_SOURCES ${COMMON_DIR}/rfbcrypto_openssl)
  else()
    message(STATUS "Building crypto with builtin functions")
    set(CRYPTO_SOURCES ${COMMON_DIR}/rfbcrypto_included.c ${COMMON_DIR}/md5.c ${COMMON_DIR}/sha1.c)
  endif()
  set(LIBVNCSERVER_HAVE_CRYPTO 1)
endif(LIBVNCSERVER_HAVE_SYS_UIO_H)


if(WITH_WEBSOCKETS AND LIBVNCSERVER_HAVE_CRYPTO AND (LIBVNCSERVER_HAVE_HTOBE64 OR LIBVNCSERVER_HAVE_OSSWAPHOSTTOBIGINT64))
  set(LIBVNCSERVER_WITH_WEBSOCKETS 1)
endif()

if(WITH_GCRYPT AND LIBGCRYPT_LIBRARIES)
  message(STATUS "Found libgcrypt: ${LIBGCRYPT_LIBRARIES}")
  set(LIBVNCSERVER_WITH_CLIENT_GCRYPT 1)
  set(ADDITIONAL_LIBS ${ADDITIONAL_LIBS} ${LIBGCRYPT_LIBRARIES})
endif(WITH_GCRYPT AND LIBGCRYPT_LIBRARIES)

if(GNUTLS_FOUND)
  set(LIBVNCSERVER_HAVE_GNUTLS 1)
endif(GNUTLS_FOUND)

if(OPENSSL_FOUND)
  set(LIBVNCSERVER_HAVE_LIBSSL 1)
endif(OPENSSL_FOUND)

if(WITH_IPv6)
  if(WIN32 AND LIBVNCSERVER_HAVE_WS2TCPIP_H AND LIBVNCSERVER_HAVE_VPRINTF)
    set(LIBVNCSERVER_IPv6 1)
  endif()
  if(NOT WIN32)
    set(LIBVNCSERVER_IPv6 1)
  endif()
endif(WITH_IPv6)


if(WITH_24BPP)
  set(LIBVNCSERVER_ALLOW24BPP 1)
endif()


if(CMAKE_USE_PTHREADS_INIT)
  set(LIBVNCSERVER_HAVE_LIBPTHREAD 1)
endif(CMAKE_USE_PTHREADS_INIT)
if(LIBVNCSERVER_HAVE_SYS_SOCKET_H)
  # socklen_t
  list(APPEND CMAKE_EXTRA_INCLUDE_FILES "sys/socket.h")
endif(LIBVNCSERVER_HAVE_SYS_SOCKET_H)
if(HAVE_ARPA_INET_H)
  # in_addr_t
  list(APPEND CMAKE_EXTRA_INCLUDE_FILES "arpa/inet.h")
endif(HAVE_ARPA_INET_H)

check_type_size(pid_t     LIBVNCSERVER_PID_T)
check_type_size(size_t    LIBVNCSERVER_SIZE_T)
check_type_size(socklen_t LIBVNCSERVER_SOCKLEN_T)
check_type_size(in_addr_t LIBVNCSERVER_IN_ADDR_T)
if(NOT HAVE_LIBVNCSERVER_IN_ADDR_T)
  set(LIBVNCSERVER_NEED_INADDR_T 1)
endif(NOT HAVE_LIBVNCSERVER_IN_ADDR_T)

TEST_BIG_ENDIAN(LIBVNCSERVER_WORDS_BIGENDIAN)

if(WITH_SASL)
  find_path(SASL2_INCLUDE_DIR sasl/sasl.h)
  find_library(LIBSASL2_LIBRARIES sasl2 libsasl.lib)
endif(WITH_SASL)

if(WITH_SASL AND LIBSASL2_LIBRARIES AND SASL2_INCLUDE_DIR)
  message(STATUS "Building with SASL: ${LIBSASL2_LIBRARIES} and ${SASL2_INCLUDE_DIR}")
  set(LIBVNCSERVER_HAVE_SASL 1)
  set(ADDITIONAL_LIBS ${ADDITIONAL_LIBS} ${LIBSASL2_LIBRARIES})
  include_directories(${SASL2_INCLUDE_DIR})
endif(WITH_SASL AND LIBSASL2_LIBRARIES AND SASL2_INCLUDE_DIR)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/rfb/rfbconfig.h.cmakein ${CMAKE_CURRENT_BINARY_DIR}/rfb/rfbconfig.h)
set(LIBVNCSERVER_SOURCES
    ${LIBVNCSERVER_DIR}/main.c
    ${LIBVNCSERVER_DIR}/rfbserver.c
    ${LIBVNCSERVER_DIR}/rfbregion.c
    ${LIBVNCSERVER_DIR}/auth.c
    ${LIBVNCSERVER_DIR}/sockets.c
    ${LIBVNCSERVER_DIR}/stats.c
    ${LIBVNCSERVER_DIR}/corre.c
    ${LIBVNCSERVER_DIR}/hextile.c
    ${LIBVNCSERVER_DIR}/rre.c
    ${LIBVNCSERVER_DIR}/translate.c
    ${LIBVNCSERVER_DIR}/cutpaste.c
    ${LIBVNCSERVER_DIR}/httpd.c
    ${LIBVNCSERVER_DIR}/cursor.c
    ${LIBVNCSERVER_DIR}/font.c
    ${LIBVNCSERVER_DIR}/draw.c
    ${LIBVNCSERVER_DIR}/selbox.c
    ${COMMON_DIR}/d3des.c
    ${COMMON_DIR}/vncauth.c
    ${LIBVNCSERVER_DIR}/cargs.c
    ${LIBVNCSERVER_DIR}/ultra.c
    ${LIBVNCSERVER_DIR}/scale.c
)

if(GNUTLS_FOUND)
  set(LIBVNCSERVER_SOURCES
    ${LIBVNCSERVER_SOURCES}
    ${LIBVNCSERVER_DIR}/rfbssl_gnutls.c
    )
  include_directories(${GNUTLS_INCLUDE_DIR})
elseif(OPENSSL_FOUND)
  set(LIBVNCSERVER_SOURCES
    ${LIBVNCSERVER_SOURCES}
    ${LIBVNCSERVER_DIR}/rfbssl_openssl.c
  )
  include_directories(${OPENSSL_INCLUDE_DIR})
else()
  set(LIBVNCSERVER_SOURCES
    ${LIBVNCSERVER_SOURCES}
    ${LIBVNCSERVER_DIR}/rfbssl_none.c
  )
endif()

if(ZLIB_FOUND)
  add_definitions(-DLIBVNCSERVER_HAVE_LIBZ)
  include_directories(${ZLIB_INCLUDE_DIR})
  set(LIBVNCSERVER_SOURCES
    ${LIBVNCSERVER_SOURCES}
    ${LIBVNCSERVER_DIR}/zlib.c
    ${LIBVNCSERVER_DIR}/zrle.c
    ${LIBVNCSERVER_DIR}/zrleoutstream.c
    ${LIBVNCSERVER_DIR}/zrlepalettehelper.c
  )
endif(ZLIB_FOUND)

if(LZO_FOUND)
  add_definitions(-DLIBVNCSERVER_HAVE_LZO)
  include_directories(${LZO_INCLUDE_DIR})
else()
  set(LIBVNCSERVER_SOURCES
    ${LIBVNCSERVER_SOURCES}
    ${COMMON_DIR}/minilzo.c
  )
endif()

if(JPEG_FOUND)
  add_definitions(-DLIBVNCSERVER_HAVE_LIBJPEG)
  include_directories(${JPEG_INCLUDE_DIR})
  set(TIGHT_C ${LIBVNCSERVER_DIR}/tight.c ${COMMON_DIR}/turbojpeg.c)
endif(JPEG_FOUND)

if(PNG_FOUND)
  add_definitions(-DLIBVNCSERVER_HAVE_LIBPNG)
  include_directories(${PNG_INCLUDE_DIR})
endif(PNG_FOUND)

set(LIBVNCSERVER_SOURCES
    ${LIBVNCSERVER_SOURCES}
    ${TIGHT_C}
)

if(WITH_TIGHTVNC_FILETRANSFER AND CMAKE_USE_PTHREADS_INIT)
  set(LIBVNCSERVER_SOURCES
    ${LIBVNCSERVER_SOURCES}
    ${LIBVNCSERVER_DIR}/tightvnc-filetransfer/rfbtightserver.c
    ${LIBVNCSERVER_DIR}/tightvnc-filetransfer/handlefiletransferrequest.c
    ${LIBVNCSERVER_DIR}/tightvnc-filetransfer/filetransfermsg.c
    ${LIBVNCSERVER_DIR}/tightvnc-filetransfer/filelistinfo.c
  )
endif(WITH_TIGHTVNC_FILETRANSFER AND CMAKE_USE_PTHREADS_INIT)

if(LIBVNCSERVER_WITH_WEBSOCKETS)
  add_definitions(-DLIBVNCSERVER_WITH_WEBSOCKETS)
  set(LIBVNCSERVER_SOURCES
    ${LIBVNCSERVER_SOURCES}
    ${LIBVNCSERVER_DIR}/websockets.c
    ${LIBVNCSERVER_DIR}/ws_decode.c
    ${COMMON_DIR}/base64.c
    ${CRYPTO_SOURCES}
  )
endif(LIBVNCSERVER_WITH_WEBSOCKETS)

add_library(vncserver STATIC ${LIBVNCSERVER_SOURCES})

target_link_libraries(vncserver
                      ${ADDITIONAL_LIBS}
                      ${ZLIB_LIBRARIES}
                      ${LZO_LIBRARIES}
                      ${JPEG_LIBRARIES}
                      ${PNG_LIBRARIES}
                      ${CRYPTO_LIBRARIES}
                      ${GNUTLS_LIBRARIES}
                      ${OPENSSL_LIBRARIES}
)

