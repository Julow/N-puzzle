/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwWindow.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 18:32:46 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/30 19:07:07 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GlfwWindow.hpp"
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
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	initGlew();
	glViewport(0, 0, width, height);
}

GlfwWindow::~GlfwWindow(void)
{
	glfwSetWindowShouldClose(_window, GL_TRUE);
}

bool			GlfwWindow::_glfwInitied = false;
bool			GlfwWindow::_glewInitied = false;

void			GlfwWindow::initGlfw(void)
{
	if (_glfwInitied)
		return ;
	if (glfwInit() != GL_TRUE)
		throw std::runtime_error("Cannot load GLFW");
	_glfwInitied = true;
}

void			GlfwWindow::initGlew(void)
{
	if (_glewInitied)
		return ;
	if (!INIT_GLEW)
		throw std::runtime_error("Cannot load GLEW");
	_glewInitied = true;
}

};
