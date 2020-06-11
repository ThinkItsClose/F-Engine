#pragma comment(lib, "OpenGL32.lib")

#include <iostream>
#include <string>

#include "FEngine.h"

int main(){
    FEngine engine;
    engine.CreateEngineWindow("F Engine", 800, 450);
    engine.GetWindow()->GetWindow();

    Object testObj;

   
    Vertex test1;
    Vertex test2;
    Vertex test3;
    test1.position = glm::vec3(-0.5, -0.5, 0);
    test2.position = glm::vec3(0.5, -0.5, 0);
    test3.position = glm::vec3(0.5, 0.5, 0);
    
    
    std::vector<Vertex> verticesTest = {test1, test2, test3};
    std::vector<unsigned int> indicesTest = {0, 1, 2};

    Shader testShaders("shaders/vertex.cpp", "shaders/fragment.cpp");
    testObj.AddShader(&testShaders);

    Mesh testMesh(verticesTest, indicesTest);
    testObj.AddMesh(&testMesh);

    Scene testScene;
    testScene.AddObject(&testObj);
    engine.ChangeScene(&testScene);

    while (engine.IsActive()) {
        engine.DrawFrame();
    }

    return 0;
}

