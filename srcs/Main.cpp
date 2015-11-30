// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.cpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 10:15:01 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/30 12:05:48 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>
#include <array>

#include "ft/utils.hpp"
#include "ftui/AView.hpp"

#include "libftui_extend/Bookmark.hpp"
#include "Main.hpp"
#include "config_window.hpp"
#include "PickState.hpp"
#include "SolvingState.hpp"

/*
** ************************************************************************** **
** CONSTRUCTION
*/

Main			*Main::instance(void)
{
	static Main		*m = nullptr;

	if (m == nullptr)
	{
		m = new Main();
	}
	return m;
}

void			Main::loadSharedScripts(ftui::Activity &act)
{
	auto				pushFun =
		[&](std::string const &fname, lua_CFunction f)
		{ act.registerLuaCFun_table("Main", fname, f); };
	int					ret;
	lua_State *const	l = act.getLuaState();

	luaL_dostring(l, "Main = {}");
	pushFun("getAlgorithms", &Main::getAlgorithmsG);
	pushFun("getAlgorithmId", &Main::getAlgorithmIdG);

	pushFun("getHeuristics", &Main::getHeuristicsG);
	pushFun("getHeuristicId", &Main::getHeuristicIdG);

	pushFun("getGrid", &Main::getGridG);
	pushFun("getTableToReal", &Main::getGridG);
	pushFun("getCost", &Main::getCostG);
	pushFun("getTableToReal", &Main::getTableToRealG);

	ret = lua_getglobal(l, "Main"); // TTAG push0
	FTASSERT(ret == LUA_TTABLE);

	lua_pushinteger(l, 0);
	lua_pushlightuserdata(l, this);
	lua_settable(l, -3);

	lua_pop(l, 1);
	return ;
}

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

Main::Main(void)
	: _window(nullptr)
	, _canvasHolder(WIN_WIDTHI, WIN_HEIGHTI)
		// , _state()
	, _ocaml()
	, files({"g54m_hard.np", "g60m_hard.np", "g64m_hard.np"})
	, grid(Grid::def)
	, algorithmId(0)
	, heuristicId(0)
	, cost(0)
{
	std::srand(time(NULL));

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
	if ((_window = glfwCreateWindow(WIN_WIDTHI, WIN_HEIGHTI, "npuzzle"
									, NULL, NULL)) == NULL)
		throw std::runtime_error("Cannot create GLFW window");
	glfwMakeContextCurrent(_window);
	if (!INIT_GLEW)
		throw std::runtime_error("Cannot load GLEW");
	glViewport(0, 0, WIN_WIDTHI, WIN_HEIGHTI);
	glfwSetWindowUserPointer(_window, this);
	glfwSetKeyCallback(_window, &Main::handleKeyEvents);
	glfwSetCursorPosCallback(_window, &Main::handleMousePosEvents);
	glfwSetMouseButtonCallback(_window, &Main::handleMouseButtonEvents);
	glfwSetScrollCallback(_window, &Main::handleMouseScrollEvents);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_canvasHolder.init();
	Bookmark::declare_libftui();
}

Main::~Main(void)
{
	_state.reset();
	glfwDestroyWindow(_window);
	glfwTerminate();
}

/*
** ************************************************************************** **
** LOOP
*/

void				Main::loop(void)
{
	ftui::ACanvas		&canvas(_canvasHolder.getCanvas());

	_state.reset(new PickState(*this, _ocaml));
	while (!glfwWindowShouldClose(_window))
	{
		glfwPollEvents();
		// glClearColor(0.f, 0.f, 0.f, c1.f);
		// glClear(GL_COLOR_BUFFER_BIT);
		// canvas.clear();
		_state->loop(_state, canvas);
		_canvasHolder.render();
		glfwSwapBuffers(_window);
	}
}

IBundle				*Main::popBundle(std::string const &str)
{
	auto		it = this->_bundles.find(str);
	IBundle		*b{nullptr};

	if (it != this->_bundles.end())
	{
		b = it->second;
		this->_bundles.erase(it);
	}
	return b;
}

void				Main::pushBundle(std::string const &str, IBundle *b)
{
	bool 	success;

	std::tie(std::ignore, success) = this->_bundles.insert({str, b});
	FTASSERT(success == true, "Key already taken");
	return ;
}


/*
** ************************************************************************** **
** GLFW INTERACTIONS
*/

void			Main::onKeyUp(int key, int scancode, int mods)
{
	if (key == GLFW_KEY_ESCAPE)
		glfwSetWindowShouldClose(_window, true);
	else
		_state->getActivity().onKeyUp(key, mods);
	(void)scancode;
}

