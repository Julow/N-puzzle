/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:16:33 by jaguillo          #+#    #+#             */
//   Updated: 2015/10/02 12:24:13 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIVITY_HPP
# define ACTIVITY_HPP

# include "ftui/libftui.hpp"

# include <vector>
# include <unordered_map>
# include <string>
# include <istream>

# include "ftui/IViewHolder.hpp"
// # include "ftui/EventBox.hpp"
// # include "ftui/EventParams.hpp"

class lua_State; //debug

namespace ftui
{

/*
** Activity
** -
** Hold the whole UI
** Multiple activity can cohabit but there is no facility for that
*/
class	Activity
{
public:
	class	RootViewHolder;

	typedef std::unordered_multimap<std::string, IEventBox*>	event_map_t;

	Activity(Vec2<int> size);
	virtual ~Activity(void);

	virtual void		inflate(std::istream &stream);

	void				render(ACanvas &canvas);

	void				onKeyUp(int key_code);
	bool				onKeyDown(int key_code);

	void				onMouseMove(int x, int y);

	void				onMouseUp(int x, int y, int button);
	bool				onMouseDown(int x, int y, int button);

	template<typename... Args>
	void				registerEvent(std::string const &event, AView *v);
	template<class T, typename... Args>
	void				registerEvent(std::string const &event, AView *v
		, bool (T::*callback_)(Args...));
	void				unregisterEvent(std::string const &event, AView *v);

	template<typename... Args>
	bool				fireEvent(std::string const &event, Args... args) const;

	void				registerFun(std::string const &name
									, void (*f)(lua_State *));

protected:

	RootViewHolder		*_rootView;
	event_map_t			_eventMap;
	Vec2<int>			_size;
	
private:
	Activity(void);
	Activity(Activity const &src);
	Activity			&operator=(Activity const &rhs);
};

/*
** Activity::RootViewHolder
** -
** TODO comment
*/
class	Activity::RootViewHolder : public IViewHolder
{
public:
	RootViewHolder(XmlParser const &xml, AView *v, Vec2<int> s);
	virtual ~RootViewHolder(void);
		
	virtual ALayout			*getParent(void);
	virtual ALayout const	*getParent(void) const;

	virtual AView			*getView(void);
	virtual AView const		*getView(void) const;

	virtual Vec2<int>		getPos(void) const;
	virtual Vec2<int>		getSize(void) const;

	virtual void			setRequestedSize(Vec2<int> size);
	virtual Vec2<int>		getRequestedSize(void) const;

	virtual void			setParam(std::string const &k
									, std::string const &v);
protected:

	AView					*_view;
	Vec2<int>				_size;
	Vec2<int>				_requestedSize;

private:
	RootViewHolder(void) = delete;
	RootViewHolder(RootViewHolder const &src) = delete;
	RootViewHolder			&operator=(RootViewHolder const &rhs) = delete;
};

};

# include "ftui/templates/Activity.tpp"

#endif
