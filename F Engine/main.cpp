#pragma comment(lib, "OpenGL32.lib")

#include <iostream>
#include <string>
#include <math.h>

#include "FEngine.h"

int main() {

    FEngine engine;
    engine.CreateEngineWindow("F Engine", 1000, 650);

      

    Shader testShaders("shaders/vertex.glsl", "shaders/fragment.glsl");
    

    Object testObj;
    testObj.AddShader(&testShaders);
    std::vector<Mesh> test = Model::GetMeshes("C:\\Users\\Aidan\\Downloads\\bread.obj");
    testObj.SetMeshList(test);
    //Mesh testObjCubeMesh = CubePrimitive::GetMesh();
    //testObj.AddMesh(&testObjCubeMesh);
    testObj.SetScale(glm::vec3(1.2f));
    Texture albedoMap("C:\\Users\\Aidan\\Downloads\\bread\\albedo.jpg", GL_TEXTURE_2D);
    Material testObjMaterial;
    testObjMaterial.AddAlbedoMap(&albedoMap);
    testObj.AddMaterial(&testObjMaterial);

    Camera sceneCam(engine.GetWindow());

    Scene testScene;
    testScene.AddObject(&testObj);
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
    testScene.AddObject(&lightObj);
    lightObj.SetScale(glm::vec3(0.2f));
    lightObj.SetPosition(glm::vec3(2, 4, 3));

    /////////////////// TEMP //////////////
    // Move camera
    sceneCam.SetPosition(glm::vec3(0, 0, 2));
    ///////////////////////////////////////

    while (engine.IsActive()) {

        testObj.SetRotation(glm::vec3(0, glfwGetTime() * 30, 0));

        engine.HandleInput();

        // Draw objects
        engine.DrawFrame(&sceneCam);
    }

    return 0;
}

