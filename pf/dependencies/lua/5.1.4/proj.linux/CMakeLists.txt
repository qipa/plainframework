# This file generate by plain framework admin tool, date: 2017-05-21 12:54:17
SET(LIBRARY_OUTPUT_PATH ./../../../dll/)

ADD_DEFINITIONS(-DLUA_USE_MKSTEMP)
SET(USE_32BITS 0)

IF(CMAKE_SYSTEM MATCHES Linux)
  ADD_DEFINITIONS(-D_REENTRANT)
  ADD_DEFINITIONS(-DDONT_TD_VOID)
  ADD_DEFINITIONS(-DLUA_USE_LINUX)
ELSE(CMAKE_SYSTEM MATCHES Linux)
ENDIF(CMAKE_SYSTEM MATCHES Linux)

LINK_DIRECTORIES(
  "./"
)

INCLUDE_DIRECTORIES(
  "../include/"
)


SET (INCLUDE_LIST
  ../include/lapi.h
  ../include/lauxlib.h
  ../include/lcode.h
  ../include/ldebug.h
  ../include/ldo.h
  ../include/lfunc.h
  ../include/lgc.h
  ../include/llex.h
  ../include/llimits.h
  ../include/lmem.h
  ../include/lobject.h
  ../include/lopcodes.h
  ../include/lparser.h
  ../include/lstate.h
  ../include/lstring.h
  ../include/ltable.h
  ../include/ltm.h
  ../include/lua.h
  ../include/luaconf.h
  ../include/lualib.h
  ../include/lundump.h
  ../include/lvm.h
  ../include/lzio.h
)

SET (SRC_LIST
  ../src/lapi.c
  ../src/lauxlib.c
  ../src/lbaselib.c
  ../src/lcode.c
  ../src/ldblib.c
  ../src/ldebug.c
  ../src/ldo.c
  ../src/ldump.c
  ../src/lfunc.c
  ../src/lgc.c
  ../src/linit.c
  ../src/liolib.c
  ../src/llex.c
  ../src/lmathlib.c
  ../src/lmem.c
  ../src/loadlib.c
  ../src/lobject.c
  ../src/lopcodes.c
  ../src/loslib.c
  ../src/lparser.c
  ../src/lstate.c
  ../src/lstring.c
  ../src/lstrlib.c
  ../src/ltable.c
  ../src/ltablib.c
  ../src/ltm.c
  ../src/lundump.c
  ../src/lvm.c
  ../src/lzio.c
  ../src/print.c
)


ADD_LIBRARY(lua SHARED
  ${SRC_LIST}
)

if (WIN32)
TARGET_LINK_LIBRARIES(lua ws2_32.lib )
else()
TARGET_LINK_LIBRARIES(lua )
  if(USE_32BITS)
    SET(CMAKE_C_FLAGS "-Wall -ggdb -pipe -march=i386 -mtune=i686")
    SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -ggdb -pipe -march=i386 -mtune=i686")
  else()
    SET(CMAKE_C_FLAGS "-Wall -ggdb -pipe -march=x86-64 -mtune=i686")
    SET(CMAKE_CXX_FLAGS "-std=c++11 -Wall -ggdb -pipe -march=x86-64 -mtune=i686")
  endif(USE_32BITS)
endif(WIN32)
