#include "Application.h"

int main()
{
	try
	{
		Application app = Application();
	} 
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}