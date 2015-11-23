// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   libftui.hpp                                        :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 11:55:01 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/23 19:24:38 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LIBFTUI_H
# define LIBFTUI_H

# include "ft/assert.hpp"

namespace ftui
{

/*
** libftui
** TODO: move all this comments to their respective header
*/

/*
** ========================================================================== **
** AView inheritance
** -
** AView							# Base class
** 	->	ASolidView					# Base class for views with a background
** 		->	SolidView				# Simplest concrete View
** 		->	TextView				# Draw text
** 		->	SliderView				# (TODO)
** 		->	...
** 		->	ALayout					# Base class for layouts
** 			->	VerticalLayout
** 				-> ScrollableLayout	# (TODO)
** 			->	AbsoluteLayout		# (TODO)
** 			->	RelativeLayout		# (TODO)
*/

/*
** ========================================================================== **
** Layout
** -
** Store and order a set of views (it's childs)
** (also dispatch events to it's childs)
** -
** Inside a layout, each childs are associated to a view holder
** 												(impl of IViewHolder)
** -
** Implemented layouts:
** 	VerticalLayout			# Order it's childs vertically
*/

/*
** ========================================================================== **
** Callbacks
** -
** C++	Callback are virtual members and can be overriden,
** 		their default implentation is to call the registered lua function
** Lua	Callback are functions that have to be registered like this:
** 			<view_table>:setCallback("<callback_name>", <callback function>)
** 		The view table is accessible inside the function by using 'self' keyword
** -
** Callback list:
** 	AView
** 		onUpdate			-
** 				Called from it's parent when registered "queryUpdate()"
** 		onMeasure			-
** 				Called from it's parent when registered "queryMeasure()"
** 				Have to measure and set the view requested size by using:
** 					getViewHolder()->setMeasuredSize()
** 		onDraw				Canvas &canvas
** 				Called from it's parent when registered "queryRedraw()"
** 				Have to draw the view into the canvas
** 		onMouseScroll		int x, int y, float delta
** 				Called after the user scroll on the view
** 				Require the view to be registered to hookMouseScroll
** 		onMouseDown			int x, int y, int button, int mods
** 				Called after the user press a mouse button on the view
** 				Require the view to be registered to hookMouseClick
** 		onMouseUp			int x, int y, int button, int mods
** 				Called after the user release a mouse button on the view
** 				Require the view to be registered to hookMouseClick
** 		onMouseMove			int x, int y
** 				Called after the user move the mouse on the view
** 				Require the view to be registered to hookMouseMove
** 		onKeyDown			int key_code, int mods
** 				Called after the user press a key
** 				Require the view to be registered to hookKeyboard
** 		onKeyUp				int key_code, int mods
** 				Called after the user release a key
** 				Require the view to be registered to hookKeyboard
** 		onMouseEnter		int x, int y
** 				Called after the cursor enter the view's bounds
** 				Require the view to be registered to hookMouseMove
** 		onMouseLeave		int x, int y
** 				Called after the cursor leave the view's bounds
** 				Require the view to be registered to hookMouseMove
** 		onAttach			-
** 				Called after a view has been attached to a parent view
** 		onDetach			-
** 				Called before a view is dettached from it's parent
** 		onEvent				std::string const &event, IEventParams *p
** 				Called when an event is fired
** 				Require the view to be registered to this event using:
** 					registerEvent("<event_name>")
** 		onPositionChange	-
** 				Called from the parent when the view position change
** 		onSizeChange		-
** 				Called from the parent when the view size change
** 		onCaptureChange		bool status
** 		onVisibilityChange	bool hidden
** 	ALayout
** 		onChildAttach	TODO
** 		onChildDetach	TODO
** 	SliderView
** 		onValueChange		float value
** 				Called when the value change (by user interation or setValue())
*/

/*
** ========================================================================== **
** Params (xml)
** -
** Params are set when the view is inflating
** Of course, params can be set during runtime
** -
** Any implementation of setParam() should call AView::setParam()
**  in order to handle correctly all params
**  (only if the param is inexploitable)
** So AView::setParam() can call it's view holder's setParam()
** -
** AView		# Available to all views
**		id					(str)	View id (XML exclusive)
** 		alpha				(float)	View transparency
** 		visibility			(bool)
** 		mouse_scroll_target	(bool)
** 		mouse_click_target	(bool)
** 		mouse_move_target	(bool)
** 		keyboard_target		(bool)
** 		activity_scripts	(str)	Script files (separated by ';')
** ASolidView
** 		backgroundColor		(color)	Background color
** 		borderColor			(color)	Border color
** 		borderWidth			(int)	Border width
** VerticalLayout's view holder
** 		marginTop			(int)	Extra margin with the previous view
** 		marginBottom		(int)	Extra margin with the next view
** 		verticalAlign		(enum)	LEFT, CENTER or RIGHT
** 		width				(uint)	Requested width
** 		height				(uint)	Requested height
** TextView
** 		text				(str)	Text to be render
** 		textFont			(str)	Font
** 		textColor			(color)
** 		textSize			(int)
** SliderView
** 		value				(float)	Initial value
** 		maxValue			(float)	Max value
** 		minValue			(float)	Min value
*/

/*
** ========================================================================== **
** Lua methods
** -
** -- Canvas
** Canvas:drawRect(left:int, top:int, right:int, bottom:int, fillColor:int,
** 				strokeColor:int = 0, lineWidth:int = 0)
** Canvas:drawText(text:str, x:int, y:int, color:int, fontSize:int)
** Canvas:measureText(text:str, fontSize:int)
** Canvas:setFont(file_name:str)
*/

/*
** ========================================================================== **
*/

class	Activity;
class	IEventBox;
template<class T, typename... Args>	class EventBox;
class	IEventParams;
template<typename... Args>			class EventParams;
template<typename... Args>			class DefaultEventBox;

class	Canvas;

class	AView;
class	SliderView;
class	TextView;

class	IViewHolder;

class	ALayout;
class	AbsoluteLayout;
class	RelativeLayout;
class	VerticalLayout;

};

#endif
