// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 12:56:29 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/07 14:35:39 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AVIEW_HPP
# define AVIEW_HPP

# include <string>
# include <vector>
# include <unordered_map>
# include <stdint.h>

# include "ft_xml/XmlParser.hpp"

# include "ftlua/ftlua.hpp"

# include "ftui/ACanvas.hpp"
# include "ftui/IViewHolder.hpp"
# include "ftui/ViewTemplate.hpp"

namespace ftui
{

class	Activity;

/*
** ========================================================================== **
** AView
** -
** Represents an UI component
** This is the base class for any UI component
** -
** Params:
**	id					(str)	View id (XML exclusive)
** 	alpha				(float)	View transparency
** 	visibility			(bool)
** 	mouse_scroll_target	(bool)
** 	mouse_click_target	(bool)
** 	mouse_move_target	(bool)
** 	keyboard_target		(bool)
** 	activity_scripts	(str)	Script files (separated by ';')
** -
** Callbacks:
** 	onUpdate			-
**	 			Called from it's parent when registered "queryUpdate()"
** 	onMeasure			-
**	 			Called from it's parent when registered "queryMeasure()"
**	 			Have to measure and set the view requested size by using:
**	 				getViewHolder()->setMeasuredSize()
** 	onDraw				ACanvas &canvas
**	 			Called from it's parent when registered "queryRedraw()"
**	 			Have to draw the view into the canvas
** 	onMouseScroll		int x, int y, float delta
**	 			Called after the user scroll on the view
**	 			Require the view to be registered to hookMouseScroll
** 	onMouseDown			int x, int y, int button, int mods
**	 			Called after the user press a mouse button on the view
**	 			Require the view to be registered to hookMouseClick
** 	onMouseUp			int x, int y, int button, int mods
**	 			Called after the user release a mouse button on the view
**	 			Require the view to be registered to hookMouseClick
** 	onMouseMove			int x, int y
**	 			Called after the user move the mouse on the view
**	 			Require the view to be registered to hookMouseMove
** 	onKeyDown			int key_code, int mods
**	 			Called after the user press a key
**	 			Require the view to be registered to hookKeyboard
** 	onKeyUp				int key_code, int mods
**	 			Called after the user release a key
**	 			Require the view to be registered to hookKeyboard
** 	onMouseEnter		int x, int y
**	 			Called after the cursor enter the view's bounds
**	 			Require the view to be registered to hookMouseMove
** 	onMouseLeave		int x, int y
**	 			Called after the cursor leave the view's bounds
**	 			Require the view to be registered to hookMouseMove
** 	onAttach			-
**	 			Called after a view has been attached to a parent view
** 	onDetach			-
**	 			Called before a view is dettached from it's parent
** 	onEvent				std::string const &event, IEventParams *p
**	 			Called when an event is fired
**	 			Require the view to be registered to this event using:
**	 				registerEvent("<event_name>")
** 	onPositionChange	-
**	 			Called from the parent when the view position change
** 	onSizeChange		-
**	 			Called from the parent when the view size change
** 	onCaptureChange		bool status
** 	onVisibilityChange	bool hidden
*/
class	AView
{
public:
	enum		Query
	{
		UPDATE_QUERY = (1 << 1),
		MEASURE_QUERY = (1 << 2),
		REDRAW_QUERY = (1 << 3),
	};
	enum		Target
	{
		MOUSE_SCROLL_TARGET = (1 << 8),
		MOUSE_CLICK_TARGET = (1 << 9),
		MOUSE_MOVE_TARGET = (1 << 10),
		MOUSE_CAPTURE_TARGET = (1 << 11),
		KEYBOARD_TARGET = (1 << 12)
	};
	enum		Misc
	{
		MOUSE_OVER = (1 << 16),
		HIDDEN = (1 << 17),
		ATTACHED = (1 << 18)
	};
	enum class	LuaCallback : uint32_t
	{
		MOUSE_SCROLL = 1,
		MOUSE_DOWN,
		MOUSE_UP,
		MOUSE_MOVE,
		KEY_DOWN,
		KEY_UP,
		MOUSE_ENTER,
		MOUSE_LEAVE,
		EVENT,
		POSITION_CHANGE,
		CAPTURE_CHANGE,
		SIZE_CHANGE,
		VISIBILITY_CHANGE,
		UPDATE,
		MEASURE,
		DRAW,
		ATTACH,
		DETACH,
		__LAST
	};

