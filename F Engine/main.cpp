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
    //testObj.SetMeshList(Model::GetMeshes("C:\\Users\\Aidan\\Downloads\\nanosuit.obj"));
    std::vector<Mesh> test = Model::GetMeshes("C:\\Users\\Aidan\\Downloads\\bread.obj");
    testObj.SetMeshList(test);
    testObj.SetScale(glm::vec3(1.2f));

    Camera sceneCam(engine.GetWindow());

    Scene testScene;
    testScene.AddObject(&testObj);
    testScene.AddCamera(&sceneCam);
    engine.ChangeScene(&testScene);

    
    Mesh lightMesh = CubePrimitive::GetMesh();
    Object lightObj;
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

        testObj.SetRotation(glm::vec3(glfwGetTime()*30, 0, 0));

        engine.HandleInput();

        // Draw objects
        engine.DrawFrame(&sceneCam);
    }

    return 0;
}

