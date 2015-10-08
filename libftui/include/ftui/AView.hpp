// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   AView.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 12:56:29 by ngoguey           #+#    #+#             //
//   Updated: 2015/10/08 13:38:01 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef AVIEW_HPP
# define AVIEW_HPP

# include "ftui/libftui.hpp"

# include <string>
# include <vector>
# include <unordered_map>

# include "ftui/lua.hpp"

namespace ftui
{

/*
** Represents an UI component
** -
** This is the base class for any UI component
** -
** TODO: Call lua callbacks
*/
class	AView
{
public:
	enum	Query
	{
		UPDATE_QUERY = (1 << 1),
		MEASURE_QUERY = (1 << 2),
		REDRAW_QUERY = (1 << 3),
	};
	enum	Target
	{
		MOUSE_SCROLL_TARGET = (1 << 8),
		MOUSE_CLICK_TARGET = (1 << 9),
		MOUSE_MOVE_TARGET = (1 << 10),
		MOUSE_CAPTURE_TARGET = (1 << 10),
		KEYBOARD_TARGET = (1 << 11),
	};
	enum	Misc
	{
		MOUSE_OVER = (1 << 16),
		HIDDEN = (1 << 17),
	};

	virtual ~AView(void);
	AView(XmlParser const &xml, Activity &a);

/*
** View core
*/
	std::string const			*getId(void) const;
	ALayout						*getParent(void);

	IViewHolder					*getViewHolder(void);
	IViewHolder const			*getViewHolder(void) const;
	void						setViewHolder(IViewHolder *holder);
	virtual void				inflate(XmlParser &xml, Activity &act);

	/*
	** View properties
	*/
	float						getAlpha(void) const;
	bool						isVisible(void) const;
	
	void						setAlpha(float value);
	void						setVisibility(bool hidden);

	bool						isMouseOver(void) const;

	virtual void				setParam(std::string const &k,
										 std::string const &v);

/*
** Callbacks
*/
	/*
	** Queries callbacks
	*/
	virtual void				onUpdate(void);
	virtual void				onMeasure(void);
	virtual void				onDraw(Canvas &canvas);

	/*
	** Low level callbacks
	*/
	virtual bool				onMouseScroll(int x, int y, float delta);
	virtual bool				onMouseDown(int x, int y, int button);
	virtual bool				onMouseUp(int x, int y, int button);
	virtual bool				onMouseMove(int x, int y);
	virtual bool				onKeyDown(int key_code);
	virtual bool				onKeyUp(int key_code);

	/*
	** High level callbacks
	*/
	virtual void				onMouseEnter(void);
	virtual void				onMouseLeave(void);
	virtual void				onEvent(std::string const &event
										, IEventParams *p);
	virtual void				onPositionChange(void);
	// virtual void				onCaptureChange(bool status); //TODO ??
	virtual void				onSizeChange(void);
	virtual void				onVisibilityChange(bool hidden);

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
	bool						isUpdateQueried(void) const;
	bool						isMeasureQueried(void) const;
	bool						isRedrawQueried(void) const;

/*
** Register target
** Some low level callbacks are not enabled by default
*/

	void						hookMouseScroll(bool state);
	void						hookMouseClick(bool state);
	void						hookMove(bool state);
	void						hookMouseCapture(bool state);
	void						hookKeyboard(bool state);

/*
** Query
** Queries a callback for the next frame
*/
	void						queryUpdate(void);
	void						queryMeasure(void);
	void						queryRedraw(void);

protected:
/*
** View core
*/
	IViewHolder					*_holder;
	Activity					&_act;

	std::string const *			_id;
	unsigned long				_flags;
	float						_alpha;

	void						setMouseOver(bool state);

/*
** Static
*/
public:
	struct view_info_s
	{
		typedef AView		*(*factory_t)(XmlParser const &, Activity &);
		typedef std::tuple<std::string, lua_CFunction>	luamethod_t;

		std::string					parent;
		factory_t					factory;
		std::vector<luamethod_t>	luaMethods;
	};

	typedef std::unordered_map<std::string, view_info_s>	views_info_t;
	static views_info_t				viewsInfo;

	static view_info_s::factory_t	getFactory(std::string const &name);

	/*
	 *	registerNewSonView()	Call this function to register your new AViews
	 *  ********************************************************************* **
	 *		It should be done once for all AViews, and before any xml inflating.
	 */
	static void					registerNewSonView(
		std::string const &name
		, std::string const &parent
		, view_info_s::factory_t factory
		, std::vector<view_info_s::luamethod_t> luaMethods);

private:

	static int				setRequestedSizeG(lua_State *l);

	static int				setAlphaG(lua_State *l);
	static int				setVisibilityG(lua_State *l);
	static int				setParamG(lua_State *l);

	static int				hookMouseScrollG(lua_State *l);
	static int				hookMouseClickG(lua_State *l);
	static int				hookMoveG(lua_State *l);
	static int				hookMouseCaptureG(lua_State *l);
	static int				hookKeyboardG(lua_State *l);
	static int				queryUpdateG(lua_State *l);
	static int				queryMeasureG(lua_State *l);
	static int				queryRedrawG(lua_State *l);

	static int				getRequestedSizeG(lua_State *l);
	static int				getPosG(lua_State *l);
	static int				getSizeG(lua_State *l);

	static int				getIdG(lua_State *l);
	static int				getParentG(lua_State *l);
	static int				getAlphaG(lua_State *l);
	static int				isVisibleG(lua_State *l);
	static int				isMouseOverG(lua_State *l);

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

};

#endif // ********************************************************* AVIEW_HPP //
