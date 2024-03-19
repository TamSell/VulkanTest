#pragma once
#include <iostream>
#include "myWindow.h"
#include <vector>
#include <string>
#include <Windows.h>
#include <stdio.h>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan/vulkan.h>


void SetupVulkanInstance(HWND windowHandle, VkInstance* instance, VkSurfaceKHR* surface);

void SetupPhysicalDevice(VkInstance instance, VkPhysicalDevice* physicalDevice, VkDevice* device);

void SetupSwapChain(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, int* width, int* height, VkSwapchainKHR* swapChain, VkImage* presentImages, VkImageView** presentImageViews);

void SetupRenderPass(VkDevice device, VkPhysicalDevice physicalDevice, int width, int height, VkImageView* presentImages, VkRenderPass* renderPass, VkFramebuffer** frameBuffers);

void SetupCommandBuffer(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandBuffer* commandBuffer);

void SetupVertexBuffer(VkDevice device, VkPhysicalDevice physicalDevice, int* vertexSize, int* numberOfTriangles, VkBuffer* vertexInputBuffer);

void SetupShaderandUniforms(VkDevice device, VkPhysicalDevice physicaldevice, int width, int height, VkShaderModule* vertShaderModule, VkShaderModule* fragShaderModule, VkBuffer* buffer, VkDeviceMemory* memory);

void SetupDescriptors(VkDevice device, VkPhysicalDevice physicalDevice, VkDescriptorSet* descriptorSet, VkDescriptorSetLayout* descriptorSetLayout);

void SetupPipeline(VkDevice device, int width, int height, int vertexSize, VkDescriptorSetLayout descriptorSetLayout, VkShaderModule vertShaderModule, VkShaderModule fragShaderModule, VkRenderPass renderPass, VkPipeline* pipeline, VkPipelineLayout* pipelineLayout);

void RenderLoop(VkDevice device, int width, int height, int numberOfTriangles, VkSwapchainKHR swapChain, VkCommandBuffer commandBuffer, VkImage* presentImages, VkFramebuffer* framBuffers, VkRenderPass renderPass, VkBuffer vertexInputBuffer, VkDescriptorSetLayout descriptorSetLayout, VkPipeline pipeline);

int main() {


#if defined(_WIN32) defined(_WIN64)
	std::cout << "Windows OS" << std::endl;
#elif defined(APPLE)  defined(MACH)
	std::cout << "Mac OS" << std::endl;
#elif defined(linux)
	std::cout << "Linux OS" << std::endl;
#elif defined(unix)
	std::cout << "UNIX OS" << std::endl;
#else
	std::cout << "Unknown OS" << std::endl;
#endif

	//Step 1 -- Initializing the Window handled in myWindow class
	int width = 1080;
	int height = 720;
	myWindow* pWindow = new myWindow(width, height);
	bool running = true;

	//Step 2 -- Initializing Vulkan
	VkInstance instance = NULL;
	VkSurfaceKHR surface = NULL;
	SetupVulkanInstance(pWindow->getMyHandle(), &instance, &surface);

	//Step 3 -- Find/Create Device and Set-up selected Device
	VkPhysicalDevice physicalDevice = NULL;
	VkDevice device = NULL;
	SetupPhysicalDevice(instance, &physicalDevice, &device);

	//Step 4 -- Initialize Swap-Chain
	VkSwapchainKHR swapChain = NULL;
	VkImage* presentImages = NULL;
	VkImageView* presentImageViews = NULL;
	//SetupSwapChain(device, physicalDevice, surface, &width, &height , &swapChain, presentImages, &presentImageViews);


	//Step 5 -- Create Render Pass
	VkRenderPass renderPass = NULL;
	VkFramebuffer* frameBuffers = NULL;
//	SetupRenderPass(device, physicalDevice, width, height, presentImageViews, &renderPass, &frameBuffers);



	//Step 6 -- Create Command Pool/Buffer
	VkCommandBuffer commandBuffer = NULL;
	//SetupCommandBuffer(device, physicalDevice, &commandBuffer);


	//Step 7 -- Vertex Data/Buffer
	VkBuffer vertexInputBuffer = NULL;
	int vertexSize = 0;
	int numberOfTriangles = 0;
	//SetupVertexBuffer(device, physicalDevice, &vertexSize, &numberOfTriangles, &vertexInputBuffer);



	//Step 8 -- Load/Setup Shader
	VkShaderModule vertShaderModule = NULL;
	VkShaderModule fragShaderModule = NULL;
	VkBuffer buffer = NULL;
	VkDeviceMemory memory = NULL;
	//SetupShaderandUniforms(device, physicalDevice, width, height, &vertShaderModule, &fragShaderModule, &buffer, &memory);



	//Step 9 -- Setup Descriptors/Sets
	VkDescriptorSet descriptorSet = NULL;
	VkDescriptorSetLayout descriptorSetLayout = NULL;
	//SetupDescriptors(device, physicalDevice, &descriptorSet, &descriptorSetLayout);


	//Step 10 -- Pipeline
	VkPipeline pipeline = NULL;
	VkPipelineLayout pipelineLayout = NULL;
	//SetupPipeline(device, width, height, vertexSize, descriptorSetLayout, vertShaderModule, fragShaderModule, renderPass, &pipeline, &pipelineLayout);


	//Step 11 -- Render Loop

	while (running)
	{
		if (!pWindow->ProcessMessages())
		{
			std::cout << "Closing Window\n";
			running = false;
		}

		//Render
		//RenderLoop(device, width, height, numberOfTriangles, swapChain, commandBuffer, presentImages, frameBuffers, renderPass, vertexInputBuffer, descriptorSetLayout, pipeline);


		Sleep(10);

	} // End of While

	return 0;

} // end of Main



