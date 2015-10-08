// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 11:54:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/08 10:34:46 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ft/utils.hpp"

#include <iostream>
#include <fstream>
#include <stdexcept>

#include "ftui/Activity.hpp"
#include "ftui/luaCFunctions_helpers.hpp"
#include "ftui/lua.hpp"

#include "GlCanvasHolder.hpp"
#include "gl.hpp"

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

/*
** everything here is example or test
*/

#define WIDTH		500
#define HEIGHT		400

class Main
{
public:
	Main(void) :
		_canvasHolder(WIDTH, HEIGHT),
		_act(ft::Vec2<int>(WIDTH, HEIGHT)),
		_puzzleSize(42)
	{
		std::ifstream			stream("res/layout/npuzzleui.xml");

		Main::_instance = this;
		_act.inflate(stream);
		_act.registerLuaCFun_global("getPuzzleSize", &Main::getPuzzleSize);

/*
** init glwf
*/
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
		if ((_window = glfwCreateWindow(WIDTH, HEIGHT, "npuzzle", NULL, NULL)) == NULL)
			throw std::runtime_error("Cannot create GLFW window");
		glfwMakeContextCurrent(_window);
		if (!INIT_GLEW)
			throw std::runtime_error("Cannot load GLEW");
		glViewport(0, 0, WIDTH, HEIGHT);
		glfwSetWindowUserPointer(_window, this);
		glfwSetKeyCallback(_window, &Main::handleKeyEvents);
/*
** -
*/
		_canvasHolder.init();

/*
** test
*/
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
		ftui::Canvas		canvas(_canvasHolder.getCanvas());

		while (!glfwWindowShouldClose(_window))
		{
			glfwPollEvents();
			canvas.clear(ft::Rect<int>(0, 0, canvas.getWidth(), canvas.getHeight()));
			_act.render(canvas);
			_canvasHolder.render();
			glfwSwapBuffers(_window);
		}
	}
	int					getPuzzleSize(void) { return _puzzleSize; }

	~Main(void)
	{
		glfwDestroyWindow(_window);
		glfwTerminate();
	}

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
** events
*/
	void				onKeyUp(int key, int scancode, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(_window, true);
		else
			ft::f(std::cout, "Key up; key: %, scancode: %, mods: %\n",
				key, scancode, mods);
	}

	void				onKeyDown(int key, int scancode, int mods)
	{
		ft::f(std::cout, "Key down; key: %, scancode: %, mods: %\n",
			key, scancode, mods);
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
	GLFWwindow			*_window;
	GlCanvasHolder		_canvasHolder;
	ftui::Activity		_act;
	int					_puzzleSize;
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
