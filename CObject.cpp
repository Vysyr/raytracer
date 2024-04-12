//
//  CObject.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"
#include "CObject.hpp"
#include <cmath>


/// \fn intersect(CRay ray)
/// \brief Computes intersection between ray and sphere.
/// \param ray Ray parameters.
/// \return Distance from camera position to the closest intersection point, or negative value.
///
float CSphere::intersect(const CRay& ray) {

    glm::vec3 v = ray.pos - this->pos;
    float A = glm::dot(ray.dir,ray.dir);
    float B = 2.0f * glm::dot(v,ray.dir);
    float C = glm::dot(v,v) - this->r * this->r;

    float delta = B * B - 4.0f * A * C;
    if (delta) {
        float t1 = (-B + sqrt(delta)) / (2.0f * A);
        float t2 = (-B - sqrt(delta)) / (2.0f * A);
        if (t1 > 0 && t1 < t2) {
            //std::cout << t1 << "\n";
            return t1;
        } else if (t2 > 0 && t2 <= t1) {
            //std::cout << t2 << "\n";
            return t2;
        }
    }
    return -1.0f;
}


/// Normal vector to the sphere surface
/// \fn normal(glm::vec3 hit_pos)
/// \brief Surface normal vector at the intersection point.
/// \param hit_pos Intersection point.
/// \return Normal vector parameters.
///
glm::vec3 CSphere::normal(const glm::vec3& hit_pos) {
    return glm::normalize(hit_pos - this->pos);
}

/// Computes texture mapping coordinates (u,v).
/// \param normal_vec Normalized normal vector at intersection point.
/// \return (u,v) texture coordinates in <0,1> range.
glm::vec2 CSphere::textureMapping(const glm::vec3& normal_vec) {
    float u = 0.5f + glm::asin(normal_vec.x/M_PI);
    float v = 0.5f - glm::asin(normal_vec.y/M_PI);
    return glm::vec2 {u,v};
}



/// \fn intersect(CRay ray)
/// \brief Computes intersection between triangle and sphere.
/// \param ray Ray parameters.
/// \return Distance from camera position to the closest intersection point, or negative value.
///
float CTriangle::intersect(const CRay& ray) {
    glm::vec3 P;
    if(glm::intersectRayTriangle(ray.pos,ray.dir,v0,v1,v2,P)){
        return glm::distance(P,glm::vec3{0,0,0});
    }
    return -1.0f;
}


/// \fn normal(glm::vec3 hit_pos)
/// \brief Surface normal vector at the intersection point.
/// \param hit_pos Intersection point (not used for triangle).
/// \return Normal vector parameters.
///
glm::vec3 CTriangle::normal(const glm::vec3& hit_pos) {
    glm::vec3 u = this->v1 - this->v0;
    glm::vec3 v = this->v2 - this->v0;
    return glm::normalize(glm::cross(u,v));
}



