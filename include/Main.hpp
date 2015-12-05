// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 12:58:38 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/05 17:00:38 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAIN_HPP
# define MAIN_HPP

# include <iostream>

# include "gl/gl.hpp"

# include "gl_canvas/GlCanvasHolder.hpp"
# include "OCamlBinding.hpp"
# include "IState.hpp"
# include "IBundle.hpp"
# include "Grid.hpp"

class Main
{
	/* CONSTRUCTION ***************** */
public:
	static Main				*instance(void);
	void					loadSharedScripts(ftui::Activity &a);

private:
	Main(void);
public:
	~Main(void);

	/* LOOP ************************* */
public:
	void					loop(void);
	IBundle					*popBundle(std::string const &str);
	void					pushBundle(std::string const &str, IBundle *b);

public:
	/* GLFW INTERACTIONS ************ */
	void					onMouseMove(int x, int y);
	void					onMouseScroll(float delta);
	void					onKeyUp(int key, int scancode, int mods);
	void					onKeyDown(int key, int scancode, int mods);
	void					onMouseUp(int x, int y, int button, int mods);
	void					onMouseDown(int x, int y, int button, int mods);

	static void				handleKeyEvents(
		GLFWwindow *window, int key, int scancode, int action, int mods);
	static void				handleMousePosEvents(
		GLFWwindow *window, double x, double y);
	static void				handleMouseButtonEvents(
		GLFWwindow *window, int button, int action, int mods);
	static void				handleMouseScrollEvents(GLFWwindow *window,
													double, double y);

	/* LIBFTUI INTERACTIONS ********* */
	typedef std::integral_constant<unsigned int, 1> ftlua_size;
	//TODO: Push application's classes too
	static Main	*ftlua_pop(lua_State *l, int i, std::function<void(std::string)> panic)
		{
			Main		*v;
			int			type;

			FTLUA_STACKASSERT_PANIC(
				l, lua_istable(l, i), panic
				, ft::f("Main::ftlua_pop(i = %)", i), ft::f("No table at i"));
			ftlua::push(l, 0);
			type = lua_gettable(l, i < 0 ? i - 1 : i);
			FTLUA_STACKASSERT_PANIC(
				l, type == LUA_TLIGHTUSERDATA, panic
				, ft::f("Main::ftlua_pop(i = %)", i), ft::f("No pointer at [0]"));
			v = reinterpret_cast<Main*>(lua_touserdata(l, -1));
			lua_pop(l, 1);
			lua_remove(l, i);
			return v;
		}


	static int					getAlgorithmsG(lua_State *l);
	std::vector<std::string>	getAlgorithms(void);

	static int					getHeuristicsG(lua_State *l);
	std::vector<std::string>	getHeuristics(void);

	static int				getTableToRealG(lua_State *l);
	std::vector<int>		getTableToReal(int i);


	static int				getGridG(lua_State *l);
	Grid const				&getGrid(void) const;
	Grid					getGridToReal(void);

	static int				getAlgorithmIdG(lua_State *l);
	int						getAlgorithmId(void) const;

	static int				getHeuristicIdG(lua_State *l);
	int						getHeuristicId(void) const;

	static int				getCostG(lua_State *l);
	int						getCost(void) const;


private:
	GLFWwindow									*_window;
	gl::GlCanvasHolder							_canvasHolder;
	std::unique_ptr<IState>						_state;
	OCamlBinding								_ocaml;
	std::unordered_map<std::string, IBundle*>	_bundles;

public:

	std::vector<std::string>					files;
	Grid										grid;
	unsigned int								algorithmId;
	unsigned int								heuristicId;
	int											cost;

};

#endif
