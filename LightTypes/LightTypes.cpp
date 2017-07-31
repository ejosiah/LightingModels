// LightTypes.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define GLM_SWIZZLE 

#include <ncl/gl/GlfwApp.h>
#include "LightTypesScene.h"

using namespace std;
using namespace ncl;
using namespace gl;

static ConsoleAppender CONSOLE_APPENDER;
vector<Appender*> Logger::appenders = { &CONSOLE_APPENDER };
const unsigned int Logger::level = LEVEL_DEBUG;

int main()
{
	start(new LigthTypesScene);
    return 0;
}

