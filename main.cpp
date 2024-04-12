
#include <iostream>


#include "rt.h"

extern void draw_robot();
extern void draw_triangles();
extern void draw_images();
extern void draw_spheres();
extern void draw_triangle();
extern void reflection_test();

///
int main (int argc, char * const argv[]) {

    //draw_triangles();
    //draw_robot();
    //draw_images();
    draw_spheres();
    //reflection_test();
    //draw_triangle();
    return 0;
}


/// Draws two trianges
void draw_triangles() {

    CImage img(1000, 1000);
    
    glm::vec3 color1(0.9,0.1,0.1); // red
    glm::vec3 color2(0.1,0.9,0.1); // green
    
    // draw circle
    glm::vec3 pp(0.0,0.0,1.0);
    float radius = 0.1f;
    img.drawCircle(pp, radius, color1);
    
    // triangle vertices
    glm::vec3 pp0(0.4, 0.3, 1);
    glm::vec3 pp1(-0.4, 0.3, 1);
    glm::vec3 pp2(0.4, -0.3, 1);
    
    // draws triangle in 2D
    img.drawLine(pp0, pp1, color1);
    img.drawLine(pp1, pp2, color1);
    img.drawLine(pp2, pp0, color1);
    
    // translation
    float tX = 0.2f; // OX translation
    float tY = 0.1f; // OY translation
    glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix
    PRINT_MAT3(mTrans);

    // translation of vertices
    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;

    // draws triangle after translation
    img.drawLine(pp0, pp1, color2);
    img.drawLine(pp1, pp2, color2);
    img.drawLine(pp2, pp0, color2);

    img.save("robot.png");
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();

}

void rotate_and_scale(glm::vec3 *pp0, float rad, float scalex, float scaley)
{
    pp0->x = pp0->x * scalex;
    pp0->y = pp0->y * scaley;
    float x = pp0->x;
    float y = pp0->y;
    pp0->x = cos(rad) * x - sin(rad) * y;
    pp0->y = sin(rad) * x + cos(rad) * y;
}

void drawRectangle(CImage *img, glm::vec3 pp0, glm::vec3 pp1, glm::vec3 pp2, glm::vec3 pp3, glm::vec3 color, glm::mat3x3 mTrans, float scalex, float scaley, float radians)
{
    rotate_and_scale(&pp0,radians,scalex, scaley);
    rotate_and_scale(&pp1,radians,scalex, scaley);
    rotate_and_scale(&pp2,radians,scalex,scaley);
    rotate_and_scale(&pp3,radians,scalex,scaley);

    pp0 = mTrans * pp0;
    pp1 = mTrans * pp1;
    pp2 = mTrans * pp2;
    pp3 = mTrans * pp3;

    img->drawLine(pp0,pp1,color);
    img->drawLine(pp0,pp2,color);
    img->drawLine(pp1,pp3,color);
    img->drawLine(pp3,pp2,color);

}

/// Draws robot.
void draw_robot() {
    CImage img(600, 600);

    glm::vec3 color1(0.3,0.6,0.6); // red

    glm::vec3 pp0(0.15,0.25,1);//RU
    glm::vec3 pp1(-0.15,0.25,1);//LU
    glm::vec3 pp2(0.15,-0.25,1);//RL
    glm::vec3 pp3(-0.15,-0.25,1);//LL


    float tX = 0.0f; // OX translation
    float tY = 0.0f; // OY translation
    glm::mat3x3 mTrans {{1,0,0}, {0,1,0}, {tX,tY,1}}; // translation matrix
    float sizex = 1.0f;
    float sizey = 1.0f;
    float radians = 0.0f;
    //brzuszek
    drawRectangle(&img,pp0,pp1,pp2,pp3,color1,mTrans,sizex, sizey,radians);

    //prawa reka
    tX = -0.4f;
    tY = 0.05f;
    mTrans = {{1,0,0},{0,1,0},{tX,tY,1}};
    sizex = 0.4f;
    sizey - 0.5f;
    radians = 100.0f;
    drawRectangle(&img,pp0,pp1,pp2,pp3,color1,mTrans,sizex,sizey,radians);

    //lewa reka
    tX = 0.4f;
    tY = 0.05f;
    mTrans = {{1,0,0},{0,1,0},{tX,tY,1}};
    sizex = 0.4f;
    sizey - 0.5f;
    radians = -100.0f;
    drawRectangle(&img,pp0,pp1,pp2,pp3,color1,mTrans,sizex,sizey,radians);

    //prawa noga
    tX = -0.2f;
    tY = -0.6f;
    mTrans = {{1,0,0},{0,1,0},{tX,tY,1}};
    sizex = 0.45f;
    sizey - 0.55f;
    radians = 50.0f;
    drawRectangle(&img,pp0,pp1,pp2,pp3,color1,mTrans,sizex,sizey,radians);

    //lewa noga
    tX = 0.2f;
    tY = -0.6f;
    mTrans = {{1,0,0},{0,1,0},{tX,tY,1}};
    sizex = 0.45f;
    sizey - 0.55f;
    radians = -50.0f;
    drawRectangle(&img,pp0,pp1,pp2,pp3,color1,mTrans,sizex,sizey,radians);

    // glowa
    glm::vec3 pp(0.0,0.45,1.0);
    float radius = 0.12f;
    img.drawCircle(pp, radius, color1);

    img.save("robot.png");
    cv::imshow("ROBOT", img.getImage());
    cv::waitKey();
}

