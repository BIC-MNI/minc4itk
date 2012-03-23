# CMakeFiles.txt for the minc4itk 
#
# Vladimir S. FONOV - vladimir.fonov@gmail.com
project(ITKIOMINC)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
FIND_PACKAGE( MINC2 REQUIRED )

INCLUDE( ${MINC2_USE_FILE} )

SET(MINC4ITK_HEADERS 
  include/itkMincImageIOFactory.h
  include/itkMincImageIO.h
  include/minc_general_transform.h
  include/minc_helpers.h
)

SET(ITKIOMINC_LIBRARIES ITKIOMINC ${EZMINC_LIBRARIES})


IF(NOT itk-module) #building outside of ITKv4 system
  #FIND_PACKAGE( ITK REQUIRED )
  INCLUDE(${ITK_USE_FILE})

  IF(NOT ITK_FOUND)
    MESSAGE( FATAL_ERROR "ITK Is missing!")
  ENDIF(NOT ITK_FOUND)

  IF(BUILD_SHARED_LIBS AND NOT ITK_BUILD_SHARED)
    message(WARNING "Building Shared library but ITK is linked statically!")
  ENDIF(BUILD_SHARED_LIBS AND NOT ITK_BUILD_SHARED)
ENDIF(NOT itk-module) #building outside of ITKv4 system

add_subdirectory(src)

  
IF(NOT itk-module) #building outside of ITKv4 system

  OPTION(MINC4ITK_BUILD_EXAMPLES   "Build minc4itk examples"    ON)
  OPTION(MINC4ITK_BUILD_TOOLS      "Build minc4itk-bases tools" ON)

  LINK_DIRECTORIES(${ITK_LIBRARY_DIRS})
  INCLUDE_DIRECTORIES(${ITK_INCLUDE_DIRS} include)
 
  TARGET_LINK_LIBRARIES( ITKIOMINC 
      ${ITK_LIBRARIES}
      itkvnl_algo
      itkvnl
      ${EZMINC_LIBRARIES}
      )
  
  INSTALL(FILES  ${MINC4ITK_HEADERS} DESTINATION include)

  IF(MINC4ITK_BUILD_EXAMPLES)
    add_subdirectory(examples)
  ENDIF(MINC4ITK_BUILD_EXAMPLES)

  IF(MINC4ITK_BUILD_TOOLS)
    add_subdirectory(tools)
  ENDIF(MINC4ITK_BUILD_TOOLS)

ENDIF(NOT itk-module)
