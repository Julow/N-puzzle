// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 12:58:38 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/12 19:19:48 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAIN_HPP
# define MAIN_HPP

//TODO: move to own file
class Main;
class StartState;
# define MATRIX33I(...) std::array<int*, 3>{{__VA_ARGS__}}.data()
# define LINE3I(...) std::array<int, 3>{{__VA_ARGS__}}.data()
# define DEFGRID Grid(MATRIX33I(LINE3I(0,1,2), LINE3I(3,4,5), LINE3I(6,7,8)), 3)
//TODO: move to own file

# include <iostream>

# include "ftlua/ftlua.hpp"
# include "gl.hpp"

# include "GlCanvasHolder.hpp"
# include "OCamlBinding.hpp"
# include "IState.hpp"
# include "Grid.hpp"

class Main
{
	/* CONSTRUCTION ***************** */
public:
	static Main				*instance(void);
	static void				loadSharedScripts(ftui::Activity &a);

private:
	Main(void);
public:
	~Main(void);

	/* LOOP ************************* */
public:
	void					loop(void);

public:
	/* GLFW INTERACTIONS ************ */
	void					onMouseMove(int x, int y);
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

	/* LIBFTUI INTERACTIONS ********* */
	// static int				getAlgorithms(lua_State *l);
	// static int				getHeuristics(lua_State *l);
	// static int				getTranspToReal(lua_State *l);

	static int				getGridG(lua_State *l);
	Grid const				&getGrid(void) const;

	static int				getAlgorithmIdG(lua_State *l);
	int						getAlgorithmId(void) const;

	static int				getHeuristicIdG(lua_State *l);
	int						getHeuristicId(void) const;

	static int				getCostG(lua_State *l);
	int						getCost(void) const;


private:
	GLFWwindow				*_window;
	GlCanvasHolder			_canvasHolder;
	std::unique_ptr<IState>	_state;
	OCamlBinding			_ocaml;

public:

	Grid					grid;
	unsigned int			algorithmId;
	unsigned int			heuristicId;
	int						cost;

};

#endif
