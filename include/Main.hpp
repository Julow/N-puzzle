// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Main.hpp                                           :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 12:58:38 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/08 19:19:03 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#include <iostream>

#include "ft/utils.hpp"
#include "config_window.hpp"
#include "GlCanvasHolder.hpp"
#include "gl.hpp"
#include "OCamlBinding.hpp"
#include "IState.hpp"
#include "StartState.hpp"

class Main
{
public:
	Main(void);
	~Main(void);
	void					loop(void);

private:
	static Main				*_instance;
public:
	static Main				*instance(void);
public:
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

protected:

	GLFWwindow				*_window;
	std::unique_ptr<IState>	_state;
	OCamlBinding			_ocaml;

	GlCanvasHolder			_canvasHolder;
};
