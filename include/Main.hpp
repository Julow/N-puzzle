// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 12:58:38 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/17 14:46:00 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef MAIN_HPP
# define MAIN_HPP

//TODO: move to own file
class Main;
class StartState;
//TODO: move to own file

# include <iostream>

# include "ftlua/ftlua.hpp"
# include "gl/gl.hpp"

# include "GlCanvasHolder.hpp"
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
	GLFWwindow									*_window;
	GlCanvasHolder								_canvasHolder;
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
