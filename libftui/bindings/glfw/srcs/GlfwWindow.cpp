/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwWindow.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 18:32:46 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/02 10:29:43 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftui/glfw/GlfwWindow.hpp"
#include "ftui/glfw/IGlfwEventListener.hpp"
#include <stdexcept>

namespace ftui
{

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

GlfwWindow::GlfwWindow(int width, int height, char const *title,
		int major, int minor) :
	_window(NULL)
{
	initGlfw();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	if (HINT_DOUBLE_BUFFER)
		glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, OPENGL_PROFILE);
	if ((_window = glfwCreateWindow(width, height, title, NULL, NULL)) == NULL)
	{
		glfwTerminate();
		throw std::runtime_error("Cannot create GLFW window");
	}
	glfwMakeContextCurrent(_window);
	initGlew();
	glViewport(0, 0, width, height);
	glfwSetKeyCallback(_window, &GlfwWindow::_glfw_on_key);
	glfwSetMouseButtonCallback(_window, &GlfwWindow::_glfw_on_button);
	glfwSetScrollCallback(_window, &GlfwWindow::_glfw_on_scroll);
	glfwSetCursorPosCallback(_window, &GlfwWindow::_glfw_on_move);
	glfwSetCursorEnterCallback(_window, &GlfwWindow::_glfw_on_enter);
}

GlfwWindow::~GlfwWindow(void)
{
	glfwDestroyWindow(_window);
	deinitGlfw();
}

void				GlfwWindow::setEventListener(IGlfwEventListener *listener)
{
	glfwSetWindowUserPointer(_window, listener);
}

bool				GlfwWindow::shouldClose(void) const
{
	if (glfwWindowShouldClose(_window))
		return (true);
	return (false);
}

void				GlfwWindow::setShouldClose(bool shouldClose)
{
	glfwSetWindowShouldClose(_window, shouldClose);
}

GLFWwindow			*GlfwWindow::getWindow(void)
{
	return (_window);
}

/*
** ========================================================================== **
** Static
*/

/*
** GLFW and GLEW loaders
*/

int					GlfwWindow::_glfwInstances = 0;
bool				GlfwWindow::_glewInitied = false;

void				GlfwWindow::initGlfw(void)
{
	_glfwInstances++;
	if (_glfwInstances > 1)
		return ;
	if (glfwInit() != GL_TRUE)
		throw std::runtime_error("Cannot load GLFW");
}

void				GlfwWindow::initGlew(void)
{
	if (_glewInitied)
		return ;
	if (!INIT_GLEW)
		throw std::runtime_error("Cannot load GLEW");
	_glewInitied = true;
}

void				GlfwWindow::deinitGlfw(void)
{
	_glfwInstances--;
	if (_glfwInstances > 0)
		return ;
	glfwTerminate();
}

/*
** GLFW event handling
*/

void				GlfwWindow::_glfw_on_key(GLFWwindow *window,
	int key, int scancode, int action, int mods)
{
	IGlfwEventListener	*listener = reinterpret_cast<IGlfwEventListener*>
		(glfwGetWindowUserPointer(window));

	if (listener == NULL)
		return ;
	if (action == GLFW_PRESS)
		listener->onKeyDown(key, scancode, mods);
	else if (action == GLFW_RELEASE)
		listener->onKeyUp(key, scancode, mods);
	else if (action == GLFW_REPEAT)
		listener->onKeyRepeat(key, scancode, mods);
}

void				GlfwWindow::_glfw_on_button(GLFWwindow *window,
	int button, int action, int mods)
{
	IGlfwEventListener	*listener = reinterpret_cast<IGlfwEventListener*>
		(glfwGetWindowUserPointer(window));

	if (listener == NULL)
		return ;
	if (action == GLFW_PRESS)
		listener->onMouseDown(button, mods);
	else if (action == GLFW_RELEASE)
		listener->onMouseUp(button, mods);
}

void				GlfwWindow::_glfw_on_scroll(GLFWwindow *window,
	double x, double y)
{
	IGlfwEventListener	*listener = reinterpret_cast<IGlfwEventListener*>
		(glfwGetWindowUserPointer(window));

	if (listener != NULL)
		listener->onMouseScroll(x, y);
}

void				GlfwWindow::_glfw_on_move(GLFWwindow *window,
	double x, double y)
{
	IGlfwEventListener	*listener = reinterpret_cast<IGlfwEventListener*>
		(glfwGetWindowUserPointer(window));

	if (listener != NULL)
		listener->onMouseMove(x, y);
}

void				GlfwWindow::_glfw_on_enter(GLFWwindow *window, int enter)
{
	IGlfwEventListener	*listener = reinterpret_cast<IGlfwEventListener*>
		(glfwGetWindowUserPointer(window));

	if (listener == NULL)
		return ;
	if (enter)
		listener->onMouseEnter();
	else
		listener->onMouseLeave();
}

};
