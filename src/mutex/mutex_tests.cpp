// clang: MatousFormat

// Include the LKF header
#include <pairs_lib/mutex.h>
#include <iostream>

int main()
{
  {
    std::cout << "get_set_mutexed test -----------------------------------" << std::endl;
    std::mutex mtx;
    bool bvar = true;

    std::cout << "before: " << bvar << std::endl;
    auto [ret] = pairs_lib::get_set_mutexed(mtx,
        std::forward_as_tuple(bvar),
        std::make_tuple(false),
        std::forward_as_tuple(bvar)
        );
    std::cout << "after: " << bvar << ", read: " << ret << std::endl;
  }

  {
    std::cout << "set_mutexed test ---------------------------------------" << std::endl;
    std::mutex mtx;
    bool bvar = true;
    int ivar = 666;

    std::cout << "before: " << bvar << ", " << ivar << std::endl;
    /* pairs_lib::set_mutexed(mtx, bvar, false, ivar, 0); */
    pairs_lib::set_mutexed(mtx, false, bvar);
    std::cout << "after: " << bvar << ", " << ivar << std::endl;
  }


}



