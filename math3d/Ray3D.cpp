#include "Ray3D.h"
using namespace Math3D;

Real Ray3D::closestPoint(const Point3D& in, Point3D& out) const
{
  return Line3D::closestPoint(in,out,0,Inf);
}

Real Ray3D::distance(const Point3D& pt) const
{
  Point3D closest;
  closestPoint(pt,closest);
  return (pt-closest).norm();
}

bool Ray3D::intersects(const Line3D& l, Real* t, Real* u, Real epsilon) const
{
  if(Line3D::intersects(l,t,u,epsilon)) {
    if(*t < -epsilon) return false;
    return true;
  }
  return false;
}

bool Ray3D::intersects(const Ray3D& r, Real* t, Real* u, Real epsilon) const
{
  if(Line3D::intersects(r,t,u,epsilon)) {
    if(*t < -epsilon || *u < -epsilon) return false;
    return true;
  }
  return false;
}

bool Ray3D::intersects(const AABB3D& bb, Real& tmin, Real& tmax) const
{
  if(Line3D::intersects(bb,tmin,tmax)) {
    if(tmin < 0) {
      if(tmax < 0) return false;
      tmin = 0;
    }
    return true;
  }
  return false;
}

void Ray3D::closestPoint(const Line3D& l,Real& t,Real& u) const
{
  Line3D::closestPoint(l,t,u);
  if(t < 0) {
    t=0;
    u=l.closestPointParameter(source);
  }
}

void Ray3D::closestPoint(const Ray3D& r,Real& t,Real& u) const
{
  Line3D::closestPoint(r,t,u);
  if(t < 0) {
    t=0;
    u=r.closestPointParameter(source);
  }
  if(u < 0) {
    u=0;
    t=r.closestPointParameter(r.source);
  }
  if(t < 0) t=0;
}

Real Ray3D::distance(const AABB3D& bb) const
{
  Real tclosest;
  Vector3 bbclosest;
  return distance(bb,tclosest,bbclosest);
}

Real Ray3D::distance(const AABB3D& bb, Real& tclosest, Vector3& bbclosest) const
{
  Real d = Line3D::distance(bb,tclosest,bbclosest);
  if(tclosest >= 0) return d;
  else {
    tclosest = 0;
    return bb.distance(source,bbclosest);
  }
}
