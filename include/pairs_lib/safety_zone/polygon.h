// clang: TomasFormat
#ifndef PAIRS_LIB_POLYGON_H
#define PAIRS_LIB_POLYGON_H

#include <ros/ros.h>
#include <eigen3/Eigen/Eigen>
#include <vector>
#include <geometry_msgs/Point.h>
#include <pairs_lib/safety_zone/line_operations.h>

namespace pairs_lib
{
class Polygon {
public:
  Polygon(const Eigen::MatrixXd vertices);

  bool isPointInside(const double px, const double py);
  bool doesSectionIntersect(const double startX, const double startY, const double endX, const double endY);
  bool isClockwise();
  void inflateSelf(double amount);

  std::vector<geometry_msgs::Point> getPointMessageVector(const double z);

private:
  Eigen::MatrixXd vertices;

public:
  // exceptions
  struct WrongNumberOfVertices : public std::exception
  {
    const char* what() const throw() {
      return "Polygon: wrong number of vertices was supplied!";
    }
  };

  struct WrongNumberOfColumns : public std::exception
  {
    const char* what() const throw() {
      return "Polygon: wrong number of colums, it should be =2!";
    }
  };

  struct ExtraVertices : public std::exception
  {
    const char* what() const throw() {
      return "Polygon: useless vertices detected, polygon methods may break!";
    }
  };
};
}  // namespace pairs_lib

#endif  // PAIRS_LIB_POLYGON_H
