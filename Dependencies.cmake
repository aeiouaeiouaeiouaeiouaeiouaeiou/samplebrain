################################################################################
# FetchContent
################################################################################

include(FetchContent)

################################################################################
# fftw3
################################################################################

FetchContent_Declare(
  fftw3
  URL       http://fftw.org/fftw-3.3.10.tar.gz
  URL_HASH  MD5=8ccbf6a5ea78a16dbc3e1306e234cc5c)
FetchContent_MakeAvailable(fftw3)

include_directories(${fftw3_SOURCE_DIR}/api)

################################################################################
# liblo
################################################################################

FetchContent_Declare(
  liblo
  URL       http://downloads.sourceforge.net/liblo/liblo-0.31.tar.gz
  URL_HASH  MD5=14378c1e74c58e777fbb4fcf33ac5315)
FetchContent_MakeAvailable(liblo)

add_subdirectory(${liblo_SOURCE_DIR}/cmake)
