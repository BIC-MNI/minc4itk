# CMakeFiles.txt for the minc4itk 
#
# Vladimir S. FONOV - vladimir.fonov@gmail.com
project(ITKIOMINC)
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE( MINC2 REQUIRED )

if(not itk-module)
  FIND_PACKAGE( ITK REQUIRED )
ENDIF(not itk-module)


SET( MINC4ITK_HEADERS
    include/itkMincImageIOFactory.h
    include/minc_general_transform.h
    include/minc_helpers.h
    include/itkMincImageIO.h
    )

SET( MINC4ITK_SRC 
    src/minc_helpers.cxx
    src/itkMincImageIO.cxx
    src/itkMincImageIOFactory.cxx
  )

INCLUDE( ${MINC2_USE_FILE} )


IF(itk-module) # module for ITKv4

  TARGET_LINK_LIBRARIES(ITKIOMINC ${ITKIOTransformBase_LIBRARIES} ${MINC2_LIBRARIES})
  ADD_LIBRARY( ITKIOMINC ${MINC4ITK_HEADERS} ${MINC4ITK_SRC})

  SET(ITKIOMINC_LIBRARIES ITKIOMINC)
  itk_module_target(ITKIOMINC)
  
ELSE(itk-module)
  
  INCLUDE(${ITK_USE_FILE})

  IF(NOT ITK_LIBRARIES)
    MESSAGE( FATAL_ERROR "ITK libraries are not found!")
  ENDIF(NOT ITK_LIBRARIES)

  IF(NOT ITK_INCLUDE_DIRS)
    MESSAGE( FATAL_ERROR "ITK include directories are not found!")
  ENDIF(NOT ITK_INCLUDE_DIRS	)

  IF(BUILD_SHARED_LIBS AND NOT ITK_BUILD_SHARED)
    message(WARNING "Building Shared library but ITK is linked statically!")
  ENDIF(BUILD_SHARED_LIBS AND NOT ITK_BUILD_SHARED)

  OPTION(MINC4ITK_BUILD_EXAMPLES   "Build minc4itk examples" ON)
  OPTION(MINC4ITK_BUILD_TOOLS      "Build minc4itk-bases tools" ON)

  LINK_DIRECTORIES(${ITK_LIBRARY_DIRS})
  INCLUDE_DIRECTORIES(${ITK_INCLUDE_DIRS} include)
 
  TARGET_LINK_LIBRARIES( ITKIOMINC 
      minc_io
      ${ITK_LIBRARIES}
      itkvnl_algo 
      itkvnl 
      ${VOLUME_IO_LIBRARY}
      ${MINC2_LIBRARIES}
      m 
      z )


  INSTALL(TARGETS ITKIOMINC ${LIBRARY_INSTALL} DESTINATION lib)
  INSTALL(FILES  ${MINC4ITK_HEADERS} DESTINATION include)

  IF(MINC4ITK_BUILD_EXAMPLES)
    add_subdirectory(examples)
  ENDIF(MINC4ITK_BUILD_EXAMPLES)

  IF(MINC4ITK_BUILD_TOOLS)
    add_subdirectory(tools)
  ENDIF(MINC4ITK_BUILD_TOOLS)

  IF(MINC4ITK_BUILD_CONVERTERS)
    add_subdirectory(conversion)
  ENDIF(MINC4ITK_BUILD_CONVERTERS)
ENDIF(itk-module)
