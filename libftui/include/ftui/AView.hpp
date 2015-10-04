/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   AView.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 12:56:29 by ngoguey           #+#    #+#             */
//   Updated: 2015/10/04 12:42:16 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef AVIEW_HPP
# define AVIEW_HPP

# include "ftui/libftui.hpp"

# include <string>
# include <vector>
# include <unordered_map>

extern "C"
{
# include <lua.h>
# include <lauxlib.h>
# include <lualib.h>
}

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
	virtual void				onDraw(ACanvas &canvas);

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

	std::string const *const	_id;
	unsigned long				_flags;
	float						_alpha;

	void						setMouseOver(bool state);

/*
** Static
*/
public:
	class Son
	{
	public:
		typedef AView		*(*factory_t)(XmlParser const &, Activity &);
		typedef std::tuple<std::string, lua_CFunction>	luamemfuninfo_t;
		typedef std::vector<luamemfuninfo_t>			luamemfunsinfo_t;
		
		virtual ~Son(void);		
		Son(factory_t create, luamemfunsinfo_t luaMemfuns);
		Son(Son const &src);
		Son();
		Son			&operator=(Son const &rhs);

		factory_t			create;
		luamemfunsinfo_t	luaMemfuns;
	};

	typedef std::unordered_map<std::string, Son>	views_info_t;
	static views_info_t									_views_info;

	static Son::factory_t	getFactory(std::string const &name);

	/*
	 *	registerNewView()	Call this function to register your new AViews
	 *  ********************************************************************* **
	 *		It should be done once for all instanciable AViews, and before any
	 *	Xml inflating.
	 */
	static void					registerNewView(
		std::string const &name
		, Son::factory_t factory
		, Son::luamemfunsinfo_t luaMemFuns);

private:

	static void			setRequestedSize(lua_State *l);

	static void			setAlpha(lua_State *l);
	static void			setVisibility(lua_State *l);
	static void			setParam(lua_State *l);

	static void			hookMouseScroll(lua_State *l);
	static void			hookMouseClick(lua_State *l);
	static void			hookMove(lua_State *l);
	static void			hookMouseCapture(lua_State *l);
	static void			hookKeyboard(lua_State *l);
	static void			queryUpdate(lua_State *l);
	static void			queryMeasure(lua_State *l);
	static void			queryRedraw(lua_State *l);

	static void			getRequestedSize(lua_State *l);
	static void			getPos(lua_State *l);
	static void			getSize(lua_State *l);

	static void			getId(lua_State *l);
	static void			getParent(lua_State *l);
	static void			getAlpha(lua_State *l);
	static void			isVisible(lua_State *l);
	static void			isMouseOver(lua_State *l);

	static void			isMouseScrollTargeted(lua_State *l);
	static void			isMouseClickTargeted(lua_State *l);
	static void			isMouseMoveTargeted(lua_State *l);
	static void			isMouseCaptureTargeted(lua_State *l);
	static void			isKeyboardTargeted(lua_State *l);
	static void			isUpdateQueried(lua_State *l);
	static void			isMeasureQueried(lua_State *l);
	static void			isRedrawQueried(lua_State *l);

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
