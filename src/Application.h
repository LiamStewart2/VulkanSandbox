#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <map>
#include <optional>

#include <GLM/glm.hpp>

struct QueueFamilyIndices {
    std::optional<uint32_t> m_GraphicsFamily;
    bool IsComplete() {return m_GraphicsFamily.has_value(); }
};

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
    
    /* Initializing Vulkan */

    void CreateInstance();
    void CreateLogicalDevice();

    // Validation Layer
    bool CheckValidationLayerSupport();
    std::vector<const char*> GetRequiredExtensions();
    void PopulateDebugMessagerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    void SetupDebugMessenger();

    // Devices
    void PickPhysicalDevices();
    bool IsDeviceSuitable(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);



    void HandleEvents();
    void Update();
    void Render();

    void Cleanup();


private:
    GLFWwindow* m_Window;
    VkInstance m_Instance;
    VkPhysicalDevice m_PhysicalDevice = VK_NULL_HANDLE;
    VkDevice m_Device;
    VkQueue m_GraphicsQueue;

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