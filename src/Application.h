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
#include <chrono>

#define GLM_FORCE_RADIANS
#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include "Vertex.h"

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

struct UniformBufferObject
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

class Application
{
public:
    Application();
    ~Application();

    void SetFramebufferChangedFlag(bool value) {m_FramebufferResized = value;}

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
    void RecreateSwapChain();
    void CleanupSwapChain();
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

    // Sync
    void CreateSyncObjects();

    // Vertex objects
    void CreateVertexBuffer();
    void CreateIndexBuffer();
    uint32_t FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
    void CreateBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
    void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);

    // Uniform Buffer Objects
    void CreateDescriptorSetLayout();
    void CreateUniformBuffers();
    void UpdateUniformBuffer(uint32_t currentImage);

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
    VkDescriptorSetLayout m_DescriptorSetLayout;
    VkPipelineLayout m_PipelineLayout;
    VkPipeline m_GraphicsPipeline;
    VkRenderPass m_RenderPass;
    std::vector<VkFramebuffer> m_SwapChainFramebuffers;
    VkCommandPool m_CommandPool;
    std::vector<VkCommandBuffer> m_CommandBuffers;
    std::vector<VkSemaphore> m_ImageAvailableSemaphores;
    std::vector<VkSemaphore> m_RenderFinishedSemaphores;
    std::vector<VkFence> m_InFlightFences;
    bool m_FramebufferResized = false;
    uint32_t m_CurrentFrame = 0;
    VkBuffer m_VertexBuffer;
    VkDeviceMemory m_VertexBufferMemory;
    VkBuffer m_IndexBuffer;
    VkDeviceMemory m_IndexBufferMemory;
    std::vector<VkBuffer> m_UniformBuffers;
    std::vector<VkDeviceMemory> m_UniformBuffersMemory;
    std::vector<void*> m_UniformBuffersMapped;

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

    const uint8_t MAX_FRAMES_IN_FLIGHT = 3;

    const std::vector<Vertex> m_Vertices =
    {
        {{-0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}},
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
        {{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
    };

    const std::vector<uint32_t> m_Indices = {
        0, 1, 2, 2, 3, 0
    };
};