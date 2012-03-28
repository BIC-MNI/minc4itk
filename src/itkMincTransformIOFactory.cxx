#include "itkVersion.h"
#include "itkMincTransformIOFactory.h"
#include "itkCreateObjectFunction.h"
#include "itkMincTransformIO.h"
#include "itkTransformFactory.h"
//#include "itkDisplacementFieldTransform.h"

namespace itk
{
  void MincTransformIOFactory::PrintSelf(std::ostream &, Indent) const
  {}

  MincTransformIOFactory::MincTransformIOFactory()
  {
    this->RegisterOverride( "itkTransformIOBase",
                            "itkMincTransformIO",
                            "MINC XFM Transform IO",
                            1,
                            CreateObjectFunction< MincTransformIO >::New() );
  }

  MincTransformIOFactory::~MincTransformIOFactory()
  {}

  const char *
  MincTransformIOFactory::GetITKSourceVersion(void) const
  {
    return ITK_SOURCE_VERSION;
  }

  const char *
  MincTransformIOFactory::GetDescription() const
  {
    return "MINC XFM TransformIO Factory, allows the"
          " loading of Minc XFM transforms into insight";
  }

  // Undocumented API used to register during static initialization.
  // DO NOT CALL DIRECTLY.
  static bool MincTransformIOFactoryHasBeenRegistered;

  void MincTransformIOFactoryRegister__Private(void)
  {
    if( ! MincTransformIOFactoryHasBeenRegistered )
    {
      MincTransformIOFactoryHasBeenRegistered = true;
      MincTransformIOFactory::RegisterOneFactory();
      
      //TransformFactory< DisplacementFieldTransform<double,3> >::RegisterTransform ();
      // register additional transform type
    }
  } 
} // end namespace itk
