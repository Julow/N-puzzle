/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:16:33 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/25 15:26:33 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIVITY_HPP
# define ACTIVITY_HPP

# include "libftui.h"

# include <vector>
# include <unordered_map>
# include <string>
# include <istream>

# include "IViewHolder.hpp"

namespace ftui
{

/*
** Activity
** -
** TODO comment
*/
class	Activity
{
public:
	class	RootViewHolder;

	typedef std::unordered_multimap<std::string, AView*>	event_map_t;

	Activity(Vec2<int> size);
	virtual ~Activity(void);

	virtual void		inflate(std::istream &stream);
	// void				loadScripts(std::vector<std::istream> &scripts);

	bool				onDraw(ACanvas &canvas);

	void				onKeyUp(int key_code);
	bool				onKeyDown(int key_code);

	void				onMouseMove(int x, int y);

	void				onMouseUp(void);
	bool				onMouseDown(int x, int y);

	bool				fireEvent(std::string const &event);

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

	virtual void			 setParam(std::string const &k
									  , std::string const &v);
protected:
	AView					*_view;
	Vec2<int>				_size;
		
private:
	RootViewHolder(void) = delete;
	RootViewHolder(RootViewHolder const &src) = delete;
	RootViewHolder			&operator=(RootViewHolder const &rhs) = delete;
};

};

#endif
