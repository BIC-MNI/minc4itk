# CMakeFiles.txt for the minc4itk module
#
# Vladimir S. FONOV - vladimir.fonov@gmail.com
PROJECT( ITKIOMINC )

# either compile as ITKv4 module or a stand-alone library for ITKv3 or ITKv4

IF(NOT MINC_TOOLKIT_BUILD)

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
  
ELSE( NOT MINC_TOOLKIT_BUILD)

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
    include/itkMincTransformIOFactory.h
    include/itkMincTransformIO.h
    include/itkMincGeneralTransform.h
    include/itkMincHelpers.h
  )

  IF( ITK_VERSION_MAJOR VERSION_EQUAL 4 )
    SET(ITKIOMINC_SRC
      ${ITKIOMINC_SRC}
      src/itkMincTransformIO.cxx
      src/itkMincTransformIOFactory.cxx
    )
    
    SET(ITKIOMINC_HEADER
      ${ITKIOMINC_HEADER}
      include/itkMincImageIOFactory.h
    )
  ENDIF(ITK_VERSION_MAJOR VERSION_EQUAL 4)

  INCLUDE_DIRECTORIES( ${MINC2_INCLUDE_DIRS} include )
  LINK_DIRECTORIES( ${MINC2_LIBRARY_DIRS} )

  ADD_LIBRARY(ITKIOMINC ${ITKIOMINC_SRC} ${ITKIOMINC_HEADER})

  TARGET_LINK_LIBRARIES(ITKIOMINC
    minc_io
    ${ITK_LIBRARIES}
    itkvnl_algo 
    itkvnl 
    volume_io2
    minc2
    m 
    z  )

  INSTALL(FILES ${ITKIOMINC_HEADER}
    DESTINATION include)

  INSTALL(TARGETS 
    ITKIOMINC  ${LIBRARY_INSTALL} 
    DESTINATION lib)

  ADD_EXECUTABLE(itk_convert  tools/itk_convert.cpp)
  TARGET_LINK_LIBRARIES(itk_convert ITKIOMINC ${VOLUME_IO_LIBRARY} )

  ADD_EXECUTABLE(itk_resample tools/itk_resample.cpp)
  TARGET_LINK_LIBRARIES(itk_resample ITKIOMINC ${VOLUME_IO_LIBRARY} )

  INSTALL(
    TARGETS
      itk_resample
      itk_convert
    DESTINATION 
      bin )

  SET(MINC4ITK_LIBRARY ITKIOMINC)

ENDIF(NOT MINC_TOOLKIT_BUILD)

