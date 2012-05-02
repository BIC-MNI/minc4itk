# CMakeFiles.txt for the minc4itk module
#
# Vladimir S. FONOV - vladimir.fonov@gmail.com
PROJECT( ITKIOMINC )

cmake_minimum_required(VERSION 2.6)

# either compile as ITKv4 module or a stand-alone library for ITKv3 or ITKv4
SET(ITK_MODULE_BUILD OFF)
SET(MINC4ITK_EXTERNALLY_CONFIGURED OFF)



IF(MINC_TOOLKIT_BUILD)
 SET(ITK_MODULE_BUILD OFF)
 SET(MINC4ITK_EXTERNALLY_CONFIGURED ON)
ENDIF(MINC_TOOLKIT_BUILD)

IF(ITK_MODULE_BUILD)

  FIND_PACKAGE( MINC2 REQUIRED )
  INCLUDE_DIRECTORIES(${MINC2_INCLUDE_DIRS})
  LINK_DIRECTORIES(${MINC2_LIBRARY_DIRS})

  SET(MINC4ITK_HEADERS 
    include/itkMincImageIOFactory.h
    include/itkMincImageIO.h
    include/itkMincGeneralTransform.h
    include/itkMincHelpers.h
    include/itkMincTransformIOFactory.h
    include/itkMincTransformIO.h
  )

  SET(ITKIOMINC_LIBRARIES ITKIOMINC ${VOLUME_IO_LIBRARIES} ${EZMINC_LIBRARIES})

  itk_module_impl()
  add_subdirectory(tools)
  
ELSE( ITK_MODULE_BUILD )

  IF(NOT MINC4ITK_EXTERNALLY_CONFIGURED)
   FIND_PACKAGE( MINC2 REQUIRED )
   INCLUDE_DIRECTORIES(${MINC2_INCLUDE_DIRS})
   LINK_DIRECTORIES(${MINC2_LIBRARY_DIRS})
   FIND_PACKAGE( ITK REQUIRED )
  ENDIF(NOT MINC4ITK_EXTERNALLY_CONFIGURED)

  # Add include directories needed to use ITK.
  INCLUDE_DIRECTORIES(BEFORE ${ITK_INCLUDE_DIRS})

  # Add link directories needed to use ITK.
  LINK_DIRECTORIES( ${ITK_LIBRARY_DIRS} )

  SET( ITKIOMINC_SRC
      src/itkMincHelpers.cxx
      src/itkMincImageIO.cxx
      src/itkMincImageIOFactory.cxx
      src/itkMincHelpers.cxx
  )

  SET( ITKIOMINC_HEADER
    include/itkMincImageIO.h
    include/itkMincTransformIO.h
    include/itkMincGeneralTransform.h
    include/itkMincHelpers.h
    include/itkMincImageIOFactory.h
  )

  IF( ITK_VERSION_MAJOR VERSION_EQUAL 4 )
    SET(ITKIOMINC_SRC
      ${ITKIOMINC_SRC}
      src/itkMincTransformIO.cxx
      src/itkMincTransformIOFactory.cxx
    )
    
    SET(ITKIOMINC_HEADER
      ${ITKIOMINC_HEADER}
      include/itkMincTransformIOFactory.h
    )
  ENDIF(ITK_VERSION_MAJOR VERSION_EQUAL 4)

  INCLUDE_DIRECTORIES( ${MINC2_INCLUDE_DIRS} include )
  LINK_DIRECTORIES( ${MINC2_LIBRARY_DIRS} )

  ADD_LIBRARY(ITKIOMINC ${ITKIOMINC_SRC} ${ITKIOMINC_HEADER})

  TARGET_LINK_LIBRARIES(ITKIOMINC
    ${EZMINC_LIBRARIES}
    ${VOLUME_IO_LIBRARIES}
    ${ITK_LIBRARIES}
    ${MINC2_LIBRARIES}
   )

  INSTALL(FILES ${ITKIOMINC_HEADER}
    DESTINATION include)

  INSTALL(TARGETS 
    ITKIOMINC  ${LIBRARY_INSTALL} 
    DESTINATION lib)

  ADD_EXECUTABLE(itk_convert  tools/itk_convert.cpp)
  TARGET_LINK_LIBRARIES(itk_convert ITKIOMINC )

  ADD_EXECUTABLE(itk_resample tools/itk_resample.cpp)
  TARGET_LINK_LIBRARIES(itk_resample ITKIOMINC  )

  INSTALL(
    TARGETS
      itk_resample
      itk_convert
    DESTINATION 
      bin )

  SET(MINC4ITK_LIBRARY ITKIOMINC)
  
  set(MINC4ITK_INCLUDE_DIRS_CONFIG   
      ${MINC2_INCLUDE_DIRS} 
      ${CMAKE_CURRENT_SOURCE_DIR}/Include 
      ${CMAKE_CURRENT_SOURCE_DIR}/GLUT_windows/Include )

  set(MINC4ITK_LIBRARY_DIRS_CONFIG   ${CMAKE_CURRENT_BINARY_DIR} ${MINC2_LIBRARY_DIRS} )
  set(MINC4ITK_LIBRARIES_CONFIG      
    ITKIOMINC     
    ${EZMINC_LIBRARIES}
    ${VOLUME_IO_LIBRARIES}
    ${ITK_LIBRARIES}
    ${MINC2_LIBRARIES} )

  configure_file(src/MINC4ITKConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MINC4ITKConfig.cmake @ONLY )

  # config for install dir
  set(MINC4ITK_INCLUDE_DIRS_CONFIG  
      ${CMAKE_INSTALL_PREFIX}/include/bicgl/OpenGL_graphics/Include 
      ${CMAKE_INSTALL_PREFIX}/include/bicgl/Include 
      ${CMAKE_INSTALL_PREFIX}/include/bicgl/GLUT_windows/Include )

  set(MINC4ITK_LIBRARY_DIRS_CONFIG  ${CMAKE_INSTALL_PREFIX}/lib ${MINC2_LIBRARY_DIRS})
  set(MINC4ITK_LIBRARIES_CONFIG     
      ITKIOMINC
      ${EZMINC_LIBRARIES}
      ${VOLUME_IO_LIBRARIES}
      ${ITK_LIBRARIES}
      ${MINC2_LIBRARIES} )

  configure_file(src/MINC4ITKConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/MINC4ITKConfig.cmake @ONLY )

  INSTALL(FILES 
      ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/MINC4ITKConfig.cmake
    DESTINATION lib
    COMPONENT Development)
  

ENDIF(ITK_MODULE_BUILD)

