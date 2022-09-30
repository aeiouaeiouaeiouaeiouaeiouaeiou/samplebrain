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
