#pragma comment(lib, "OpenGL32.lib")

#include <iostream>
#include <string>
#include <math.h>

#include "FEngine.h"

int main() {

    FEngine engine("F Engine", 1000, 650);

    Shader testShaders("shaders/gBufferVertex.glsl", "shaders/gBufferFragment.glsl");
    Scene testScene;

    Object testObj;
    testObj.AddShader(&testShaders);
    //std::vector<Mesh> test = Model::GetMeshes("C:\\Users\\Aidan\\Downloads\\sponza.obj");
    //testObj.SetMeshList(test);
    Mesh testObjCubeMesh = QuadPrimitive::GetMesh();
    testObj.AddMesh(&testObjCubeMesh);
    //Texture albedoMap("C:\\Users\\Aidan\\Downloads\\sponza_maps\\KAMEN.jpg", GL_TEXTURE_2D);
    Texture albedoMap("C:\\Users\\Aidan\\Documents\\C++\\OpenGL\\textures\\bricks\\albedo.jpg", GL_TEXTURE_2D);
    Texture normalMap("C:\\Users\\Aidan\\Documents\\C++\\OpenGL\\textures\\bricks\\normal.jpg", GL_TEXTURE_2D);
    Material testObjMaterial;
    testObjMaterial.AddAlbedoMap(&albedoMap);
    testObjMaterial.AddNormalMap(&normalMap);
    testObj.AddMaterial(&testObjMaterial);
    testScene.AddObject(&testObj);

    Camera sceneCam(engine.GetWindow());
    testScene.AddCamera(&sceneCam);
    engine.ChangeScene(&testScene);

    Mesh lightMesh = CubePrimitive::GetMesh();
    Object lightObj;
    Texture lightObjAlbedoMap("C:\\Users\\Aidan\\Documents\\C++\\OpenGL\\textures\\bricks\\albedo.jpg", GL_TEXTURE_2D);
    Material lightObjMaterial;
    lightObjMaterial.AddAlbedoMap(&lightObjAlbedoMap);
    lightObj.AddMaterial(&lightObjMaterial);
    lightObj.AddShader(&testShaders);
    lightObj.AddMesh(&lightMesh);
    lightObj.SetScale(glm::vec3(0.2f));
    lightObj.SetPosition(glm::vec3(2, 4, 3));
    testScene.AddObject(&lightObj);
    

    /////////////////// TEMP //////////////
    // Move camera
    sceneCam.SetPosition(glm::vec3(0, 0, 2));
    ///////////////////////////////////////
    while (engine.IsActive()) {
        engine.HandleInput();

        // Draw objects
        engine.DrawFrame(&sceneCam);
    }

    return 0;
}

