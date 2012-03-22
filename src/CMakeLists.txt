set(ITKIOMINC_SRC
     minc_helpers.cxx
     itkMincImageIO.cxx
     itkMincImageIOFactory.cxx
)

# IF(itk-module)

ADD_LIBRARY(ITKIOMINC ${ITKIOMINC_SRC})
TARGET_LINK_LIBRARIES(ITKIOMINC  ${ITKIOImageBase_LIBRARIES} ${EZMINC_LIBRARIES})
itk_module_target(ITKIOMINC)
  
# ELSE(itk-module)
# 
#   add_library(ITKIOMINC ${ITKIOMINC_SRC})
#   
#   target_link_libraries(ITKIOMINC  
#       ${ITK_LIBRARIES}
#       itkvnl_algo
#       itkvnl
#       ${EZMINC_LIBRARIES})
#   
#   INSTALL(TARGETS ITKIOMINC ${LIBRARY_INSTALL} DESTINATION lib)
#   
# ENDIF(itk-module)
