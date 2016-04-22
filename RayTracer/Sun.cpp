//
//  Sun.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 08.04.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Sun.hpp"
#include <utility>

Sun::Sun():
    __S(), __intensity(){}
                              
Sun::Sun(const Point3D& _S, const double& _intensity):
    __S(_S), __intensity(_intensity){}

Sun::Sun(Point3D&& _S, double&& _intensity):
    __S(std::move(_S)), __intensity(std::move(_intensity)){}

const Point3D& Sun::S() const{return __S;}
const double& Sun::intensity() const{return __intensity;}

void Sun::S(const Point3D& _S){__S = _S;}
void Sun::S(Point3D&& _S){__S = std::move(_S);}
void Sun::intensity(const double& _intensity){__intensity = _intensity;}
void Sun::intensity(double&& _intensity){__intensity = std::move(_intensity);}
