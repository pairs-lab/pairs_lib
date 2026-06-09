/**  \file
 *   \author Daniel Hert - hertdani@fel.cvut.cz
 */
#ifndef NOTCH_FILTER_H
#define NOTCH_FILTER_H

#include <Eigen/Dense>
#include <iostream>
#include <memory>

#include <pairs_lib/iir_filter.h>

namespace pairs_lib
{

  class NotchFilter
  {

  public:
    NotchFilter(const double& sample_rate, const double& frequency_in, const double& bandwidth_in);

    double iterate(double& sample_in);

  private:
    std::unique_ptr<pairs_lib::IirFilter> filter;
  };

} // namespace pairs_lib

#endif
