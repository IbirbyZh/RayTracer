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
#include "IObject.hpp"
#include "Sun.hpp"

static const int DPI = 50;
static const double MAX_DISTANCE = 1E9;
static const double MAGIC_CONST = 500;
static const double DELTA_CONST = 1E-3;

bool findPoint(const Point3D& x0, const Point3D& a, std::vector<IObject*> objects,
               Point3D& x, IObject*& object)
{
    double dist = MAX_DISTANCE;
    bool ans = false;
    for(auto i = objects.begin(); i < objects.end(); ++i){
        Point3D xtemp;
        if((*i)->crossing(x0, a, xtemp)){
            double temp;
            if(dist > (temp =(x0 - xtemp).length())){
                dist = std::move(temp);
                object = (*i);
                x = std::move(xtemp);
                ans = true;
            }
        }
    }
    return ans;
}

void rayTrace(const Point3D& x0, const Point3D& a, std::vector<IObject*> objects,
              std::vector<Sun> suns, RGB& rgb)
{
    rgb = RGB();
    Point3D x;
    IObject* object;
    if(findPoint(x0, a, objects, x, object)){
        LAB lcolor(XYZ(object->color()));
        lcolor.l(10);
        Point3D delta = object -> normal(x);
        if(delta * a > 0){
            delta *= -1;
        }
        delta *= DELTA_CONST;
        for(auto i = suns.begin(); i < suns.end(); ++i){
            Point3D sunPoint;
            double coef = (i->S() - x).normalize() * (object->normal(x));
            coef *= coef;
            if(findPoint(x + delta, (i->S() - x).normalize(), objects, sunPoint, object)){
                double dist;
                if((x - sunPoint).length2() > (dist = (x - i->S()).length2())){                    lcolor.increaseLight(coef * MAGIC_CONST / dist * i->intensity());
                }
            }else{
                double dist = (x - i->S()).length2();
                lcolor.increaseLight(coef * MAGIC_CONST / dist * i->intensity());
            }
        }
        rgb = RGB(XYZ(lcolor));
    }
}

int main(int argc, const char * argv[]) {
    /*
    srand(42);
    std::vector<float> r,g,b;
    int n = 10;
    for(int i = 0; i < n; ++i){
        r.push_back(static_cast<float>((rand() % 256)) / 256);
        g.push_back(static_cast<float>((rand() % 256)) / 256);
        b.push_back(static_cast<float>((rand() % 256)) / 256);
    }
    */
        /*
    for(int i = 0; i < W; i += 5){
        for(int j = 0; j < H; j += 5){
            int ind = (i + j) % n;
            cairo_set_source_rgb(cr, r[ind], g[ind], b[ind]);
            cairo_rectangle (cr, i, j, 1, 1);
            cairo_fill (cr);
        }
    }
    */
    
    
    freopen("input.txt", "r", stdin);
    double height, width;
    int n, m;
    double x, y, z;
    scanf("%lf%lf%lf", &x, &y, &z);
    Point3D x0(std::move(x), std::move(y), std::move(z));
    scanf("%lf%lf%lf", &x, &y, &z);
    Point3D a(std::move(x), std::move(y), std::move(z));
    a -= x0;
    Point3D w = a % Point3D(0, 0, 1);
    w.normalize();
    Point3D h = a % w;
    h.normalize();
    scanf("%lf%lf%d%d", &width, &height, &n, &m);
    std::vector<IObject*> objects(n, NULL);
    std::vector<Sun> suns;
    for(int i = 0; i < n; ++i){
        int type;
        double r, g, b, reflect, refract;
        scanf("%d%lf%lf%lf%lf%lf", &type, &r, &g, &b, &reflect, &refract);
        if(type == triangle){
            double x1, y1, z1, x2, y2, z2, x3, y3, z3;
            scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf",
                  &x1, &y1, &z1, &x2, &y2, &z2, &x3, &y3, &z3);
            objects[i] = createObject(triangle, r, g, b, reflect, refract,
                                      x1, y1, z1, x2, y2, z2, x3, y3, z3);
        }
        if(type == sphere){
            double x1, y1, z1, rad;
            scanf("%lf%lf%lf%lf",
                  &x1, &y1, &z1, &rad);
            objects[i] = createObject(sphere, r, g, b, reflect, refract,
                                      x1, y1, z1, rad);
        }
        if(type == quadrangle){
            double x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
            scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",
                  &x1, &y1, &z1, &x2, &y2, &z2, &x3, &y3, &z3, &x4, &y4, &z4);
            objects[i] = createObject(quadrangle, r, g, b, reflect, refract,
                                      x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4);
        }
        assert(objects[i] != NULL);
    }
    suns.reserve(m);
    for(int i = 0; i < m; ++i){
        double x, y, z, intensity;
        scanf("%lf%lf%lf%lf", &x, &y, &z, &intensity);
        suns.push_back(Sun(Point3D(std::move(x), std::move(y), std::move(z)), std::move(intensity)));
    }
    Point3D dw = w;
    dw *= (width / 2);
    Point3D dh = h;
    dh *= (height / 2);
    Point3D x1 = x0 + a - dw - dh;
    dw.normalize();
    dh.normalize();
    dw /= DPI;
    dh /= DPI;
    
    cairo_surface_t *surface;
    cairo_t *cr;
    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
                                         static_cast<int>(height * DPI),
                                         static_cast<int>(width * DPI));
    cr = cairo_create(surface);
    
    h = Point3D();
    for(int i = 0; i < width * DPI; ++i){
        w = Point3D();
        for(int j = 0; j < height * DPI; ++j){
            RGB rgb;
            rayTrace(x0, (x1 + w + h - x0).normalize(), objects, suns, rgb);
            //rgb.adecvat();
            //assert(rgb.r() <= 1 && rgb.g() <= 1 && rgb.b() <= 1);
            //assert(rgb.r() >= 0 && rgb.g() >= 0 && rgb.b() >= 0);
            cairo_set_source_rgb(cr, rgb.r(), rgb.g(), rgb.b());
            cairo_rectangle (cr, j, i, 1, 1);
            cairo_fill (cr);
            w += dw;
        }
        h += dh;
    }
    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    cairo_rectangle (cr, 0, 0, 10, 10);
    cairo_fill (cr);
    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    cairo_rectangle (cr, 0, 100, 10, 10);
    cairo_fill (cr);
    cairo_surface_write_to_png(surface, "image.png");
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
    for(int i = 0; i < n; ++i){
        delete objects[i];
    }
    return 0;
}
