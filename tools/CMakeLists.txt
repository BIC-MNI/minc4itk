LINK_LIBRARIES( ITKIOMINC )

ADD_EXECUTABLE(itk_convert  itk_convert.cpp)
ADD_EXECUTABLE(itk_resample itk_resample.cpp)

INSTALL(
  TARGETS
    itk_resample
    itk_convert
  DESTINATION 
    bin )
