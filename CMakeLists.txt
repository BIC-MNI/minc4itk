# CMakeFiles.txt for the minc4itk 
#
# Vladimir S. FONOV - vladimir.fonov@gmail.com
PROJECT(ITKIOMINC)
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

