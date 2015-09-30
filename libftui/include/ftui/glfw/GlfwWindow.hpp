/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GlfwWindow.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/30 18:32:14 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/30 19:06:50 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLFWWINDOW_HPP
# define GLFWWINDOW_HPP

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

protected:

	GLFWwindow			*_window;

private:
	GlfwWindow(void);
	GlfwWindow(GlfwWindow const &src);
	GlfwWindow			&operator=(GlfwWindow const &rhs);

/*
** Static
*/
protected:

	static bool			_glfwInitied;
	static bool			_glewInitied;

/*
** Load libs
** throw runtime_error on fail
** It's safe to call them more than once
*/
	static void			initGlfw(void);
	static void			initGlew(void);
};

};

#endif
