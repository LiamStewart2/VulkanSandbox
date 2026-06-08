#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include <GLFW/glfw3.h>
#include <GLM/glm.hpp>

class Application
{
public:
    Application();
    ~Application();

private:
    void Mainloop();

    void Init();
    void InitWindow();
    void InitVulkan();
    
    void CreateInstance();
    

    void HandleEvents();
    void Update();
    void Render();

    void Cleanup();

private:
    GLFWwindow* window;
    VkInstance instance;

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
};