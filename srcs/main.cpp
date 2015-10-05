/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 11:54:09 by jaguillo          #+#    #+#             */
//   Updated: 2015/10/05 19:20:51 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#include "ftui/glfw/GlfwWindow.hpp"
#include "ftui/glfw/IGlfwEventListener.hpp"
#include "ft/utils.hpp"

#include <iostream>
#include <fstream>

#include "ftui/Activity.hpp"
#include "ftui/luaCFunctions_helpers.hpp"

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

/*
** everything here is example or test
*/

class Main : public ftui::IGlfwEventListener
{
public:
	Main(void) :
		_window(500, 400, "lol"), _act(ftui::Vec2<int>(500, 400))
		, _puzzleSize(42)
	{
		std::ifstream			stream("res/layout/npuzzleui.xml");

		Main::_instance = this;
		_act.inflate(stream);
		_window.setEventListener(this);
		_act.registerGFun("getPuzzleSize", &Main::getPuzzleSize);

		
		std::cout << std::endl;
		lua_getglobal(_act.getLuaState(), "ftpt");
		lua_getglobal(_act.getLuaState(), "_G");
		lua_call(_act.getLuaState(), 1, 0);
		lua_getglobal(_act.getLuaState(), "print");
		lua_pushstring(_act.getLuaState(), "puzzle size:");
		lua_getglobal(_act.getLuaState(), "getPuzzleSize");
		lua_call(_act.getLuaState(), 0, 1);
		lua_call(_act.getLuaState(), 2, 0);
		
		std::cout << std::endl;

		Main::give6ret5(_act.getLuaState());
	}

	void				loop(void)
	{
		while (!_window.shouldClose())
		{
			glfwPollEvents();
			_act.render(*reinterpret_cast<ftui::ACanvas*>(&_act));
		}
	}
	int					getPuzzleSize(void) { return _puzzleSize; }

private:
	static Main			*_instance;
public:
	static Main			*instance(void){return _instance;}
	static int			getPuzzleSize(lua_State *l)
		{
			lua_pushinteger(l, instance()->getPuzzleSize());
			return (1);
		}

	static ftui::Vec2<int>	ret2(void)
		{
			std::cout << "ret2" << std::endl;
			return {21, 42};
		}

	static void				give2(ftui::Vec2<int>)
		{
			std::cout << "give2" << std::endl;
			return ;
		}

	static int				give1ret1(int)
		{
			std::cout << "give1ret1" << std::endl;
			return 84;
		}

	static int			give6ret5(lua_State *l)
		{
			return
				ftui::helperFun<4, 4>(
					l
					// , std::vector<ftui::Imemfun*>(
					// , ftui::make_fun<0, 2>(&Main::ret2)
					, ftui::make_fun<2, 0>(&Main::give2)
					// , ftui::make_fun<1, 1>(&Main::give1ret1)
					// , ftui::make_memfun<1, 1>(instance(), &Main::getPuzzleSize)
						// ftui::memfun(instance(), &Main::getPuzzleSize)
						// )
					)
				;
			(void)l;
		}
public:
	
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
	ftui::Activity		_act;
	int					_puzzleSize;
};
Main			*Main::_instance;

int				main(void)
{
	Main				main;
	
	main.loop();
	std::cout << "main end" << std::endl;
	return (0);
}