void draw_images() {
    glm::vec3 eyep(0,0,10);
    glm::vec3 lookp(0,0,0);
    glm::vec3 up(0,1,0);
    float fov = 50.0f * (3.14f / 180.0f);
    int width = 500;
    int height = 400;
    CScene scene;
    scene.create(eyep,lookp,up,fov,width,height); // defines sample scene parameters
    if (!scene.cam.width) {
        std::cout << "WARNING: scene not defined" << std::endl;
        return;
    }
    CRayTrace rt;
    CRay ray;
    COutput results;

    /// computes primary ray matrix
    glm::mat3 ray_matrix;
    CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);
    std::cout << "Camera projection matrix:" << std::endl;
    PRINT_MAT3(ray_matrix);

    /// computes ray direction for sample pixel positions

    float fxes[] = {0.5f * float(scene.cam.width) - 0.5f,0.5f,0.5f * float(scene.cam.width) - 0.5f,0.5f,float(scene.cam.width) - 0.5f  };
    float fyes[] = {0.5f * float(scene.cam.height) - 0.5f,0.5f,0.5f,0.5f * float(scene.cam.height) - 0.5f,float(scene.cam.height) - 0.5f };

    std::cout << "Promienie pierwotne:\n";
    for(int i = 0; i < 5; i++) {
        float fx = fxes[i];
        float fy = fyes[i];
        glm::vec3 r = norm(ray_matrix, fx, fy);
        std::cout << "\n" << r[0] << " " << r[1] << " " << r[2];
    }


    /// creates raster image object
    CImage image(scene.cam.width, scene.cam.height);
    CImage image2(scene.cam.width, scene.cam.height);
    CImage image3(scene.cam.width, scene.cam.height);

    // main loop

    for (int j = 0; j < scene.cam.height; j++) {
        for (int i = 0; i < scene.cam.width; i++) {
// position of the image point
            float fx = (float) i + 0.5f;
            float fy = (float) j + 0.5f;

            /// primary ray
            /// ...
            ray.pos = scene.cam.eyep;
            ray.dir = norm(ray_matrix, fx, fy);
            /// background color
            results.col = {0, 0, 0};
            /// secondary ray counter
            results.tree = 0;
            /// ray energy
            results.energy = 1.0f;

            /// rendering
            rt.rayTrace(scene, ray, results);

            /// handles pixel over-saturation
            if (results.col.x > 1 || results.col.y > 1 || results.col.z > 1) {
                results.col = {1, 1, 1};
            }

            /// writes pixel to output image
            glm::vec3 rgb(0.0f, 0.0f, 0.0f);
            rgb.x = (ray.dir.x + 1.0f) / 2.0f;
            glm::vec3 rgb2(0.0f, 0.0f, 0.0f);
            rgb2.y = (ray.dir.y + 1.0f) / 2.0f;
            glm::vec3 rgb3(0.0f, 0.0f, 0.0f);
            rgb3.z = (ray.dir.z + 1.0f) / 2.0f;
            //std::cout << "\n\n" << ray.dir.x;
            image.setPixel(i, j, rgb);
            image2.setPixel(i, j, rgb2);
            image3.setPixel(i, j, rgb3);

        }
    }

    // writes image to disk file with gamma correction
   // image.save("output.png", true);

    cv::imshow("imagered", image.getImage());
    cv::imshow("imagegreen", image2.getImage());
    cv::imshow("imageblack", image3.getImage());

    cv::waitKey();

    std::cout << std::endl << std::endl;
}

