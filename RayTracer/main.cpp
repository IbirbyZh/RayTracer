//
//  main.cpp
//  RayTraser
//
//  Created by Шишкин Евгений on 01.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <vector>
#include "/sw/include/cairo/cairo.h"
#include "Polygon.hpp"
#include "Sun.hpp"
#include "Ray.hpp"
#include "KDTree.hpp"
#include <utility>
#include "Reader.hpp"
#include "Scene.hpp"
#include <chrono>

static const double DELTA_CONST = 1E-6;
static const double DEC = 20;

bool findPoint(const Ray& ray,
               Point3D& x, const Polygon*& object, const KDTree& kd)
{
    return kd.crossing(ray, x, object);
}

void rayTrace(const Ray& ray,
              std::vector<Sun>& suns, RGB& rgb, Scene& scene, const KDTree& kd)
{
    rgb = RGB();
    Point3D x;
    const Polygon* object;
    if(findPoint(ray, x, object, kd)){
        LAB lcolor(XYZ(object->color()));
        lcolor.decreaseLight(DEC);
        Point3D delta = object -> normal(x);
        if(delta * ray.rail() > 0){
            delta *= -1;
        }
        delta *= DELTA_CONST;
        for(auto i = suns.begin(); i < suns.end(); ++i){
            Point3D sunPoint;
            double coef = (i->S() - x).normalize() * (object->normal(x));
            coef *= coef;
            if(findPoint(Ray(x + delta, (i->S() - x).normalize()), sunPoint, object, kd)){
                double dist;
                if((x - sunPoint).length2() > (dist = (x - i->S()).length2())){
                    lcolor.increaseLight(DEC * coef * scene.normDist * scene.normDist / dist * i->intensity() / scene.normPower);
                }
            }else{
                double dist = (x - i->S()).length2();
                lcolor.increaseLight(DEC * coef * scene.normDist * scene.normDist / dist * i->intensity() / scene.normPower);
            }
        }
        rgb = RGB(XYZ(lcolor));
    }
}

int main(int argc, const char * argv[]) {
    //FileReader reader("input.rt");
    //FileReader reader("spheres_pure1.rt");
    FileReader reader("gnome_pure.rt");
    std::chrono::time_point<std::chrono::system_clock> start, end;
    Scene scene;
    std::vector<Polygon> objects;
    std::vector<Sun> suns;
    std::cout<<"Start Read\n";
    start = std::chrono::system_clock::now();
    reader.Read(scene, suns, objects);
    end = std::chrono::system_clock::now();
    double l = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
    / static_cast<double>(1000);
    std::cout << "Read time : " << l << "s\n";
    
    start = std::chrono::system_clock::now();
    KDTree kd(objects);
    end = std::chrono::system_clock::now();
    l = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
    / static_cast<double>(1000);
    std::cout << "KD time : " << l << "s\n";
    
    cairo_surface_t *surface;
    cairo_t *cr;
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                         static_cast<int>(RIGHT_MAX / ANTI_ALI),
                                         static_cast<int>(DOWN_MAX / ANTI_ALI));
    cr = cairo_create(surface);
    
    Point3D h, x0 = scene.origin();
    scene.toStart();
    int i = 0;
    start = std::chrono::system_clock::now();
    std::vector<std::vector<RGB>> rgb(RIGHT_MAX, std::vector<RGB>(DOWN_MAX));
    while(scene.next(h)){
        rayTrace(Ray(x0, (h - x0).normalize()), suns, rgb[i % RIGHT_MAX][i / RIGHT_MAX], scene, kd);
        //rayTrace(Ray(x0, (h - x0).normalize()), suns, rgb[RIGHT_MAX - i % RIGHT_MAX - 1][i / RIGHT_MAX], scene, kd);
        //rgb.adecvat();
        //assert(rgb.r() <= 1 && rgb.g() <= 1 && rgb.b() <= 1);
        //assert(rgb.r() >= 0 && rgb.g() >= 0 && rgb.b() >= 0);
        ++i;
        if (i == RIGHT_MAX * DOWN_MAX / 4){
            end = std::chrono::system_clock::now();
            double l = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
            / static_cast<double>(1000);
            std::cout << "25%,  Time: " << l << "s\n";
        }
        if (i == RIGHT_MAX * DOWN_MAX / 2){
            end = std::chrono::system_clock::now();
            double l = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
            / static_cast<double>(1000);
            std::cout << "50%,  Time: " << l << "s\n";
        }
        if (i == RIGHT_MAX * DOWN_MAX / 4 * 3){
            end = std::chrono::system_clock::now();
            double l = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
            / static_cast<double>(1000);
            std::cout << "75%,  Time: " << l << "s\n";
        }
        
    }
    
    for(int i = 0; i < RIGHT_MAX/ANTI_ALI; ++i){
        for(int j = 0; j < DOWN_MAX/ANTI_ALI; ++j){
            Point3D crgb;
            for(int l = 0; l < ANTI_ALI; ++l){
                for(int k = 0; k < ANTI_ALI; ++k){
                    crgb += rgb[ANTI_ALI * i + l][ANTI_ALI * j + k].rgb();
                }
            }
            crgb /= ANTI_ALI * ANTI_ALI;
            cairo_set_source_rgb(cr, crgb.x(), crgb.y(), crgb.z());
            cairo_rectangle (cr, i, j, 1, 1);
            cairo_fill (cr);
        }
    }
    
    end = std::chrono::system_clock::now();
    l = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()
    / static_cast<double>(1000);
    std::cout << "100%, Time: " << l << "s\n";
    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    cairo_rectangle (cr, 0, 0, 10, 10);
    cairo_fill (cr);
    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    cairo_rectangle (cr, 0, 100, 10, 10);
    cairo_fill (cr);
    cairo_surface_write_to_png(surface, "image.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    for(int i = 0; i < objects.size(); ++i){
        objects[i].free();
    }
    return 0;
}
