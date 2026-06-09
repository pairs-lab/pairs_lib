// clang: TomasFormat
#ifndef PAIRS_LIB_SAFETYZONE_H
#define PAIRS_LIB_SAFETYZONE_H

#include <pairs_lib/safety_zone/polygon.h>
#include <visualization_msgs/Marker.h>
#include <eigen3/Eigen/Eigen>
#include <vector>

namespace pairs_lib
{
class SafetyZone {
public:
  SafetyZone(Polygon outerBorder);
  ~SafetyZone();

  SafetyZone(const Eigen::MatrixXd& outerBorderMatrix);

  bool isPointValid(const double px, const double py);
  bool isPathValid(const double p1x, const double p1y, const double p2x, const double p2y);

  Polygon getBorder();

private:
  Polygon* outerBorder;

public:
  struct BorderError : public std::exception
  {
    const char* what() const throw() {
      return "SafeZone: Wrong configuration for the border";
    }
  };
};
}  // namespace pairs_lib

#endif  // PAIRS_LIB_SAFETYZONE_H
