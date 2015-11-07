// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 09:37:37 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/07 09:47:52 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ft/utils.hpp"
#include "config_window.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <typeinfo>
#include <string>     // std::string, std::to_string

#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/ALayout.hpp"
#include "ftlua/ftlua.hpp"
#include "ftui/lua/lua.hpp"

#include "tiles/Tiles.hpp"

#include "GlCanvasHolder.hpp"
#include "gl.hpp"

#include "ISolverListener.hpp"
#include "OCamlBinding.hpp"

#include "ftui/Activity.hpp"
#include "ft/Vec.hpp"
#include "IState.hpp"
#include "StartState.hpp"
// #include "LoadingState.hpp"
// #include "ResultsState.hpp"


/*
** init glfw
*/
#ifdef MAC_OS_MODE
# define INIT_GLEW			true
# define OPENGL_PROFILE		GLFW_OPENGL_CORE_PROFILE
#else
# define INIT_GLEW			(glewInit() == GLEW_OK)
# define OPENGL_PROFILE		GLFW_OPENGL_COMPAT_PROFILE
#endif
#ifdef GLFW_DOUBLEBUFFER
# define HINT_DOUBLE_BUFFER	true
#else
# define GLFW_DOUBLEBUFFER	0
# define HINT_DOUBLE_BUFFER	false
#endif

class Main
{
public:
	Main(void)
		: _window(nullptr), _canvasHolder(WIN_WIDTHI, WIN_HEIGHTI)
	{
		std::srand(time(NULL));

		if (glfwInit() != GL_TRUE)
			throw std::runtime_error("Cannot load GLFW");
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_SAMPLES, 4);
		glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
		if (HINT_DOUBLE_BUFFER)
			glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_PROFILE);
		if ((_window = glfwCreateWindow(WIN_WIDTHI, WIN_HEIGHTI, "npuzzle", NULL, NULL)) == NULL)
			throw std::runtime_error("Cannot create GLFW window");
		glfwMakeContextCurrent(_window);
		if (!INIT_GLEW)
			throw std::runtime_error("Cannot load GLEW");
		glViewport(0, 0, WIN_WIDTHI, WIN_HEIGHTI);
		glfwSetWindowUserPointer(_window, this);
		glfwSetKeyCallback(_window, &Main::handleKeyEvents);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		_canvasHolder.init();

		IState::globalInit();
	}

	void				loop(void)
	{
		ftui::Canvas		canvas(_canvasHolder.getCanvas());

		while (!glfwWindowShouldClose(_window))
		{
			glfwPollEvents();
			// glClearColor(0.f, 0.f, 0.f, c1.f);
			// glClear(GL_COLOR_BUFFER_BIT);
			// canvas.clear();
			_state->loop(_state, canvas);
			_canvasHolder.render();
			glfwSwapBuffers(_window);
		}
	}

	~Main(void)
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

private:
	static Main			*_instance;
public:
	static Main			*instance(void){return _instance;}
public:

/*
** events
*/
	void				onKeyUp(int key, int scancode, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(_window, true);
		// else
			// _currentActivity->onKeyUp(key);
		(void)scancode;
		(void)mods;
		// changeActivity(&_mainActivity); // lol
	}

	void				onKeyDown(int key, int scancode, int mods)
	{
		// _currentActivity->onKeyDown(key);
		(void)scancode;
		(void)mods;
		// changeActivity(&_secondActivity); // lol
	}

/*
** handle glfw events
*/
	static void			handleKeyEvents(GLFWwindow *window,
		int key, int scancode, int action, int mods)
	{
		Main		*main;

		main = reinterpret_cast<Main*>(glfwGetWindowUserPointer(window));
		if (main == NULL)
			return ;
		if (action == GLFW_RELEASE)
			main->onKeyUp(key, scancode, mods);
		else if (action == GLFW_PRESS)
			main->onKeyDown(key, scancode, mods);
	}

protected:

	GLFWwindow				*_window;
	std::unique_ptr<IState>	_state;

	GlCanvasHolder			_canvasHolder;
};

Main			*Main::_instance;

int				main(void)
{
	try
	{
		Main		main;

		main.loop();
	}
	catch (std::exception const &e)
	{
		std::cout << "lol: " << e.what() << std::endl;
	}
	return (0);
}
