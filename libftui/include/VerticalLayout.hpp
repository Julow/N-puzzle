/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VerticalLayout.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:43 by jaguillo          #+#    #+#             */
//   Updated: 2015/09/25 10:16:35 by ngoguey          ###   ########.fr       //
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTICALLAYOUT_HPP
# define VERTICALLAYOUT_HPP

# include <vector>

# include "ALayout.hpp"
# include "IViewHolder.hpp"

namespace ftui
{

/*
** VerticalLayout
** -
** TODO comment
*/
class	VerticalLayout : public ALayout
{
	class	ViewHolder;
public:
	virtual ~VerticalLayout(void);

	virtual void			inflate(XmlParser &xml);

	AView					*createChild(std::string const &type, ...);

	static AView			*createView(XmlParser &xml);

protected:

	VerticalLayout(XmlParser const &xml);

private:
	VerticalLayout(void) = delete;
	VerticalLayout(VerticalLayout const &src) = delete;
	VerticalLayout			&operator=(VerticalLayout const &rhs) = delete;

public:
};

/*
** VerticalLayout::ViewHolder
** -
** TODO comment
*/
class	VerticalLayout::ViewHolder : public IViewHolder
{
public:
	virtual ~ViewHolder(void);
	ViewHolder(XmlParser const &xml, ALayout *p, AView *v);
		
	virtual AView			*getView(void);
	virtual AView const		*getView(void) const;

	virtual ALayout			*getParent(void);
	virtual ALayout const	*getParent(void) const;

	virtual Vec2<int>		getPos(void) const;
	virtual Vec2<int>		getSize(void) const;

protected:

	AView				*_view;
	ALayout				*_parent;

private:
	ViewHolder(void) = delete;
	ViewHolder(ViewHolder const &src) = delete;
	ViewHolder			&operator=(ViewHolder const &rhs) = delete;
};

};

#endif
