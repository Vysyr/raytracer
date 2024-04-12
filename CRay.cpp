//
//  CRay.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"

glm::vec3 norm(const glm::mat3& m, float fx, float fy) {
    glm::vec3 raydir;
    raydir = m * glm::vec3(fx,fy,1.0f);
    float length = glm::length(raydir);
    for(int i = 0; i < 3; i++){
        raydir[i] = raydir[i] / length;
    }
    return raydir;
}



