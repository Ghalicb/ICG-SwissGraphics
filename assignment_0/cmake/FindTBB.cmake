## ======================================================================== ##
## Copyright 2009-2015 Intel Corporation                                    ##
##                                                                          ##
## Licensed under the Apache License, Version 2.0 (the "License");          ##
## you may not use this file except in compliance with the License.         ##
## You may obtain a copy of the License at                                  ##
##                                                                          ##
##     http://www.apache.org/licenses/LICENSE-2.0                           ##
##                                                                          ##
## Unless required by applicable law or agreed to in writing, software      ##
## distributed under the License is distributed on an "AS IS" BASIS,        ##
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. ##
## See the License for the specific language governing permissions and      ##
## limitations under the License.                                           ##
## ======================================================================== ##

IF (WIN32)
  FIND_PATH(TBB_ROOT include/tbb/task_scheduler_init.h
    DOC "Root of TBB installation"
    PATHS ${PROJECT_SOURCE_DIR}/tbb "C:/Program Files (x86)/Intel/Composer XE/tbb"
  )

  IF (CMAKE_SIZEOF_VOID_P EQUAL 8)
    SET(TBB_ARCH intel64)
  ELSE()
    SET(TBB_ARCH ia32)
  ENDIF()

  IF (MSVC10)
    SET(TBB_VCVER vc10)
  ELSEIF (MSVC11)
    SET(TBB_VCVER vc11)
  ELSE()
    SET(TBB_VCVER vc12)
  ENDIF()

  SET(TBB_LIBDIR ${TBB_ROOT}/lib/${TBB_ARCH}/${TBB_VCVER})
  SET(TBB_BINDIR ${TBB_ROOT}/bin/${TBB_ARCH}/${TBB_VCVER})

  IF (TBB_ROOT STREQUAL "")
    FIND_PATH(TBB_INCLUDE_DIR tbb/task_scheduler_init.h)
    FIND_LIBRARY(TBB_LIBRARY tbb)
    FIND_LIBRARY(TBB_LIBRARY_MALLOC tbbmalloc)
  ELSE()
    SET(TBB_INCLUDE_DIR TBB_INCLUDE_DIR-NOTFOUND)
    SET(TBB_LIBRARY TBB_LIBRARY-NOTFOUND)
    SET(TBB_LIBRARY_MALLOC TBB_LIBRARY_MALLOC-NOTFOUND)
    FIND_PATH(TBB_INCLUDE_DIR tbb/task_scheduler_init.h PATHS ${TBB_ROOT}/include NO_DEFAULT_PATH)
    FIND_LIBRARY(TBB_LIBRARY tbb PATHS ${TBB_LIBDIR} NO_DEFAULT_PATH)
    FIND_LIBRARY(TBB_LIBRARY_MALLOC tbbmalloc PATHS ${TBB_LIBDIR} NO_DEFAULT_PATH)
  ENDIF()

ELSE ()

  FIND_PATH(TBB_ROOT include/tbb/task_scheduler_init.h
    DOC "Root of TBB installation"
    PATHS ${PROJECT_SOURCE_DIR}/tbb
    /opt/intel/composerxe/tbb
    $ENV{TBB_INC}/..
  )
  
  IF (TBB_ROOT STREQUAL "")
    FIND_PATH(TBB_INCLUDE_DIR tbb/task_scheduler_init.h)
    FIND_LIBRARY(TBB_LIBRARY tbb)
    FIND_LIBRARY(TBB_LIBRARY_MALLOC tbbmalloc)
  ELSE()
    SET(TBB_INCLUDE_DIR TBB_INCLUDE_DIR-NOTFOUND)
    SET(TBB_LIBRARY TBB_LIBRARY-NOTFOUND)
    SET(TBB_LIBRARY_MALLOC TBB_LIBRARY_MALLOC-NOTFOUND)
    IF (APPLE)
      FIND_PATH(TBB_INCLUDE_DIR tbb/task_scheduler_init.h PATHS ${TBB_ROOT}/include NO_DEFAULT_PATH)
      FIND_LIBRARY(TBB_LIBRARY tbb PATHS ${TBB_ROOT}/lib NO_DEFAULT_PATH)
      FIND_LIBRARY(TBB_LIBRARY_MALLOC tbbmalloc PATHS ${TBB_ROOT}/lib NO_DEFAULT_PATH)
    ELSE()
      FIND_PATH(TBB_INCLUDE_DIR tbb/task_scheduler_init.h PATHS ${TBB_ROOT}/include NO_DEFAULT_PATH)
      FIND_LIBRARY(TBB_LIBRARY tbb PATHS ${TBB_ROOT}/lib/intel64/gcc4.4 ${TBB_ROOT}/lib ${TBB_ROOT}/lib64 NO_DEFAULT_PATH)
      FIND_LIBRARY(TBB_LIBRARY_MALLOC tbbmalloc PATHS ${TBB_ROOT}/lib/intel64/gcc4.4 ${TBB_ROOT}/lib ${TBB_ROOT}/lib64 NO_DEFAULT_PATH)
    ENDIF()
  ENDIF()

ENDIF()

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(TBB DEFAULT_MSG TBB_INCLUDE_DIR TBB_LIBRARY TBB_LIBRARY_MALLOC)

IF (TBB_FOUND)
  SET(TBB_INCLUDE_DIRS ${TBB_INCLUDE_DIR})
  SET(TBB_LIBRARIES ${TBB_LIBRARY} ${TBB_LIBRARY_MALLOC})
ENDIF()

MARK_AS_ADVANCED(TBB_INCLUDE_DIR)
MARK_AS_ADVANCED(TBB_LIBRARY)
MARK_AS_ADVANCED(TBB_LIBRARY_MALLOC)

##############################################################
# Install TBB
##############################################################

IF (WIN32)
  INSTALL(PROGRAMS ${TBB_BINDIR}/tbb.dll ${TBB_BINDIR}/tbbmalloc.dll RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} DESTINATION ${CMAKE_INSTALL_BINDIR} COMPONENT examples)
  INSTALL(PROGRAMS ${TBB_BINDIR}/tbb.dll ${TBB_BINDIR}/tbbmalloc.dll RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib)
ELSEIF (RTCORE_ZIP_MODE)
  IF (APPLE)
    INSTALL(PROGRAMS ${TBB_ROOT}/lib/libc++/libtbb.dylib ${TBB_ROOT}/lib/libc++/libtbbmalloc.dylib DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib)
  ELSE()
    INSTALL(PROGRAMS ${TBB_ROOT}/lib/intel64/gcc4.4/libtbb.so.2 ${TBB_ROOT}/lib/intel64/gcc4.4/libtbbmalloc.so.2 DESTINATION ${CMAKE_INSTALL_LIBDIR} COMPONENT lib)
  ENDIF()
ENDIF()
