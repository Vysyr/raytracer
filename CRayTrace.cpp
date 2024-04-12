//
//  CRayTrace.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"

#define MAX_RAY_TREE 1
#define MIN_RAY_ENERGY 0.01


/// \fn compPrimaryRayMatrix(CCamera cam, glm::mat3& m)
/// \brief Computation of the projection matrix.
/// \param cam Camera parameters.
/// \param m Output projection matrix.
///
bool CRayTrace::compPrimaryRayMatrix(const CCamera& cam, glm::mat3& m) {
    glm::vec3 look = cam.lookp - cam.eyep;

    glm::vec3 u = glm::cross(cam.up,look);
    u = u/glm::length(u);

    glm::vec3 v = glm::cross(u,look);
    v = v/glm::length(v);

    glm::vec3 o = (look/glm::length(look)) * (0.5f * float(cam.width)/tan(cam.fov/2.0f)) - (0.5f * float(cam.width) * u + 0.5f * float(cam.height) * v);

    for(int i = 0; i < 3; i++) {
        m[0][i] = u[i];
        m[1][i] = v[i];
        m[2][i] = o[i];
    }
            return true;
}


/// \fn rayTrace(CScene scene, CRay& ray, COutput& out)
/// \brief Traces single ray.
/// \param scene Object with all scene components including a camera.
/// \param ray Ray parameter (primary and secondary rays).
/// \param out Object with output color and parameters used in recursion.
///
bool CRayTrace::rayTrace(const CScene& scene, CRay& ray, COutput& out) {
    float tmin = FLT_MAX;
    float EPS = 0.00001;
    bool is_inter = false;
    CObject* hit_obj;
    for(CObject* obj : scene.objectList){
        float t = obj->intersect(ray);
        if(t>EPS && t < tmin) {
            tmin = t;
            is_inter = true;
            hit_obj = obj;
        }
    }
    if(is_inter) {
        glm::vec3 p = ray.pos + tmin * ray.dir;
        for (CLight light : scene.lightList) {
            // compute and add ambient color component
            out.col = out.col + out.energy * light.color * hit_obj->matAmbient;
            //compute normal vector at p
            glm::vec3 n = hit_obj->normal(p);
            //compute vector from p to light position
            glm::vec3 L = glm::normalize(light.pos - n);

            CRay shadow_ray;
            shadow_ray.pos = p;
            shadow_ray.dir = glm::normalize(light.pos - p);

            bool intersection_exists = false;
            float t2min = FLT_MAX;
            for (CObject* o : scene.objectList){
                float t2 = o->intersect(shadow_ray);
                if(t2>EPS && t2 < t2min) {
                    t2min = t2;
                    intersection_exists = true;
                    break;
                }
            }
            if(intersection_exists){
                continue;
            }
            //compute angle between n and vector to light
            float cos_angle = glm::dot(n, L);
            if (hit_obj->isTexture) {
                glm::vec2 uv = hit_obj->textureMapping(n);
                glm::vec3 tex_col = CImage::getTexel(hit_obj->texture, uv.x, uv.y);
                out.col = out.col * tex_col;
            }
            if (cos_angle > EPS) {
                //coumpute and add diffuse color component
                out.col = out.col + out.energy * light.color * hit_obj->matDiffuse * cos_angle;

                //compute half angle vector h
                glm::vec3 V = -ray.dir;
                glm::vec3 h = glm::normalize(L + V);

                //compute angle between n and h
                float cos_beta = glm::dot(n, h);

                if (cos_beta > EPS) {
                    //compute and add specular color component
                    out.col = out.col + out.energy * light.color * hit_obj->matSpecular * pow(cos_beta, hit_obj->matShininess);
                }
            }
            if(hit_obj->reflectance > 0 && out.tree < MAX_RAY_TREE && out.energy > MIN_RAY_ENERGY){
                out.tree++;
                out.energy = out.energy * hit_obj->reflectance;
                CRay secondaryRay = reflectedRay(ray, n, p);
                rayTrace(scene,secondaryRay,out);
            }
        }
    }
    return is_inter;


    /// looks for the closest object along the ray path
    /// returns false if there are no intersection

    /// computes 3D position of the intersection point

    /// computes normal vector at intersection point

    /// for each light source defined in the scene

        /// computes if the intersection point is in the shadows

        /// computes diffuse color component

        /// computes specular color component

    /// adds texture for textured spheres

    /// computes ambient color component

    /// if the surface is reflective

        /// if out.tree >= MAX_RAY_TREE return from function

        /// computes the secondary ray parameters (reflected ray)

        /// recursion
        //   rayTrace(scene, secondary_ray, out);
}


/// \fn reflectedRay(CRay ray, glm::vec3 n, glm::vec3 pos)
/// \brief Computes parameters of the ray reflected at the surface point with given normal vector.
/// \param ray Input ray.
/// \param n Surface normal vector.
/// \param pos Position of reflection point.
/// \return Reflected ray.
///
CRay CRayTrace::reflectedRay(const CRay& ray, const glm::vec3& n, const glm::vec3& pos) {
    CRay reflected_ray;
    reflected_ray.pos = pos;
    glm::vec3 v = ray.dir;
    glm::vec3 r = v - (2.0f * glm::dot(v,n)) * n;
    reflected_ray.dir = glm::normalize(r);
    return reflected_ray;
}

