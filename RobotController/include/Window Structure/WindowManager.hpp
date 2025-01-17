#pragma once
#include "include/Madeline/WindowManager/WindowStructs.hpp"
#include "include/Madeline/WindowManager/Window.hpp"
#include "include/Madeline/WindowManager/VulkanDebugMessager.hpp"
#include "include/Madeline/WindowManager/Devices.hpp"
#include "include/Skeleton/Skeleton.hpp"
#include "include/Madeline/WindowManager/Swapchain.hpp"

namespace Madeline
{
	using pWindowMemberFunction = void (Window::*)();
	class WindowManager
	{
	public:
		
		void initalize();

		void cleanup();

		void allMainLoops();
		
		void addWindow( Madeline::WindowConfig& Config );
		
		bool areActiveWindows();
		
		void initalizeGLFW();
		
		void createVulkanInstance();
		
		void checkWindowsForCloseRequest();
		
		void terminateVulkanInstance();
		
		bool checkValidationLayerSupport();
		
		std::vector<const char*> getRequiredExtensions();
		
		void applyFunctionToAllWindows(pWindowMemberFunction func);
	private:
		std::vector<Madeline::Window> windowStack;
		const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};
		#ifdef NDEBUG
			const bool enableValidationLayers = false;
		#else
			const bool enableValidationLayers = true;
		#endif

		std::shared_ptr<VkObjects> vulkanObjects = std::make_shared<VkObjects>();
		VulkanDebugMessenger vkDebugMessenger{vulkanObjects};
		Devices devices{vulkanObjects, validationLayers};
	};
}

