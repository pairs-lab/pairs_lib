// clang: MatousFormat
#include <pairs_lib/geometry/cyclic.h>

namespace pairs_lib
{
  namespace geometry
  {

    // to ensure these classes are generated
    template struct cyclic<double, radians>;
    template struct cyclic<double, sradians>;
    template struct cyclic<double, degrees>;
    template struct cyclic<double, sdegrees>;

  } // namespace geometry
} // namespace pairs_lib
