// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 10:15:01 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/09 13:20:39 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

// #include <iostream>
// #include <iomanip>
// #include <fstream>
// #include <stdexcept>
// #include <typeinfo>
// #include <string>     // std::string, std::to_string

#include "ft/utils.hpp"
#include "config_window.hpp"
#include "GlCanvasHolder.hpp"
#include "gl.hpp"
#include "OCamlBinding.hpp"
#include "IState.hpp"
#include "StartState.hpp"
#include "Main.hpp"

// #include "ftui/Activity.hpp"
// #include "ft/Vec.hpp"
// #include "LoadingState.hpp"
// #include "ResultsState.hpp"
// #include "ftui/Activity.hpp"
// #include "ISolverListener.hpp"


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

Main::Main(void)
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
	if ((_window = glfwCreateWindow(WIN_WIDTHI, WIN_HEIGHTI, "npuzzle"
									, NULL, NULL)) == NULL)
		throw std::runtime_error("Cannot create GLFW window");
	glfwMakeContextCurrent(_window);
	if (!INIT_GLEW)
		throw std::runtime_error("Cannot load GLEW");
	glViewport(0, 0, WIN_WIDTHI, WIN_HEIGHTI);
	glfwSetWindowUserPointer(_window, this);
	glfwSetKeyCallback(_window, &Main::handleKeyEvents);
	glfwSetCursorPosCallback(_window, &Main::handleMousePosEvents);
	glfwSetMouseButtonCallback(_window, &Main::handleMouseButtonEvents);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	IState::globalInit();
	_canvasHolder.init();

}

void				Main::loop(void)
{
	ftui::Canvas		&canvas(_canvasHolder.getCanvas());

	_state.reset(new StartState(canvas, _ocaml));
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
		// glClearColor(0.f, 0.f, 0.f, c1.f);
		// glClear(GL_COLOR_BUFFER_BIT);
		// canvas.clear();
		_state->loop(_state, canvas, _ocaml);
		_canvasHolder.render();
		glfwSwapBuffers(_window);
	}
}

Main::~Main(void)
{
	glfwDestroyWindow(_window);
	glfwTerminate();
}

Main			*Main::_instance;
Main			*Main::instance(void)
{return _instance;}

void			Main::onKeyUp(int key, int scancode, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(_window, true);
	else
		_state->getActivity().onKeyUp(key, mods);
	(void)scancode;
}

void			Main::onKeyDown(int key, int scancode, int mods)
{
	_state->getActivity().onKeyDown(key, mods);
	(void)scancode;
}

void			Main::onMouseMove(int x, int y)
{
	_state->getActivity().onMouseMove(x, y);
}

void			Main::onMouseUp(int x, int y, int button, int mods)
{
	_state->getActivity().onMouseUp(x, y, button, mods);
}

void			Main::onMouseDown(int x, int y, int button, int mods)
{
	_state->getActivity().onMouseDown(x, y, button, mods);
}

void			Main::handleKeyEvents(
	GLFWwindow *window, int key, int scancode, int action, int mods)
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

void			Main::handleMousePosEvents(
	GLFWwindow *window, double x, double y)
{
	Main		*main;

	main = reinterpret_cast<Main*>(glfwGetWindowUserPointer(window));
	if (main == NULL)
		return ;
	main->onMouseMove(x, y);
}

void            Main::handleMouseButtonEvents(
	GLFWwindow *window, int button, int action, int mods)
{
	Main		*main;
	double		pos[2];

	main = reinterpret_cast<Main*>(glfwGetWindowUserPointer(window));
	if (main == NULL)
		return ;
	glfwGetCursorPos(window, pos + 0, pos + 1);
	if (action == GLFW_PRESS)
		main->onMouseDown(static_cast<int>(pos[0]), static_cast<int>(pos[1])
						  , button, mods);
	else
		main->onMouseUp(static_cast<int>(pos[0]), static_cast<int>(pos[1])
						  , button, mods);
}

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
