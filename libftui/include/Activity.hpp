/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Activity.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:16:33 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/25 09:08:21 by ngoguey          ###   ########.fr       //
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

class	Activity
{
public:
	class	RootViewHolder : public IViewHolder
	{
	public:
		virtual ~RootViewHolder(void);
		RootViewHolder(XmlParser const &xml, ALayout *p, AView *v);
		
		virtual ALayout			*getParent(void);
		virtual ALayout const	*getParent(void) const;

		virtual AView			*getView(void);
		virtual AView const		*getView(void) const;

		virtual Vec2<int>		getPos(void) const;
		virtual Vec2<int>		getSize(void) const;
	protected:

		AView					*_view;

	private:
		RootViewHolder(void) = delete;
		RootViewHolder(RootViewHolder const &src) = delete;
		RootViewHolder			&operator=(RootViewHolder const &rhs) = delete;
	};

	typedef std::unordered_multimap<std::string, AView*>	event_map_t;

	Activity(void);
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

private:
	Activity(Activity const &src);
	Activity			&operator=(Activity const &rhs);
};

};

#endif
