/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VerticalLayout.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:43 by jaguillo          #+#    #+#             */
/*   Updated: 2015/09/26 14:38:13 by juloo            ###   ########.fr       */
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

	virtual void			onUpdate(void);
	virtual void			onMeasure(void);
	virtual void			onDraw(ACanvas &canvas);

	AView					*createChild(std::string const &type, ...);

protected:

	VerticalLayout(XmlParser const &xml);

	virtual IViewHolder			*createHolder(XmlParser const &xml,
									ALayout *p, AView *v);
	virtual IViewHolder			*createHolder(ALayout *p, AView *v);

private:
	VerticalLayout(void) = delete;
	VerticalLayout(VerticalLayout const &src) = delete;
	VerticalLayout			&operator=(VerticalLayout const &rhs) = delete;

/*
** Static
*/
public:

	static AView			*createView(XmlParser const &xml);
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
	ViewHolder(ALayout *p, AView *v);

	virtual AView			*getView(void);
	virtual AView const		*getView(void) const;

	virtual ALayout			*getParent(void);
	virtual ALayout const	*getParent(void) const;

	virtual Vec2<int>		getPos(void) const;
	virtual Vec2<int>		getSize(void) const;

	virtual void			setParam(std::string const &k,
								std::string const &v);

protected:

	AView					*_view;
	ALayout					*_parent;

private:
	ViewHolder(void) = delete;
	ViewHolder(ViewHolder const &src) = delete;
	ViewHolder				&operator=(ViewHolder const &rhs) = delete;
};

};

#endif
