//#include "include/Skeleton/Skeleton.hpp"
//#include "include/Madeline/Logger/Logging.hpp"
//#include "include/Madeline/WindowManager/WindowManager.hpp"
#include <iostream>

int main(int, char* [])
{
	/*
		//Madeline::Logging *Logsystem = new Madeline::Logging;
		//delete Logsystem;
		//boost::log::sources::logger lg;

		std::unique_ptr<Madeline::WindowManager> WinMngr(new Madeline::WindowManager);
		WinMngr->initalize();

		//X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X
		// X X X X X X X X X Start Create Startup Window(s)  X X X X X X X X X X X
		//X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X

		Madeline::WindowConfig Window1;
		Window1.HEIGHT = 800;
		Window1.WIDTH = 800;
		Window1.NAME = "Test Window";
		WinMngr->addWindow(Window1);

		/*
		Madeline::windowConfig Window2;
		Window2.HEIGHT = 700;
		Window2.WIDTH = 700;
		Window2.NAME = "UwU 2 electric boogaloo";
		WinMngr->addWindow( Window2 );
		//*/

		/*
		Madeline::windowConfig Window3;
		Window3.HEIGHT = 600;
		Window3.WIDTH = 600;
		//Window3.NAME = "UwU 3 jump for jubilee";
		Window3.NAME = "Window 3";
		WinMngr->addWindow(Window3);
		//*/

		//X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X
		// X X X X X X X X X X End Create Startup Window(s)  X X X X X X X X X X X
		//X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X X
			/*
		while (WinMngr->areActiveWindows())
		{
			WinMngr->allMainLoops();

			WinMngr->checkWindowsForCloseRequest();
		}

		WinMngr->cleanup();
		WinMngr.release();
		*/
	std::cout << "Exit" << std::endl;
	std::cin.ignore(1000, '\n');
	return 0;
	//return EXIT_SUCCESS;
}