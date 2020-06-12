#pragma comment(lib, "OpenGL32.lib")

#include <iostream>
#include <string>

#include "FEngine.h"

int main() {
    FEngine engine;
    engine.CreateEngineWindow("F Engine", 800, 450);

    Object testObj;
   
    Vertex test1;
    Vertex test2;
    Vertex test3;
    Vertex test4;
    test1.position = glm::vec3(-0.5, -0.5, 0);
    test2.position = glm::vec3(0.5, -0.5, 0);
    test3.position = glm::vec3(0.5, 0.5, 0);
    test4.position = glm::vec3(-0.5, 0.5, 0);
    
    std::vector<Vertex> verticesTest = {test1, test2, test3, test4};
    std::vector<unsigned int> indicesTest = {0, 1, 2, 0, 3, 2};

    Shader testShaders("shaders/vertex.glsl", "shaders/fragment.glsl");
    testObj.AddShader(&testShaders);

    Mesh testMesh(verticesTest, indicesTest);
    testObj.AddMesh(&testMesh);

    Scene testScene;
    testScene.AddObject(&testObj);
    engine.ChangeScene(&testScene);

    Camera sceneCam(engine.GetWindow());

    /////////////////// TEMP //////////////
    // Move camera
    sceneCam.SetPosition(glm::vec3(0, 0, 5));
    ///////////////////////////////////////

    while (engine.IsActive()) {

        /////////////////// TEMP //////////////
        // Move camera
        //sceneCam.SetYaw(sceneCam.GetYaw() - 0.5f);
        ///////////////////////////////////////

        // Draw objects
        engine.DrawFrame(&sceneCam);
    }

    return 0;
}

