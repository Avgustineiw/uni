///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief      Main module for Problem: Calculate the Area of a Circle
/// \version    0.1.0
/// \date       30.01.2024
///
/// TASK DESCRIPTION
///
/// Write a function `double circleArea(double radius)` that calculates and 
/// returns the area of a circle given its radius.
///
///////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>

double circleArea(double radius)
{
  double area;
  area = (radius * radius) * acos(-1);

  return area;
}

int main() 
{
  double res;
  int n;
  
  std::cin >> n;

  res = circleArea(n);

  std::cout << res;

  return 0;
}
