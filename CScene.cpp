//
//  CScene.cpp
//  rt
//
//  Created by Radoslaw Mantiuk on 22/01/2023.
//

#include "rt.h"

#include<fstream>

/// \fn create(void)
/// \brief Adds components to the scene.
///
void CScene::create(glm::vec3 eyep,glm::vec3 lookp,glm::vec3 up, float fov, int width, int height) {
    
    lightList.clear(); // clears vector with the light data
    objectList.clear(); // clears vector of pointers to objects


    CCamera camm(eyep,lookp,up,width,height,fov);
    cam = camm;

    CSphere* sphere1 = new CSphere({-1,0,3},0.4);
    sphere1->matShininess = 30.0f;
    sphere1->matAmbient = glm::vec3{0,0.1,0};
    sphere1->matDiffuse = glm::vec3{0,0.6,0};
    sphere1->matSpecular = glm::vec3{0.7,0.7,0.7};
    sphere1->isTexture = true;
    sphere1->texture = CImage::createTexture(400,400);
    CSphere* sphere2 = new CSphere({0,0,0},1.6);
    sphere2->matShininess = 30.0f;
    sphere2->matAmbient = glm::vec3{0.1,0,0};
    sphere2->matDiffuse = glm::vec3{0.6,0,0};
    sphere2->matSpecular = glm::vec3{0.7,0.7,0.7};
    sphere2->texture = CImage::createTexture(2000,2000);
    CSphere* sphere3 = new CSphere({-3,-2,-2},0.6);
    sphere3->matShininess = 30.0f;
    sphere3->matAmbient = glm::vec3{0,0,0.1};
    sphere3->matDiffuse = glm::vec3{0,0,0.6};
    sphere3->matSpecular = glm::vec3{0.7,0.7,0.7};
    CTriangle* triangle1 = new CTriangle({{5,5,-5},{-5,5,-5},{-5,-5,-5}});
    triangle1->matDiffuse = glm::vec3{0.4,0.4,0.4};
    triangle1->matAmbient = glm::vec3{0.1,0.1,0.1};
    triangle1->matSpecular = glm::vec3{0,0,0};
    triangle1->matShininess = 0.0f;
    triangle1->reflectance = 1.0f;
    CTriangle* triangle2 = new CTriangle({{5,5,-5},{-5,-5,-5},{5,-5,-5}});
    triangle2->matDiffuse = glm::vec3{0.4,0.4,0.4};
    triangle2->matAmbient = glm::vec3{0.1,0.1,0.1};
    triangle2->matSpecular = glm::vec3{0,0,0};
    triangle2->matShininess = 0.0f;
    triangle2->reflectance = 1.0f;
    CLight light(glm::vec3{-3,-2,8});
    light.color = {0.6,0.6,0.6};
    CLight light2(glm::vec3{5,-2,8});
    light2.color = {0.3,0.3,0.3};
    objectList.push_back(sphere1);
    objectList.push_back(sphere2);
    objectList.push_back(sphere3);
    objectList.push_back(triangle1);
    objectList.push_back(triangle2);
    lightList.push_back(light);
    lightList.push_back(light2);
//    eyep = glm::vec3(2,5,10);
//    lookp = glm::vec3(-2,1,0);
//    CCamera cam2(eyep,lookp,up,width,height,fov);
//    cam = cam2;
//
    // add camera, light sources, and objects


}

void CScene::create2(glm::vec3 eyep,glm::vec3 lookp,glm::vec3 up, float fov, int width, int height) {
    lightList.clear();
    objectList.clear();

    CCamera camm(eyep,lookp,up,width,height,fov);
    cam = camm;


}



void CScene::createT(glm::vec3 eyep,glm::vec3 lookp,glm::vec3 up, float fov, int width, int height) {

    lightList.clear(); // clears vector with the light data
    objectList.clear(); // clears vector of pointers to objects


    CCamera camm(eyep,lookp,up,width,height,fov);
    cam = camm;

    CTriangle* triangle = new CTriangle(glm::vec3{3,3,-5},glm::vec3{-3,3,-10},glm::vec3{-3,-3,-8});
    objectList.push_back(triangle);
//    eyep = glm::vec3(2,5,10);
//    lookp = glm::vec3(-2,1,0);
//    CCamera cam2(eyep,lookp,up,width,height,fov);
//    cam = cam2;
//
    // add camera, light sources, and objects


}


