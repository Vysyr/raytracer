//
//  CScene.hpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#ifndef CScene_hpp
#define CScene_hpp


/// \class CCamera
/// \brief Class with camera parameters.
///
class CCamera {
public:
    int width; ///< Horizontal resolution in pixels.
    int height; ///< Vertical resolution in pixels.
    float fov; ///< Field-of-view (<0,180) range)
    glm::vec3 eyep; ///< Camera position.
    glm::vec3 lookp; ///< Camera target point.
    glm::vec3 up; ///< Camera orientation.

    CCamera(glm::vec3 e, glm::vec3 l, glm::vec3 u, int w, int h, float f) {
        width = w;
        height = h;
        fov = f;
        eyep = e;
        lookp = l;
        up = u;
    }

    CCamera() {
        width = 0; ///< Horizontal resolution in pixels.
        height = 0; ///< Vertical resolution in pixels.
        fov = 0; ///< Field-of-view (<0,180) range)
        eyep = {0,0,0}; ///< Camera position.
        lookp = {0,0,0}; ///< Camera target point.
        up = {0,0,0}; ///< Camera orientation.
    }
};


/// \class CLight
/// \brief Class with light source parameters.
///
class CLight  {
public:
    glm::vec3 pos; ///< Light position.
    glm::vec3 color; ///< Light color.
    
    CLight() {
        color = {1,1,1};
    }
    
    explicit CLight(const glm::vec3& pos) {
        this->pos = pos;
    }
};


/// \class CScene
/// \brief Container for the scene components.
///
class CScene {
public:
    CCamera cam; ///< Camera object.
    std::vector<CObject*> objectList; ///< List of geometric objects.
    std::vector<CLight> lightList; ///< List of the light sources.
    
public:
    void create(glm::vec3 eyep,glm::vec3 lookp,glm::vec3 up, float fov, int width, int height);

    void createT(glm::vec3 eyep, glm::vec3 lookp, glm::vec3 up, float fov, int width, int height);

    void create2(glm::vec3 eyep,glm::vec3 lookp,glm::vec3 up, float fov, int width, int height);
};



#endif /* CScene_hpp */
