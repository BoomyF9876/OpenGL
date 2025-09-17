#pragma once

#ifndef _WINDOWCONTROLLER_H_
#define _WINDOWCONTROLLER_H_

#include "StandardIncludes.h"

class WindowController
{
	GLFWwindow* window = nullptr;

public:
	static WindowController& GetInstance()
	{
		static WindowController instance;
		return instance;
	}

	GLFWwindow* GetWindow()
	{
		if (window == nullptr)
		{
			NewWindow();
		}

		return window;
	}

	void NewWindow();

private:
	WindowController() = default;
	~WindowController();
};

#endif