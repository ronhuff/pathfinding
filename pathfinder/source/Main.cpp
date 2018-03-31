//#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include <memory>

#include "Executive.h"


int main()
{
	srand(time(NULL));
	Executive exec;
	while (exec.run())
	{

	}
	return(0);
}
