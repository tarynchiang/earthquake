/** CSci-4611 Assignment 3:  Earthquake
 */

#include "earth.h"
#include "config.h"

#include <vector>

// for M_PI constant
#define _USE_MATH_DEFINES
#include <math.h>

Earth::Earth() {
}

Earth::~Earth() {
}

void Earth::Init(const std::vector<std::string> &search_path,const bool &globe) {
    // init shader program
    shader_.Init();

    // init texture: you can change to a lower-res texture here if needed
    earth_tex_.InitFromFile(Platform::FindFile("earth-2k.png", search_path));

    // init geometry
    const int nslices = 10;
    const int nstacks = 10;

    // TODO: This is where you need to set the vertices and indiceds for earth_mesh_.
    std::vector<unsigned int> indices;
    std::vector<Point3> plane_vertices;
    std::vector<Point3> sphere_vertices;
    std::vector<Vector3> normal_vertices;
    std::vector<Point2> tex_coords;

    float xInterval = 2*M_PI/nslices;
    float yInterval = M_PI/nstacks;
    float longInterval = 360/nslices;
    float latInterval = 180/nstacks;

    //add vertices
    for(int i=0;i < nstacks+1;i++){
      for(int j=0;j < nslices+1;j++){

        plane_vertices.push_back(Point3((-M_PI)+j*xInterval, (-M_PI/2)+i*yInterval, 0));
        sphere_vertices.push_back(LatLongToSphere(-90 + i*latInterval, 180 + j*longInterval));
        normal_vertices.push_back((LatLongToSphere(-90 + i*latInterval, 180 + j*longInterval)-Point3(0,0,0)).ToUnit());
        tex_coords.push_back(Point2(((float)j/nslices), -((float)i/nstacks)));
      }
    }

    //add indices
    int start=0;
    for(int i=0;i < nstacks;i++){
      for(int j=0;j<nslices;j++){
        //first triangle in square
        indices.push_back(start+j);
        indices.push_back(start+j+1);
        indices.push_back(start+j+12);

        //second triangle in square
        indices.push_back(start+j);
        indices.push_back(start+j+12);
        indices.push_back(start+j+11);
      }
      start+=11;
    }

    if(globe){
      earth_mesh_.SetVertices(sphere_vertices);
      earth_mesh_.SetNormals(normal_vertices);
    }
    else{
      earth_mesh_.SetVertices(plane_vertices);
    }


    earth_mesh_.SetIndices(indices);
    earth_mesh_.SetTexCoords(0, tex_coords);
    earth_mesh_.UpdateGPUMemory();

	}



void Earth::Draw(const Matrix4 &model_matrix, const Matrix4 &view_matrix, const Matrix4 &proj_matrix) {
    // Define a really bright white light.  Lighting is a property of the "shader"
    DefaultShader::LightProperties light;
    light.position = Point3(10,10,10);
    light.ambient_intensity = Color(1,1,1);
    light.diffuse_intensity = Color(1,1,1);
    light.specular_intensity = Color(1,1,1);
    shader_.SetLight(0, light);

    // Adust the material properties, material is a property of the thing
    // (e.g., a mesh) that we draw with the shader.  The reflectance properties
    // affect the lighting.  The surface texture is the key for getting the
    // image of the earth to show up.
    DefaultShader::MaterialProperties mat;
    mat.ambient_reflectance = Color(0.5, 0.5, 0.5);
    mat.diffuse_reflectance = Color(0.75, 0.75, 0.75);
    mat.specular_reflectance = Color(0.75, 0.75, 0.75);
    mat.surface_texture = earth_tex_;

    // Draw the earth mesh using these settings
    if (earth_mesh_.num_triangles() > 0) {
        shader_.Draw(model_matrix, view_matrix, proj_matrix, &earth_mesh_, mat);
    }
}


Point3 Earth::LatLongToSphere(double latitude, double longitude) const {
    // TODO: We recommend filling in this function to put all your
    // lat,long --> sphere calculations in one place.
    double x = cos(GfxMath::ToRadians(latitude)) * sin(GfxMath::ToRadians(longitude));
    double y = sin(GfxMath::ToRadians(latitude));
    double z = cos(GfxMath::ToRadians(latitude)) * cos(GfxMath::ToRadians(longitude));
    return Point3(x, y, z);
}

Point3 Earth::LatLongToPlane(double latitude, double longitude) const {
    // TODO: We recommend filling in this function to put all your
    // lat,long --> plane calculations in one place.
    double x = -M_PI + (longitude+180.0)/180.0 * M_PI;
    double y = -M_PI_2 + (latitude+90.0)/180.0 * M_PI;
    return Point3(x,y,0.0);
}



void Earth::DrawDebugInfo(const Matrix4 &model_matrix, const Matrix4 &view_matrix, const Matrix4 &proj_matrix) {
    // This draws a cylinder for each line segment on each edge of each triangle in your mesh.
    // So it will be very slow if you have a large mesh, but it's quite useful when you are
    // debugging your mesh code, especially if you start with a small mesh.
    for (int t=0; t<earth_mesh_.num_triangles(); t++) {
        std::vector<unsigned int> indices = earth_mesh_.triangle_vertices(t);
        std::vector<Point3> loop;
        loop.push_back(earth_mesh_.vertex(indices[0]));
        loop.push_back(earth_mesh_.vertex(indices[1]));
        loop.push_back(earth_mesh_.vertex(indices[2]));
        quick_shapes_.DrawLines(model_matrix, view_matrix, proj_matrix,
            Color(1,1,0), loop, QuickShapes::LinesType::LINE_LOOP, 0.005);
    }
}
