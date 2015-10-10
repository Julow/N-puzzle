// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 11:54:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/10 10:49:28 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ft/utils.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <string>     // std::string, std::to_string

#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/ALayout.hpp"
#include "ftui/luaCFunctions_helpers.hpp"
#include "ftui/lua.hpp"

#include "GlCanvasHolder.hpp"
#include "SolidView.hpp"
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

/*
** Print tree of view
*/

void		printViewTree(ftui::AView const *view, int indent = 0)
{
	ftui::ALayout const	*layout;

	std::cout << std::setfill('\t') << std::setw(indent) << "";
	std::cout << typeid(*view).name();
	if (view->getId() != NULL)
		std::cout << " #" << *(view->getId());
	if (view->getViewHolder() != nullptr)
		ft::f(std::cout, " <(%, %) / (%, %)>",
			view->getViewHolder()->getPos().x,
			view->getViewHolder()->getPos().y,
			view->getViewHolder()->getSize().x,
			view->getViewHolder()->getSize().y);
	if (view->getAlpha() < 1.f)
		std::cout << " alpha=" << view->getAlpha();
	layout = dynamic_cast<ftui::ALayout const*>(view);
	if (layout != NULL)
		std::cout << ':';
	std::cout << std::endl;
	if (layout != NULL)
		for (int i = 0; i < layout->size(); i++)
			printViewTree(layout->at(i), indent + 1);
}

/*
** -
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
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

/*
** -
*/
		_canvasHolder.init();

		printViewTree(_act.getRoot());

/*
** test
*/
		lua_State *l = _act.getLuaState(); //don't remove please

		// std::cout << "caca" << std::endl;
		// luaL_dostring(l, "ftpt(_G);");
		// std::cout << "caca2" << std::endl;
		// luaL_dostring(l, "ftparents = function(t) repeat print('Table id: ', t:getId()); ftpt(t); t = t:getParent(); until t == nil; end");
		// luaL_dostring(l, "for k, v in pairs(_G) do print('salut'); end;");
		// luaL_dostring(l, "for k, v in pairs(_G) do if type(k) == 'userdata' then print('**********EXPANDING:'); ftparents(v); end; end;");
		luaL_dostring(l, "ft_psons(UIParent);");
		// luaL_dostring(l, "local t = UIParent; local n = t:size(); print('size:', n);");
		// luaL_dostring(l, "ftpt(lol);");
		// std::cout << "caca3" << std::endl;
		// luaL_dostring(l, "print('salut');");
		// luaL_dostring(l, "ftpt(lol:getParent());");
		// std::cout << "caca4" << std::endl;
	}

	void				loop(void)
	{
		ftui::Canvas		canvas(_canvasHolder.getCanvas());
		while (!glfwWindowShouldClose(_window))
		{
			glfwPollEvents();
			glClearColor(1, 1, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			// canvas.clear();
			_act.render(canvas);
			_canvasHolder.render();
			glfwSwapBuffers(_window);
		}
		printViewTree(_act.getRoot());
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
			return ftui::luaCFunHelper<0, 2>(l, &Main::ret2);
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
	ftui::AView::defineView("SolidView", "AView", ftui::SolidView::create_view, {});
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
