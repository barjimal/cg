#ifndef COMMON_HPP
#define COMMON_HPP

#include <boost/geometry.hpp>

namespace cg
{

typedef long long int cp_int;
typedef boost::geometry::model::point<double, 3, boost::geometry::cs::cartesian> point3_t;

} // namespace cg

#endif // #ifndef COMMON_HPP