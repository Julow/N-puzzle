/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwWindow.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 18:32:14 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/02 10:29:17 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFWWINDOW_HPP
# define GLFWWINDOW_HPP

# include "ftui/libftui.hpp"

# ifdef MAC_OS_MODE
#  define GLFW_INCLUDE_GLCOREARB
# else
#  include <GL/glew.h>
# endif

# include <GLFW/glfw3.h>

namespace ftui
{

/*
** GlfwWindow
** -
** Represent a window
** GLFW is used to display the window, catch events and bind OpenGL
** -
** It's safe to directly extend this class
*/
class	GlfwWindow
{
public:
	/*
	** Constructor create a new window
	** throw runtime_error on fail
	*/
	GlfwWindow(int width, int height, char const *title,
		int major = 4, int minor = 1);
	virtual ~GlfwWindow(void);

	/*
	** Set the event listener
	** Warning: previous listener will be forgotten and not correctly delete
	*/
	void					setEventListener(IGlfwEventListener *listener);

	/*
	** Return true if the window should be closed
	** Same as glfwWindowShouldClose
	*/
	bool					shouldClose(void) const;

	/*
	** Return the GLFWwindow
	*/
	GLFWwindow				*getWindow(void);

	/*
	** Set shouldClose bool
	*/
	void					setShouldClose(bool shouldClose);

protected:

	GLFWwindow				*_window;

private:

	void					_initEvents(void);

	GlfwWindow(void);
	GlfwWindow(GlfwWindow const &src);
	GlfwWindow				&operator=(GlfwWindow const &rhs);

/*
** Static
*/
protected:

	static int				_glfwInstances;
	static bool				_glewInitied;

/*
** Glfw event handling
*/
	static void				_glfw_on_key(GLFWwindow *, int, int, int, int);
	static void				_glfw_on_button(GLFWwindow *, int, int, int);
	static void				_glfw_on_scroll(GLFWwindow *, double, double);
	static void				_glfw_on_move(GLFWwindow *, double, double);
	static void				_glfw_on_enter(GLFWwindow *, int);

/*
** Load libs
** throw runtime_error on fail
** It's safe to call them more than once
*/
	static void				initGlfw(void);
	static void				initGlew(void);

/*
** Decrement _glfwInstances and terminate glfw if possible
*/
	static void				deinitGlfw(void);
};

};

#endif
