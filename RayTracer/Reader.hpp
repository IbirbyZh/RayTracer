//
//  Reader.hpp
//  RayTracer
//
//  Created by Шишкин Евгений on 18.05.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#ifndef Reader_hpp
#define Reader_hpp

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Sun.hpp"
#include "Scene.hpp"
#include "Polygon.hpp"
#include <map>
#include "Color.hpp"

class FileReader{
private:
    struct Mat{
        Mat();
        RGB rgb;
        double reflect, refract;
    };
public:
    FileReader(const std::string &s);
    ~FileReader();
    
    void Read(Scene& scene, std::vector<Sun>& suns, std::vector<Polygon> &objects);
private:
    std::ifstream input;
    std::string s;
    std::stringstream myStream;
    void ReadScene(Scene& scene);
    void ReadMatereals(std::map<std::string, Mat>& materials);
    void ReadMatereal(std::map<std::string, Mat>& materials);
    void ReadSuns(std::vector<Sun>& suns, Scene& scene);
    void ReadSun(std::vector<Sun>& suns);
    void ReadObjects(std::vector<Polygon> &objects, const std::map<std::string, Mat>& materials);
    void ReadSphere(std::vector<Polygon> &objects, const std::map<std::string, Mat>& materials);
    void ReadTriangle(std::vector<Polygon> &objects, const std::map<std::string, Mat>& materials);
    void ReadQuadrangle(std::vector<Polygon> &objects, const std::map<std::string, Mat>& materials);
    void ReadReference(Scene& scene);
};

#endif /* Reader_hpp */
