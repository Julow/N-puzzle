// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:16:33 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/17 17:17:43 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ACTIVITY_HPP
# define ACTIVITY_HPP

# include "ftui/libftui.hpp"
# include "ft_xml/XmlParser.hpp"

# include <vector>
# include <unordered_map>
# include <string>
# include <istream>

# include "ftui/IViewHolder.hpp"
# include "ftlua/ftlua.hpp"

namespace ftui
{

/*
** Activity
** -
** Holds the whole UI
** Multiple activity can cohabit but there is no facility for that
*/
class	Activity
{
public:
	class	RootViewHolder;

	typedef std::unordered_multimap<std::string, IEventBox*>	event_map_t;

	Activity(ft::Vec2<int> size);
	virtual ~Activity(void);

	void				inflate(std::istream &stream);
	void				saveScriptPath(std::string const &str);

	static int			createViewG(lua_State *l);
	static Activity		*retrieveActivity(lua_State *l);
	void				pushActivity(void);

	lua_State			*getLuaState(void) const;
	AView				*getRoot(void);
	AView const			*getRoot(void) const;

	void				render(Canvas &canvas);

	void				queryRedrawAll(void);
	void				queryMeasureAll(void);
	void				queryUpdateAll(void);

	bool				onKeyUp(int key_code, int mods);
	bool				onKeyDown(int key_code, int mods);

	void				onMouseMove(int x, int y);

	void				onMouseUp(int x, int y, int button, int mods);
	bool				onMouseDown(int x, int y, int button, int mods);

	/*
	 *	registerEvent(e,v)		Registers an event for a given view:
	 * 								- DerivedView::onEvent()	c++ method
	 * 								- self:fname()				lua callback
	 * 								- self:onEvent()			lua method
	 * 	registerEvent(e,v,c)	Registers an event for a given view:
	 *								- DerivedView::fname()		c++ callback
	 *	unregisterEvent(e,v)	Unregisters a view from an event
	 * 	********************************************************************* **
	 *	AView::onEvent handles the call to lua.
	 * 	********************************************************************* **
	 *	onFire case1: (c++ callback)
	 *		DerivedView::fname()		->(optional)	AView::onEvent()
	 *		AView::onEvent			->			self:fname() || self:onEvent()
	 *	*
	 *	onFire case2: (AView::onEvent extended)
	 *		DerivedView::onEvent()	->(optional)	AView::onEvent()
	 *		AView::onEvent			->			self:fname() || self:onEvent()
	 *	*
	 *	onFire case3: (AView::onEvent notextended)
	 *		AView::onEvent			->			self:fname() || self:onEvent()
	 */
	template<typename... Args>
	void				registerEvent(std::string const &event, AView *v);
	template<class T, typename... Args>
	void				registerEvent(
		std::string const &event, AView *v, bool (T::*callback)(Args...));
	void				unregisterEvent(std::string const &event, AView *v);

	/*
	 *	fireEvent()			fires an event in the multimap:
	 * 	********************************************************************* **
	 *		If the given Args... types do no match those from registerEvent, a
	 *	dynamic_cast may rise an exception.
	 */
	template<typename... Args>
	bool				fireEvent(std::string const &event, Args... args);

	/*
	 *	registerGFun() 		Registers a cfun to lua _G
	 *	registerMemfuns()	Registers several cfuns to a specific table in _G
	 * 	********************************************************************* **
	 *		The user must handle the lua-stack in those functions. Two optional
	 *	functions are available to assist you in the process:
	 *		- ftui::LOLfun
	 *		- ftui::LOLmemfun
	 */
	void				registerLuaCFun_global(
		std::string const &funName, lua_CFunction f);
	void				registerLuaCFun_table(
		std::string const &tabName
		, std::string const &funName
		, lua_CFunction f);

protected:
	RootViewHolder		*_rootView;
	event_map_t			_eventMap;
	ft::Vec2<int>		_size;
	lua_State			*_l;
	std::vector<std::string>	_scriptsPaths;

private:
	Activity(void) = delete;
	Activity(Activity const &src) = delete;
	Activity			&operator=(Activity const &rhs) = delete;

};

/*
** Activity::RootViewHolder
** -
** Hold the root view
*/
class	Activity::RootViewHolder : public IViewHolder
{
public:
	RootViewHolder(Activity &act, ft::XmlParser const &xml, AView *v,
					ft::Vec2<int> s);
	virtual ~RootViewHolder(void);

	virtual ALayout			*getParent(void);
	virtual ALayout const	*getParent(void) const;

	virtual AView			*getView(void);
	virtual AView const		*getView(void) const;

	virtual ft::Vec2<int>	getPos(void) const;
	virtual ft::Vec2<int>	getSize(void) const;

	virtual void			setRequestedSize(ft::Vec2<int> size);
	virtual ft::Vec2<int>	getRequestedSize(void) const;

	virtual void			setParam(std::string const &k
									, std::string const &v);

	void					setSize(ft::Vec2<int> size);

protected:

	Activity				&_activity;
	AView					*_view;
	ft::Vec2<int>			_size;
	ft::Vec2<int>			_requestedSize;

private:
	RootViewHolder(void) = delete;
	RootViewHolder(RootViewHolder const &src) = delete;
	RootViewHolder			&operator=(RootViewHolder const &rhs) = delete;
};

};

# include "ftui/templates/Activity.tpp"

#endif
