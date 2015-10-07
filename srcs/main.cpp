// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 11:54:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/05 17:34:59 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ftui/glfw/GlfwWindow.hpp"
#include "ftui/glfw/IGlfwEventListener.hpp"
#include "ft/utils.hpp"

#include <iostream>
#include <fstream>

#include "ftui/Activity.hpp"
#include "ftui/luaCFunctions_helpers.hpp"
#include "ftui/lua.hpp"

/*
** everything here is example or test
*/

class Main : public ftui::IGlfwEventListener
{
public:
	Main(void) :
		_window(500, 400, "lol"), _act(ft::Vec2<int>(500, 400))
		, _puzzleSize(42)
	{
		std::ifstream			stream("res/layout/npuzzleui.xml");

		Main::_instance = this;
		_act.inflate(stream);
		_window.setEventListener(this);
		_act.registerLuaCFun_global("getPuzzleSize", &Main::getPuzzleSize);

		
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

		lua_pushstring(_act.getLuaState(), "ft");
		lua_pushinteger(_act.getLuaState(), 42);
		lua_pushinteger(_act.getLuaState(), 43);
		lua_pushnumber(_act.getLuaState(), 21.12);
		
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

	static ft::Vec2<int>	ret2(void)
		{
			std::cout << "ret2" << std::endl;
			return {21, 42};
		}

	static void				give2(ft::Vec2<int> v)
		{
			std::cout << "give2 with:" << v.x<< " " << v.y<< std::endl;
			return ;
		}

	static void				give4(std::string s
								  , ft::Vec2<int> v
								  , double d)
		{
			std::cout << "give4 with:"
					  << s  << " "
					  << v.x  << " "
					  << v.y  << " "
					  << d  << " "
					  << std::endl;
			return ;
		}

	
	static int				give1ret1(int)
		{
			std::cout << "give1ret1" << std::endl;
			return 84;
		}

	static int			give6ret5(lua_State *l)
		{
			return ftui::helperFun<0, 2>(l, &Main::ret2);
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
