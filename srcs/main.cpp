// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 11:54:09 by jaguillo          #+#    #+#             //
//   Updated: 2015/10/21 14:57:05 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include "ft/utils.hpp"
#include "config_window.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include <typeinfo>
#include <string>     // std::string, std::to_string

#include "ftui/Activity.hpp"
#include "ftui/AView.hpp"
#include "ftui/ALayout.hpp"
#include "ftlua/ftlua.hpp"
#include "ftui/lua/lua.hpp"

#include "tiles/Tiles.hpp"

#include "GlCanvasHolder.hpp"
#include "gl.hpp"

#include "Solver.hpp"
#include "ISolverListener.hpp"

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
		std::cout << " " << ft::make_rect(view->getViewHolder()->getPos(),
			view->getViewHolder()->getSize());
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


class Main : npuzzle::ISolverListener
{
public:
	Tiles		tiles;
	Main(void) :
		_canvasHolder(WIN_WIDTHI, WIN_HEIGHTI),
		_act(WIN_SIZEVI),
		_puzzleSize(42)
	{


		std::srand(time(NULL));
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
		if ((_window = glfwCreateWindow(WIN_WIDTHI, WIN_HEIGHTI, "npuzzle", NULL, NULL)) == NULL)
			throw std::runtime_error("Cannot create GLFW window");
		glfwMakeContextCurrent(_window);
		if (!INIT_GLEW)
			throw std::runtime_error("Cannot load GLEW");
		glViewport(0, 0, WIN_WIDTHI, WIN_HEIGHTI);
		glfwSetWindowUserPointer(_window, this);
		glfwSetKeyCallback(_window, &Main::handleKeyEvents);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

/*
** -
*/
		_canvasHolder.init();

		tiles.init(WIN_SIZEVI);
		// printViewTree(_act.getRoot());

/*
** test
*/
		lua_State *l = _act.getLuaState(); //don't remove please ;'(

		// luaL_dostring(l, "ft.ptab(UIParent);");
		// luaL_dostring(l, "ft.ptab(ALayout);");
		// luaL_dostring(l, "ft.ptab(VerticalLayout);");
		// luaL_dostring(l, "ft.pchildren(UIParent);");
		// luaL_dostring(l, "setmetatable(ft, ft);");
		// luaL_dostring(l, "ft.ptab(ft);");
		// std::cout << std::endl;

		// luaL_dostring(l, "ft.pparents(solid_test);");
		// ftlua::stackdump(l);

		// luaL_dostring(l, "ft.ptab(_G);");
		// std::cout << "caca4" << std::endl;
		// luaL_dostring(l, "print('backgroundColor:'..solid_test:getBackgroundColor())");

		// luaL_dostring(l, "test:setCallback('onKeyDown', nil)");
		luaL_dostring(l, "test:setCallback('onKeyUp', function (self, key) print('onKeyUp'..tostring(key)..' #'..self:getId()); self:queryRedraw() end)");
		luaL_dostring(l, "test:setCallback('onKeyDown', function (self, key) print('onKeyDown'..tostring(key)..' #'..self:getId()) end)");
/*
** - end
*/
		int top = lua_gettop(_act.getLuaState());
		FTASSERT(top == 0, ft::f("Top not 0: %", top));
	}

/*
** Test solver api
*/
	void				solve(void)
	{
		int const			puzzle_size = 4;
		int					*puzzle[puzzle_size] = {
			new int[puzzle_size]{ 1, 2, 3, 4},
			new int[puzzle_size]{ 5, 6, 7, 8},
			new int[puzzle_size]{ 9,10,11,12},
			new int[puzzle_size]{13,14,15,0}
		};
		npuzzle::Grid		grid(puzzle, puzzle_size);
		npuzzle::Solver		solver(grid, this);

		solver.solve();
		for (int i = 0; i < puzzle_size; i++)
			delete puzzle[i];
		std::cout << "Solving done" << std::endl;
	}

	virtual void	put_progress(float progress)
	{
		std::cout << "Put progress: " << progress << std::endl;
	}
/*
** -
*/

	void				loop(void)
	{
		ftui::Canvas		canvas(_canvasHolder.getCanvas());

		while (!glfwWindowShouldClose(_window))
		{
			glfwPollEvents();
			// glClearColor(0.f, 0.f, 0.f, c1.f);
			// glClear(GL_COLOR_BUFFER_BIT);
			// canvas.clear();
			tiles.render();
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
public:

/*
** events
*/
	void				onKeyUp(int key, int scancode, int mods)
	{
		if (key == GLFW_KEY_ESCAPE)
			glfwSetWindowShouldClose(_window, true);
		else
			_act.onKeyUp(key);
		(void)scancode;
		(void)mods;
	}

	void				onKeyDown(int key, int scancode, int mods)
	{
		_act.onKeyDown(key);
		(void)scancode;
		(void)mods;
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

		main.solve();
		main.loop();
	}
	catch (std::exception const &e)
	{
		std::cout << "lol: " << e.what() << std::endl;
	}
	return (0);
}
