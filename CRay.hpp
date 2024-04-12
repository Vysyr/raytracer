//
//  CRay.hpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#ifndef CRay_hpp
#define CRay_hpp

glm::vec3 norm(const glm::mat3& m, float fx, float fy);


/// \class CRay
/// \brief Class with ray parameters.
///
class CRay{
public:
    glm::vec3 pos; ///< Position of vector origin.
    glm::vec3 dir; ///< Vector direction.
};


#endif /* CRay_hpp */