	typedef ft::XmlParser::params_map_t		param_map_t;
	class	ParamMap;

	AView(Activity &act, std::string const &viewName);
	virtual ~AView(void);

	typedef std::integral_constant<unsigned int, 1>	ftlua_size;
	void			ftlua_push(lua_State *l, std::function<void(std::string)> panic);
	static AView	*ftlua_pop(lua_State *l, int i, std::function<void(std::string)> panic);

	/*
	** Extract the view tree from a xml file
	** `v->inflate()` is always called after 'v' has been put in his parent
	** -
	** View creation:
	** v = new ...View(...) // More often: Activity::getFactory("...")(xml, act)
	** v->setHolder(...)	// if any
	** v->inflate(xml)
	*/
	virtual void				inflate(ViewTemplate const &t,
									ParamMap const *parent_p = nullptr);
	virtual void				inflate(ft::XmlParser &xml,
									ParamMap const *parent_p = nullptr);
	void						inflateParams(param_map_t const &params,
									ParamMap const *parent_p = nullptr);

/*
** View core
*/

	std::string					tostring(void) const;
	std::string const			*getId(void) const;
	ALayout						*getParent(void);

	IViewHolder					*getViewHolder(void);
	IViewHolder const			*getViewHolder(void) const;

	void						setId(std::string const &id);
	void						setMouseOver(int x, int y, bool state);
	void						setViewHolder(IViewHolder *holder);
	void						setAttached(bool state);

	/*
	** View properties
	*/
	float						getAlpha(void) const;
	bool						isVisible(void) const;

	void						setAlpha(float value);
	void						setVisibility(bool hidden);

	bool						isMouseOver(void) const;
	bool						isAttached(void) const;

	/*
	** Set param
	** used to retrieve param from XML
	** -
	** CustomView::setParam()	is called from AView::inflate()
	** AView::setParam()		is called from CustomView::setParam()
	** IViewHolder::setParam()	is called from AView::setParam()
	*/
	virtual void				setParam(std::string const &key,
										 std::string const &value);

/*
** Callbacks
*/
	/*
	** Queries callbacks
	*/
	virtual void				onUpdate(void);
	virtual void				onMeasure(void);
	virtual void				onDraw(ACanvas &canvas);

	/*
	** Low level callbacks
	*/
	virtual bool				onMouseScroll(int x, int y, float delta);
	virtual bool				onMouseDown(int x, int y, int button, int mods);
	virtual bool				onMouseUp(int x, int y, int button, int mods);
	virtual bool				onMouseMove(int x, int y);
	virtual bool				onKeyDown(int key_code, int mods);
	virtual bool				onKeyUp(int key_code, int mods);

	/*
	** High level callbacks
	*/
	virtual void				onMouseEnter(int x, int y);
	virtual void				onMouseLeave(int x, int y);
	virtual void				onAttach(void);
	virtual void				onDetach(void);
	// virtual void				onEvent(std::string const &event
										// , IEventParams *p);
	virtual void				onPositionChange(void);
	// virtual void				onCaptureChange(bool status); //TODO ??
	virtual void				onSizeChange(ft::Vec2<int> size);
	virtual void				onVisibilityChange(bool hidden);

	/*
	** Used to set/unset a lua callback (from lua)
	*/
	void						setLuaCallback(lua_State *l);
	void						registerEvent(std::string const &str);
	void						unregisterEvent(std::string const &str);

/*
** Layout system
*/
	/*
	** Targets
	*/
	virtual bool				isMouseScrollTargeted(void) const;
	virtual bool				isMouseClickTargeted(void) const;
	virtual bool				isMouseMoveTargeted(void) const;
	virtual bool				isMouseCaptureTargeted(void) const;
	virtual bool				isKeyboardTargeted(void) const;

