#include <pairs_lib/utils.h>

namespace pairs_lib
{

  AtomicScopeFlag::AtomicScopeFlag(std::atomic<bool>& in) : variable(in)
  {
    variable = true;
  }

  AtomicScopeFlag::~AtomicScopeFlag()
  {
    variable = false;
  }

} // namespace pairs_lib
