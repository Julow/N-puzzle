// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Activity.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/09/22 13:16:33 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/07 14:04:33 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ACTIVITY_HPP
# define ACTIVITY_HPP

# include <vector>
# include <unordered_map>
# include <string>
# include <istream>

# include "ft_xml/XmlParser.hpp"

# include "ftui/ACanvas.hpp"
# include "ftui/AView.hpp"
# include "ftui/EventTarget.hpp"
# include "ftui/IViewHolder.hpp"
# include "ftui/ViewTemplate.hpp"

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
	typedef ft::XmlParser::params_map_t			params_map_t;

	// ====================================================================== //
	// Interactions with application
	// ====================================================================== //

	// CONSTRUCTION ================= //
	Activity(ft::Vec2<int> size);
	void				inflate(std::istream &stream);
	void				inflateTemplate(std::istream &stream);

	virtual ~Activity(void);

	Activity(void) = delete;
	Activity(Activity const &src) = delete;
	Activity			&operator=(Activity const &rhs) = delete;

	// LOOP TIME ==================== //
	void				render(ACanvas &canvas);

	bool				onKeyUp(int key_code, int mods);
	bool				onKeyDown(int key_code, int mods);
	void				onMouseMove(int x, int y);
	void				onMouseScroll(float delta);
	void				onMouseUp(int x, int y, int button, int mods);
	bool				onMouseDown(int x, int y, int button, int mods);

	void				queryRedrawAll(void);
	void				queryMeasureAll(void);
	void				queryUpdateAll(void);

	/*
	** ====================================================================== **
	** View template
	*/
	ViewTemplate const	*getViewTemplate(std::string const &name) const;

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
	void				registerEvent(std::string const &event, AView *v);
	template<class T, typename... Args>
	void				registerEvent(
		std::string const &event, T *v, bool (T::*callback)(Args...));
	void				unregisterEvent(std::string const &event, AView *v);

	/*
	 *	fireEvent()			fires an event in the multimap:
	 * 	********************************************************************* **
	 *		If the given Args... types do no match those from registerEvent, a
	 *	dynamic_cast may rise an exception.
	 */
	template<typename... Args>
	bool				fireEvent(std::string const &event, Args... args);

	// ====================================================================== //
	// Lua init
	// ====================================================================== //

	typedef AView		*(*view_factory_t)(Activity &);
	struct	view_info_s
	{
		typedef std::tuple<std::string, lua_CFunction>		luamethod_t;

		std::string					parent;
		view_factory_t				factory;
		std::vector<luamethod_t>	luaMethods;
		std::string					tableInit;
	};
	typedef std::unordered_map<std::string, view_info_s>	views_info_t;
	typedef std::unordered_map<std::string, uint32_t>	callback_map_t;

	static views_info_t				viewsInfo;

	static callback_map_t			callback_map;

	/*
	 *  defineClass()
	 *  Define a view class so that can be created from a xml file
	 *  ********************************************************************* **
	 *  It should be done once for all custom views,
	 *    and before any xml inflating.
	 */
	static void				defineClass(std::string const &name,
						std::string const &parent,
						view_factory_t factory,
						std::vector<view_info_s::luamethod_t> luaMethods = {},
						std::string const &tableInit = {});

	static void						pushViewTemplates(lua_State *l);

	static view_factory_t			getFactory(std::string const &name);

	/*
	** Register a lua callback
	*/
	static void						registerLuaCallback(std::string const &name,
										uint32_t id);

	/*
	 *	registerGFun() 		Registers a cfun to lua _G
	 *	registerMemfuns()	Registers a cfuns to a specific table in _G
	 * 	********************************************************************* **
	 *		The user must handle the lua-stack in the registered functions.
	 * 	(See ftlua)
	 */
	void				registerLuaCFun_global(
		std::string const &funName, lua_CFunction f);
	void				registerLuaCFun_table(
		std::string const &tabName
		, std::string const &funName
		, lua_CFunction f);


	// ====================================================================== //
	// Internal interactions
	// ====================================================================== //

	// CONSTRUCTION ================= //
	void				saveScriptPath(std::string const &str);

	// LOOP TIME ==================== //
	static int			createViewG(lua_State *l);
	static Activity		*retrieveActivity(lua_State *l);

	lua_State			*getLuaState(void) const;
	AView				*getRoot(void);
	AView const			*getRoot(void) const;

protected:
	class	RootViewHolder;

	typedef std::unordered_multimap<std::string, EventTarget*>	event_map_t;
	typedef std::stack<std::pair<std::string, AView*>>		unregister_stack_t;
	typedef std::unordered_map<std::string, ViewTemplate*>	view_template_map_t;

	RootViewHolder				*_rootView;
	event_map_t					_eventMap;
	unregister_stack_t			_unregisterStack;
	ft::Vec2<int>				_size;
	lua_State					*_l;
	std::vector<std::string>	_scriptsPaths;

	ft::Vec2<int>				_cursorPos;

	view_template_map_t			_viewTemplates;

	void				inflateTemplate(ft::XmlParser &xml);

private:

	void			cleanEventMap(void);
	void			removeFromEvents(std::pair<std::string, AView*> const &p);
	template<typename... Args>
	bool			fireEventInternal(std::string const &event, Args... args);
};

/*
** Activity::RootViewHolder
** -
** Hold the root view
*/
class	Activity::RootViewHolder : public IViewHolder
{
public:

	// CONSTRUCTION ================= //
	RootViewHolder(
		Activity &act, ft::XmlParser const &xml, AView *v, ft::Vec2<int> s);
	~RootViewHolder(void);

	RootViewHolder(void) = delete;
	RootViewHolder(RootViewHolder const &src) = delete;
	RootViewHolder		&operator=(RootViewHolder const &rhs) = delete;

	// IVIEWHOLDER LEGACY =========== //
	ALayout				*getParent(void);
	ALayout const		*getParent(void) const;

	AView				*getView(void);
	AView const			*getView(void) const;

	ft::Vec2<int>		getPos(void) const;
	ft::Vec2<int>		getSize(void) const;

	void				setRequestedSize(ft::Vec2<int> size);
	ft::Vec2<int>		getRequestedSize(void) const;

	void				setParam(std::string const &k, std::string const &v);

	// SPECIFIC FUNCTIONS =========== //
	void				setSize(ft::Vec2<int> size);

private:

	Activity			&_activity;
	AView				*_view;
	ft::Vec2<int>		_size;
	ft::Vec2<int>		_requestedSize;

};

};

# include "ftui/templates/Activity.tpp"

#endif