void draw_spheres(){
    glm::vec3 eyep(0,-4,10);
    glm::vec3 lookp(0,0,0);
    glm::vec3 up(0,1,0);
    float fov = 50.0f * (3.14f / 180.0f);
    int width = 500;
    int height = 400;
    CScene scene;
    scene.create(eyep,lookp,up,fov,width,height); // defines sample scene parameters
    if (!scene.cam.width) {
        std::cout << "WARNING: scene not defined" << std::endl;
        return;
    }
    CRayTrace rt;
    CRay ray;
    COutput results;

    /// computes primary ray matrix
    glm::mat3 ray_matrix;
    CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);

    /// computes ray direction for sample pixel positions

    /// creates raster image object
    CImage image(scene.cam.width, scene.cam.height);

    // main loop

    for (int j = 0; j < scene.cam.height; j++) {
        for (int i = 0; i < scene.cam.width; i++) {
// position of the image point
            float fx = (float) i + 0.5f;
            float fy = (float) j + 0.5f;

            /// primary ray
            /// ...
            ray.pos = scene.cam.eyep;
            ray.dir = norm(ray_matrix, fx, fy);
            /// background color
            results.col = {0, 0, 0};
            /// secondary ray counter
            results.tree = 0;
            /// ray energy
            results.energy = 1.0f;

            /// rendering
            rt.rayTrace(scene, ray, results);

            /// handles pixel over-saturation
//            if (results.col.x > 1 || results.col.y > 1 || results.col.z > 1) {
//                results.col = {1, 1, 1};
//            }

            /// writes pixel to output image
            //std::cout << "\n\n" << ray.dir.x;
            image.setPixel(i, j, results.col);

        }
    }

    // writes image to disk file with gamma correction
    // image.save("output.png", true);

    cv::imshow("img", image.getImage());

    cv::waitKey();

    std::cout << std::endl << std::endl;
}

void draw_triangle(){
    glm::vec3 eyep(0,0,10);
    glm::vec3 lookp(0,0,0);
    glm::vec3 up(0,1,0);
    float fov = 50.0f * (3.14f / 180.0f);
    int width = 500;
    int height = 400;
    CScene scene;
    scene.createT(eyep,lookp,up,fov,width,height); // defines sample scene parameters
    if (!scene.cam.width) {
        std::cout << "WARNING: scene not defined" << std::endl;
        return;
    }
    CRayTrace rt;
    CRay ray;
    COutput results;

    /// computes primary ray matrix
    glm::mat3 ray_matrix;
    CRayTrace::compPrimaryRayMatrix(scene.cam, ray_matrix);

    /// computes ray direction for sample pixel positions

    /// creates raster image object
    CImage image(scene.cam.width, scene.cam.height);

    // main loop

    for (int j = 0; j < scene.cam.height; j++) {
        for (int i = 0; i < scene.cam.width; i++) {
// position of the image point
            float fx = (float) i + 0.5f;
            float fy = (float) j + 0.5f;

            /// primary ray
            /// ...
            ray.pos = scene.cam.eyep;
            ray.dir = norm(ray_matrix, fx, fy);
            /// background color
            results.col = {0, 0, 0};
            /// secondary ray counter
            results.tree = 0;
            /// ray energy
            results.energy = 1.0f;

            /// rendering
            rt.rayTrace(scene, ray, results);

            /// handles pixel over-saturation
//            if (results.col.x > 1 || results.col.y > 1 || results.col.z > 1) {
//                results.col = {1, 1, 1};
//            }

            /// writes pixel to output image
            //std::cout << "\n\n" << ray.dir.x;
            image.setPixel(i, j, results.col);

        }
    }

    // writes image to disk file with gamma correction
    // image.save("output.png", true);

    cv::imshow("img", image.getImage());

    cv::waitKey();

    std::cout << std::endl << std::endl;
}

void reflection_test(){
    CRay ray;
    ray.pos = glm::vec3{0,0,0};
    ray.dir = glm::vec3{0.5f,0.5f,0};
    glm::vec3 n = glm::vec3{0,1.0,0};
    glm::vec3 pos = glm::vec3{0,0,0};
    CRay ref = CRayTrace::reflectedRay(ray,n,pos);
    std::cout<<ref.pos.x<<" "<<ref.pos.y<<" "<<ref.pos.z<<"\n";
    std::cout<<ref.dir.x<<" "<<ref.dir.y<<" "<<ref.dir.z;
}
