#pragma comment(lib, "OpenGL32.lib")

#include <iostream>
#include <string>

#include "FEngine.h"

int main() {
    FEngine engine;
    engine.CreateEngineWindow("F Engine", 800, 450);

    Object testObj;
   
    

    Shader testShaders("shaders/vertex.glsl", "shaders/fragment.glsl");
    testObj.AddShader(&testShaders);

    std::vector<Vertex> verticesTest;
    std::vector<unsigned int> indicesTest;
    CubePrimative::GetMesh(verticesTest, indicesTest);
    Mesh testMesh(verticesTest, indicesTest);
    testObj.AddMesh(&testMesh);

    Camera sceneCam(engine.GetWindow());

    Scene testScene;
    testScene.AddObject(&testObj);
    testScene.AddCamera(&sceneCam);
    engine.ChangeScene(&testScene);




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

