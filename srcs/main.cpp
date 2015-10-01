/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 11:54:09 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/01 14:53:59 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftui/glfw/GlfwWindow.hpp"
#include "ftui/glfw/IGlfwEventListener.hpp"
#include "ft/utils.hpp"

#include <iostream>

/*
** everything here are examples or tests
*/

class Main : public ftui::IGlfwEventListener
{
public:
	Main(void) :
		_window(500, 400, "lol")
	{
		_window.setEventListener(this);
	}

	void				loop(void)
	{
		while (!_window.shouldClose())
		{
			glfwPollEvents();
		}
	}

/*
** event listener
*/
	virtual void		onKeyUp(int key, int scancode, int mods)
	{
		ft::f(std::cout, "Key up; key: %, scancode: %, mods: %\n",
			key, scancode, mods);
		if (key == GLFW_KEY_ESCAPE)
			_window.setShouldClose(true);
	}

	virtual void		onKeyDown(int key, int scancode, int mods)
	{
		ft::f(std::cout, "Key down; key: %, scancode: %, mods: %\n",
			key, scancode, mods);
	}

	virtual void		onKeyRepeat(int key, int scancode, int mods)
	{
		ft::f(std::cout, "Key repeat; key: %, scancode: %, mods: %\n",
			key, scancode, mods);
	}

	virtual void		onMouseEnter(void)
	{
		std::cout << "Mouse enter" << std::endl;
	}

	virtual void		onMouseLeave(void)
	{
		std::cout << "Mouse leave" << std::endl;
	}

	virtual void		onMouseMove(double x, double y)
	{
		(void)x;
		(void)y;
	}

	virtual void		onMouseScroll(double x, double y)
	{
		(void)x;
		(void)y;
	}

	virtual void		onMouseUp(int button, int mods)
	{
		ft::f(std::cout, "Mouse up; button: %, mods: %\n", button, mods);
	}

	virtual void		onMouseDown(int button, int mods)
	{
		ft::f(std::cout, "Mouse down; button: %, mods: %\n", button, mods);
	}

protected:
	ftui::GlfwWindow	_window;
};

int				main(void)
{
	Main			main;

	main.loop();
	return (0);
}
