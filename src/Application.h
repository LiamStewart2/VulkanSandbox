#pragma once

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <map>
#include <optional>
#include <set>
#include <limits>
#include <algorithm>
#include <fstream>

#include <GLM/glm.hpp>

struct QueueFamilyIndices {
    std::optional<uint32_t> m_GraphicsFamily;
    std::optional<uint32_t> m_PresentFamily;
    bool IsComplete() 
    {
        return m_GraphicsFamily.has_value() && m_PresentFamily.has_value(); 
    }
};

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR m_Capabilities;
    std::vector<VkSurfaceFormatKHR> m_Formats;
    std::vector<VkPresentModeKHR> m_PresentModes;
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
    bool CheckDeviceExtensionSupport(VkPhysicalDevice device);
    QueueFamilyIndices FindQueueFamilies(VkPhysicalDevice device);

    // Surface
    void CreateSurface();

    // Swap Chain Initialization
    SwapChainSupportDetails QuerySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR ChooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D ChooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
    void CreateSwapChain();
    void CreateImageViews();

    // Graphics Pipeline
    void CreateGraphicsPipeline();
    void CreateRenderPass();
    VkShaderModule CreateShaderModule(const std::vector<char>& code);

    // Framebuffers
    void CreateFramebuffers();

    // Commands
    void CreateCommandPool();
    void CreateCommandBuffer();
    void RecordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

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
    VkQueue m_PresentQueue;
    VkSurfaceKHR m_Surface;
    VkSwapchainKHR m_Swapchain;
    std::vector<VkImage> m_SwapChainImages;
    VkFormat m_SwapChainImageFormat;
    VkExtent2D m_SwapChainExtent;
    std::vector<VkImageView> m_SwapChainImageViews;
    VkPipelineLayout m_PipelineLayout;
    VkPipeline m_GraphicsPipeline;
    VkRenderPass m_RenderPass;
    std::vector<VkFramebuffer> m_SwapChainFramebuffers;
    VkCommandPool m_CommandPool;
    VkCommandBuffer m_CommandBuffer;


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


    // Required extensions
    const std::vector<const char*> m_DeviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
};