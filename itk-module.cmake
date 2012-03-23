set(DOCUMENTATION "This module Implements minc IO file format ...")
 
itk_module(
    ITKIOMINC
  DEPENDS
    ITKCommon
    ITKIOImageBase
  TEST_DEPENDS
    ITKTestKernel
  DESCRIPTION
    "${DOCUMENTATION}"
)
