CMAKE_MINIMUM_REQUIRED (VERSION 3.0.0 FATAL_ERROR)
IF (NOT MYPACKAGEBOOTSTRAP_DONE)
  INCLUDE ("3rdparty/github/cmake-utils/cmake/MyPackageBootstrap.cmake")
ENDIF ()
MYPACKAGESTART (genericScan 1 0 1)

######################
# Library definition #
######################
FILE (GLOB lib_src src/*.c)
MYPACKAGELIBRARY(
  ${CMAKE_CURRENT_SOURCE_DIR}/include/genericScan_config.h.in
  ${INCLUDE_OUTPUT_PATH}/genericScan/config.h
  ${lib_src})

################
# Dependencies #
################
MYPACKAGEDEPENDENCY (genericStack  "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/github/genericStack")
MYPACKAGEDEPENDENCY (genericLogger "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/github/genericLogger" TESTS)

#############
# Packaging #
#############
MYPACKAGEPACK("" "Generic Scan")

#########
# Setup #
#########
MYPACKAGEPRINTSETUP()
