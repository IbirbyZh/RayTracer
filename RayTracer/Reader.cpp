//
//  Reader.cpp
//  RayTracer
//
//  Created by Шишкин Евгений on 18.05.16.
//  Copyright © 2016 Шишкин Евгений. All rights reserved.
//

#include "Reader.hpp"
#include <sstream>
#include <utility>

FileReader::FileReader(const std::string& s):
    input(s)
{}

FileReader::~FileReader(){
    input.close();
}

void FileReader::Read(Scene& scene, std::vector<Sun>& suns, std::vector<Polygon>& objects)
{
    std::string s;
    std::map<std::string, Mat> materials;
    while(getline(input, s)){
        std::stringstream myStream(std::move(s));
        myStream >> s;
        if (s[0] == '#'){
            continue;
        }
        if (s == "viewport"){
            ReadScene(scene);
            continue;
        }
        if (s == "materials"){
            ReadMatereals(materials);
            continue;
        }
        if (s == "lights"){
            ReadSuns(suns, scene);
            continue;
        }
        if (s == "geometry"){
            ReadObjects(objects, materials);
            continue;
        }
    }
}

void FileReader::ReadScene(Scene &scene)
{
    std::string s;
    double xO, yO, zO;
    double xtl, ytl, ztl;
    double xtr, ytr, ztr;
    double xdl, ydl, zdl;
    while(getline(input, s)){
        std::stringstream myStream(std::move(s));
        myStream >> s;
        if (s[0] == '#'){
            continue;
        }
        if (s == "topleft"){
            myStream >> xtl >> ytl >> ztl;
            continue;
        }
        if (s == "topright"){
            myStream >> xtr >> ytr >> ztr;
            continue;
        }
        if (s == "bottomleft"){
            myStream >> xdl >> ydl >> zdl;
            continue;
        }
        if (s == "origin"){
            myStream >> xO >> yO >> zO;
            continue;
        }
        if (s == "endviewport"){
            scene = Scene(Point3D(std::move(xO), std::move(yO), std::move(zO)), Point3D(xtl, ytl, ztl),
                          Point3D(xtr - xtl, ytr - ytl, ztr - ztl), Point3D(xdl - xtl, ydl - ytl, zdl - ztl));
            return;
        }
    }
}

void FileReader::ReadSuns(std::vector<Sun> &suns, Scene& scene)
{
    std::string s;
    while(getline(input, s)){
        std::stringstream myStream(std::move(s));
        myStream >> s;
        if (s[0] == '#'){
            continue;
        }
        if (s == "point"){
            ReadSun(suns);
            continue;
        }
        if (s == "reference"){
            ReadReference(scene);
            continue;
        }
        if (s == "endlights"){
            return;
        }
    }
}

void FileReader::ReadSun(std::vector<Sun> &suns)
{
    std::string s;
    double xO, yO, zO;
    double power;
    while(getline(input, s)){
        std::stringstream myStream(std::move(s));
        myStream >> s;
        if (s[0] == '#'){
            continue;
        }
        if (s == "coords"){
            myStream >> xO >> yO >> zO;
            continue;
        }
        if (s == "power"){
            myStream >> power;
            continue;
        }
        if (s == "endpoint"){
            suns.push_back(Sun(Point3D(std::move(xO), std::move(yO), std::move(zO)), std::move(power)));
            return;
        }
    }
}

void FileReader::ReadReference(Scene& scene)
{
    std::string s;
    while(getline(input, s)){
        std::stringstream myStream(std::move(s));
        myStream >> s;
        if (s[0] == '#'){
            continue;
        }
        if (s == "power"){
            myStream >> scene.normPower;
            continue;
        }
        if (s == "distance"){
            myStream >> scene.normDist;
            continue;
        }
        if (s == "endreference"){
            return;
        }
    }
}

void FileReader::ReadMatereals(std::map<std::string, Mat> &materials)
{
    std::string s;
    while(getline(input, s)){
        std::stringstream myStream(std::move(s));
        myStream >> s;
        if (s[0] == '#'){
            continue;
        }
        if (s == "entry"){
            ReadMatereal(materials);
            continue;
        }
        if (s == "endmaterials"){
            return;
        }
    }
}