	/*
	** Queries
	*/
	virtual bool				isUpdateQueried(void) const;
	virtual bool				isMeasureQueried(void) const;
	virtual bool				isRedrawQueried(void) const;

/*
** Register target
** Some low level callbacks are not enabled by default
*/

	void						hookMouseScroll(bool state);
	void						hookMouseClick(bool state);
	void						hookMouseMove(bool state);
	void						hookMouseCapture(bool state);
	void						hookKeyboard(bool state);

/*
** Query
** Queries a callback for the next frame
*/
	virtual void				queryUpdate(void);
	virtual void				queryMeasure(void);
	virtual void				queryRedraw(void);

protected:
/*
** View core
*/
	IViewHolder					*_holder;
	Activity					&_act;

	std::string const			*_id;
	uint32_t					_flags;
	uint32_t					_luaCallbacks;
	float						_alpha;

/*
** inflateParams
*/
	void						setParam2(std::string const &key,
									std::string const &value,
									ParamMap const *param_map);

/*
** Callbacks
*/
	/*
	** Return false and do nothing if the callback is not registered
	** otherwise call the lua callback and return true
	** Call luaL_error on error
	** -
	** Warning: ftui/templates/AView_callLuaCallback.tpp have to be included
	*/
	template<typename ...ARGS>
	bool						callLuaCallback(lua_State *l, LuaCallback id,
									ARGS const &...args);
	template<typename ...ARGS>
	bool						callLuaCallback(lua_State *l, uint32_t id,
									ARGS const &...args);

public:
	static int				getIdG(lua_State *l);
	static int				getParentG(lua_State *l);
	static int				getAlphaG(lua_State *l);
	static int				isVisibleG(lua_State *l);
	static int				isMouseOverG(lua_State *l);
	static int				setIdG(lua_State *l);
	static int				setVisibilityG(lua_State *l);
	static int				setAlphaG(lua_State *l);

	static int				getPosG(lua_State *l);
	static int				getSizeG(lua_State *l);
	static int				getRequestedSizeG(lua_State *l);
	static int				setRequestedSizeG(lua_State *l);

	static int				setParamG(lua_State *l);
	static int				setCallbackG(lua_State *l);
	static int				registerEventG(lua_State *l);
	static int				unregisterEventG(lua_State *l);

	static int				hookMouseScrollG(lua_State *l);
	static int				hookMouseClickG(lua_State *l);
	static int				hookMouseMoveG(lua_State *l);
	static int				hookMouseCaptureG(lua_State *l);
	static int				hookKeyboardG(lua_State *l);

	static int				queryUpdateG(lua_State *l);
	static int				queryMeasureG(lua_State *l);
	static int				queryRedrawG(lua_State *l);

	static int				isMouseScrollTargetedG(lua_State *l);
	static int				isMouseClickTargetedG(lua_State *l);
	static int				isMouseMoveTargetedG(lua_State *l);
	static int				isMouseCaptureTargetedG(lua_State *l);
	static int				isKeyboardTargetedG(lua_State *l);
	static int				isUpdateQueriedG(lua_State *l);
	static int				isMeasureQueriedG(lua_State *l);
	static int				isRedrawQueriedG(lua_State *l);

/*
** Disable
*/
private:
	AView() = delete;
	AView(AView const &src) = delete;
	AView				&operator=(AView const &rhs) = delete;
};

class	AView::ParamMap
{
public:
	ParamMap(param_map_t const &params, ParamMap const *prev);
	virtual ~ParamMap(void);

	param_map_t const	&params;
	ParamMap const		*prev;

	std::string const	*find(std::string const &key) const;

protected:

private:
	ParamMap(void) = delete;
	ParamMap(ParamMap &&src) = delete;
	ParamMap(ParamMap const &src) = delete;
	ParamMap			&operator=(ParamMap &&rhs) = delete;
	ParamMap			&operator=(ParamMap const &rhs) = delete;
};

};

# include "ftui/templates/AView_callLuaCallback.tpp"

#endif
