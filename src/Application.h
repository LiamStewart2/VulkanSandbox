#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

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


    bool CheckValidationLayerSupport();
    std::vector<const char*> GetRequiredExtensions();
    void PopulateDebugMessagerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void SetupDebugMessenger();

    void HandleEvents();
    void Update();
    void Render();

    void Cleanup();


private:
    GLFWwindow* m_Window;
    VkInstance m_Instance;

    // Handle validation layers
    const std::vector<const char*> m_ValidationLayers = {
        "VK_LAYER_KHRONOS_validation"
    };
    #ifdef NDEBUG
        const bool enableValidationLayers = false;
    #else
        const bool enableValidationLayers = true;
    #endif
    VkDebugUtilsMessengerEXT m_DebugMessenger;

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
};