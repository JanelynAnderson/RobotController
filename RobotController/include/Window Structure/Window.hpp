#pragma once
#include "include/Skeleton/Skeleton.hpp"
#include "include/Madeline/WindowManager/WindowStructs.hpp"
#include "include/Madeline/WindowManager/Swapchain.hpp"

namespace Madeline
{
	struct WindowConfig
	{
		std::string NAME = "Default Window Name";
		uint32_t WIDTH = 300;
		uint32_t HEIGHT = 300;
	};

	class Window
	{
	public:
		Window(WindowConfig& __IN__Config, std::shared_ptr<VkObjects> vulkanObjects);
		void mainLoop();
		void cleanupWindow();
		bool shouldWindowClose();
		void createSurface();
		void initalize();
		
		VkSurfaceKHR getSurface() { return windowObjects->surface; }
		GLFWwindow* getWindow() { return windowObjects->window; }
		Swapchain& getSwapchain() { return swapchain; }
		void drawFrame();
		void initWindow();

	private:
		static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
		void createGraphicsPipeline();
		void createRenderPass();
		void createCommandPool();
		void createCommandBuffers();
		void createSyncObjects();		
		
		void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);
		int MAX_FRAMES_IN_FLIGHT = 2;
		static std::vector<char> readFile(const std::string& filename)
		{
			std::ifstream file(filename, std::ios::ate | std::ios::binary);

			if (!file.is_open())
			{
				throw std::runtime_error("failed to open file!");
			}

			size_t fileSize = static_cast<size_t>(file.tellg());
			std::vector<char> buffer(fileSize);

			file.seekg(0);
			file.read(buffer.data(), fileSize);

			file.close();

			return buffer;
		}
		VkShaderModule createShaderModule(const std::vector<char>& code);

		uint32_t windowWidth;
		uint32_t windowHeight;
		std::string windowName;

		std::shared_ptr<VkObjects> vulkanObjects;

		Swapchain swapchain;
		std::shared_ptr<WinObjects> windowObjects = std::make_shared<WinObjects>();

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;

		std::vector < VkCommandBuffer > commandBuffers;
		VkCommandPool commandPool;

		uint32_t currentFrame = 0;
		bool framebufferResized = false;
	};
}