void			Main::onKeyDown(int key, int scancode, int mods)
{
	ftui::Activity &act = _state->getActivity();
	lua_State		*l = _state->getActivity().getLuaState();


	std::cout << key << std::endl;
	if (key == 75)
	{
		std::cout << "fire event" << std::endl;
		_state->getActivity().fireEvent(
			// "Bordel", 42);
		"Bordel", 42, std::string("bordel"));
			// "Bordel", 42, ft::Vec3<double>(1., -42., 8.));
	}
	if (key == 84)
	{
		this->_ocaml.transposition_toabstract(3);
	}
	if (key == 32)
	{
		std::cout << "set cpp callback" << std::endl;

		ftlua::push(l, ftlua::make_keys("Bookmark2"));
		Bookmark	*k = ftlua::retrieveSelf<Bookmark>(l, -1);

		act.registerEvent("Bordel", k, &Bookmark::onBordel);


	}
	_state->getActivity().onKeyDown(key, mods);
	(void)scancode;
}

void			Main::onMouseMove(int x, int y)
{
	_state->getActivity().onMouseMove(x, y);
}

void			Main::onMouseScroll(float delta)
{
	_state->getActivity().onMouseScroll(delta);
}

void			Main::onMouseUp(int x, int y, int button, int mods)
{
	_state->getActivity().onMouseUp(x, y, button, mods);
}

void			Main::onMouseDown(int x, int y, int button, int mods)
{
	_state->getActivity().onMouseDown(x, y, button, mods);
}

void			Main::handleKeyEvents(
	GLFWwindow *window, int key, int scancode, int action, int mods)
{
	Main		*main;

	main = reinterpret_cast<Main*>(glfwGetWindowUserPointer(window));
	FTASSERT(main != NULL);
	if (action == GLFW_RELEASE)
		main->onKeyUp(key, scancode, mods);
	else if (action == GLFW_PRESS)
		main->onKeyDown(key, scancode, mods);
}

void			Main::handleMousePosEvents(GLFWwindow *window,
					double x, double y)
{
	Main		*main;

	main = reinterpret_cast<Main*>(glfwGetWindowUserPointer(window));
	FTASSERT(main != NULL);
	main->onMouseMove(x, y);
}

void			Main::handleMouseScrollEvents(GLFWwindow *window,
					double, double y)
{
	Main		*main;

	main = reinterpret_cast<Main*>(glfwGetWindowUserPointer(window));
	FTASSERT(main != NULL);
	main->onMouseScroll(y);
}

void			Main::handleMouseButtonEvents(
	GLFWwindow *window, int button, int action, int mods)
{
	Main		*main;
	double		pos[2];

	main = reinterpret_cast<Main*>(glfwGetWindowUserPointer(window));
	FTASSERT(main != NULL);
	glfwGetCursorPos(window, pos + 0, pos + 1);
	if (action == GLFW_PRESS)
		main->onMouseDown(static_cast<int>(pos[0]), static_cast<int>(pos[1])
							, button, mods);
	else
		main->onMouseUp(static_cast<int>(pos[0]), static_cast<int>(pos[1])
						, button, mods);
}

/*
** ************************************************************************** **
** LIBFTUI INTERACTIONS
*/

int				Main::getTableToRealG(lua_State *l) /*static*/
{
	return ftlua::handle<2, 1>(l, &Main::getTableToReal);
}
std::vector<int>        Main::getTableToReal(int i)
{ return {this->_ocaml.transposition_toreal(i)}; }


int				Main::getGridG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 1>(l, &Main::getGrid);
}
Grid const		&Main::getGrid(void) const
{ return this->grid; }



int							Main::getAlgorithmsG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 1>(l, &Main::getAlgorithms);
}
std::vector<std::string>	Main::getAlgorithms(void)
{
	return _ocaml.algorithm_list();
}
int							Main::getAlgorithmIdG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 1>(l, &Main::getAlgorithmId);
}
int							Main::getAlgorithmId(void) const
{ return this->algorithmId; }



int							Main::getHeuristicsG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 1>(l, &Main::getHeuristics);
}
std::vector<std::string>	Main::getHeuristics(void)
{
	return _ocaml.heuristic_list();
}
int							Main::getHeuristicIdG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 1>(l, &Main::getHeuristicId);
}
int							Main::getHeuristicId(void) const
{ return this->heuristicId; }




int				Main::getCostG(lua_State *l) /*static*/
{
	return ftlua::handle<1, 1>(l, &Main::getCost);
}
int				Main::getCost(void) const
{ return this->cost; }


int				main(void)
{
	try
	{
		Main *const	main = Main::instance();

		main->loop();
		delete main;
	}
	catch (std::exception const &e)
	{
		std::cout << "lol: " << e.what() << std::endl;
	}
	return (0);
}