void FileReader::ReadMatereal(std::map<std::string, Mat> &materials)
{
    std::string s;
    Mat m;
    std::string id;
    while(getline(input, s)){
        std::stringstream myStream(std::move(s));
        myStream >> s;
        if (s[0] == '#'){
            continue;
        }
        if (s == "name"){
            myStream >> id;
            continue;
        }
        if (s == "color"){
            int x, y, z;
            myStream >> x >> y >> z;
            m.rgb = RGB(x / 255., y / 255., z / 255.);
            continue;
        }
        if (s == "reflect"){
            myStream >> m.reflect;
            continue;
        }
        if (s == "refract"){
            myStream >> m.refract;
            continue;
        }
        if (s == "endentry"){
            materials.insert(std::pair<std::string, Mat>(id, m));
            return;
        }
    }
}

void FileReader::ReadObjects(std::vector<Polygon>& objects, const std::map<std::string, Mat> &materials)
{
    std::string s;
    while(getline(input, s)){
        std::stringstream myStream(std::move(s));
        myStream >> s;
        if (s[0] == '#'){
            continue;
        }
        if (s == "sphere"){
            ReadSphere(objects, materials);
            continue;
        }
        if (s == "triangle"){
            ReadTriangle(objects, materials);
            continue;
        }
        if (s == "quadrangle"){
            ReadQuadrangle(objects, materials);
            continue;
        }
        if (s == "endgeometry"){
            return;
        }
    }
}

void FileReader::ReadSphere(std::vector<Polygon> &objects, const std::map<std::string, Mat> &materials)
{
    std::string s;
    Mat m;
    double x, y, z, r;
    while(getline(input, s)){
        std::stringstream myStream(std::move(s));
        myStream >> s;
        if (s[0] == '#'){
            continue;
        }
        if (s == "material"){
            myStream >> s;
            m = materials.at(s);
            continue;
        }
        if (s == "coords"){
            myStream >> x >> y >> z;
            continue;
        }
        if (s == "radius"){
            myStream >> r;
            continue;
        }
        if (s == "endsphere"){
            objects.push_back(Polygon(std::move(m.rgb), std::move(m.reflect), std::move(m.refract), sphere, x, y, z, r));
            return;
        }
    }
}

void FileReader::ReadTriangle(std::vector<Polygon> &objects, const std::map<std::string, Mat> &materials)
{
    std::string s;
    Mat m;
    double x[3], y[3], z[3];
    int i = 0;
    while(getline(input, s)){
        std::stringstream myStream(std::move(s));
        myStream >> s;
        if (s[0] == '#'){
            continue;
        }
        if (s == "material"){
            myStream >> s;
            m = materials.at(s);
            continue;
        }
        if (s == "vertex"){
            myStream >> x[i] >> y[i] >> z[i];
            ++i;
            continue;
        }
        if (s == "endtriangle"){
            objects.push_back(Polygon(std::move(m.rgb), std::move(m.reflect), std::move(m.refract), triangle, x[0], y[0], z[0],
                                      x[1], y[1], z[1], x[2], y[2], z[2]));
            return;
        }
    }
}

void FileReader::ReadQuadrangle(std::vector<Polygon> &objects, const std::map<std::string, Mat> &materials)
{
    std::string s;
    Mat m;
    double x[4], y[4], z[4];
    int i = 0;
    while(getline(input, s)){
        std::stringstream myStream(std::move(s));
        myStream >> s;
        if (s[0] == '#'){
            continue;
        }
        if (s == "material"){
            myStream >> s;
            m = materials.at(s);
            continue;
        }
        if (s == "vertex"){
            myStream >> x[i] >> y[i] >> z[i];
            ++i;
            continue;
        }
        if (s == "endquadrangle"){
            objects.push_back(Polygon(std::move(m.rgb), std::move(m.reflect), std::move(m.refract), quadrangle, x[0], y[0], z[0],
                                      x[1], y[1], z[1], x[2], y[2], z[2], x[3], y[3], z[3]));
            return;
        }
    }
}