void SetupVulkanInstance(HWND windowHandle, VkInstance* outInstance, VkSurfaceKHR* outSurface)
{
	uint32_t count = 0;


	//Returns the number of instance layer properties available

	VkResult result = vkEnumerateInstanceLayerProperties(&count, NULL);

	if (VK_SUCCESS == result)
	{
		std::cout << "Instance Layers Available" << std::endl;
	}

	std::vector<VkLayerProperties> instanceLayers;
	instanceLayers.resize(count);

	result = vkEnumerateInstanceLayerProperties(&count, &instanceLayers[0]);



	//Extension Properties returns the requested number of global extension properties

	result = vkEnumerateInstanceExtensionProperties(NULL, &count, NULL);
	 	if (VK_SUCCESS == result)
	{
		std::cout << "Instance Extensions Available" << std::endl;
	}

	std::vector<VkExtensionProperties> instanceExtension;
	instanceExtension.resize(count);

	result = vkEnumerateInstanceExtensionProperties(NULL, &count, &instanceExtension[0]);

	std::vector<std::string> extensionNames;
	extensionNames.resize(count);

	const char* layers[] = { "VK_LAYER_NV_optimus" };

#ifdef ENABLE_VULKAN_DEBUG_CALLBACK
	const char *extensions[] = { "VK_KHR_surface",
								"VK_KHR_win32_surface",
								"VK_EXT_debug_report" };
#else
	const char *extensions[] = { "VK_KHR_surface",
								"VK_KHR_win32_surface" };
#endif

	{
		VkApplicationInfo ai = {};
		ai.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		ai.pApplicationName = "Tellor Vulkan Application";
		ai.engineVersion = 1;
		ai.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo ici = {};
		ici.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		ici.flags = 0;
		ici.pNext = 0;
		ici.pApplicationInfo = &ai;
		ici.enabledLayerCount = 1;
		ici.ppEnabledLayerNames = layers;
		ici.enabledExtensionCount = 2;
#ifdef ENABLE_VULKAN_DEBUG_CALLBACK
		ici.enabledExtensionCount = 3;
#endif
		ici.ppEnabledExtensionNames = extensions;

		VkResult result = vkCreateInstance(&ici, NULL, outInstance);

		if (result == VK_SUCCESS)
		{
			std::cout << "Created Vulkan Instance" << std::endl;
		}
	}

#ifdef ENABLE_VULKAN_DEBUG_CALLBACK
#endif

	HINSTANCE hInst = GetModuleHandle(NULL);

	VkWin32SurfaceCreateInfoKHR sci = {};
	sci.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;

	sci.hinstance = hInst;

	sci.hwnd = windowHandle;

	result = vkCreateWin32SurfaceKHR(*outInstance, &sci, NULL, outSurface);

	if (result == VK_SUCCESS)
	{
		std::cout << "Created Vulkan Surface" << std::endl;
	}
}

void SetupPhysicalDevice(VkInstance instance, VkPhysicalDevice* outPhysicalDevice, VkDevice* outDevice)
{
	uint32_t deviceCount = 0;

	VkResult result = vkEnumeratePhysicalDevices(instance, &deviceCount, NULL);

	if (result != VK_SUCCESS)
		std::cout << "Failed to find number of devices" << std::endl;

	std::vector<VkPhysicalDevice> physicalDevices(deviceCount);

	result = vkEnumeratePhysicalDevices(instance, &deviceCount, &physicalDevices[0]);

	if (result != VK_SUCCESS)
		std::cout << "Failed to enumerate physical devices" << std::endl;

	*outPhysicalDevice = physicalDevices[0];

	for (uint32_t i = 0; i < deviceCount; ++i)
	{
		VkPhysicalDeviceProperties deviceProperties;
		memset(&deviceProperties, 0, sizeof deviceProperties);

		vkGetPhysicalDeviceProperties(physicalDevices[i], &deviceProperties);
		printf("Driver Version: %d\n", deviceProperties.driverVersion);
		printf("Device Name: %s\n", deviceProperties.deviceName);
		printf("Device Type: %d\n", deviceProperties.deviceType);
	}

	VkPhysicalDeviceMemoryProperties memoryProperties;
	vkGetPhysicalDeviceMemoryProperties(*outPhysicalDevice, &memoryProperties);

	VkDeviceQueueCreateInfo queueCreateInfo = {};

	queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;

	queueCreateInfo.queueFamilyIndex = 0;
	queueCreateInfo.queueCount = 1;
	float queuePriorities[] = { 1.0f };
	queueCreateInfo.pQueuePriorities = queuePriorities;

	const char* deviceExtensions[] = { "VK_KHR_swapchain" };

	const char* layers[] = { "VK_LAYER_NV_optimus" };

	VkDeviceCreateInfo dci = {};
	dci.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

	dci.queueCreateInfoCount = 1;
	dci.pQueueCreateInfos = &queueCreateInfo;
	dci.enabledLayerCount = 0;
	dci.ppEnabledLayerNames = layers;
	dci.enabledExtensionCount = 1;
	dci.ppEnabledExtensionNames = deviceExtensions;

	VkPhysicalDeviceFeatures features = {};
	features.shaderClipDistance = VK_TRUE;
	dci.pEnabledFeatures = &features;

	result = vkCreateDevice(*outPhysicalDevice, &dci, NULL, outDevice);

	if (result == VK_SUCCESS)
		std::cout << "Created Logical Device" << std::endl;


}