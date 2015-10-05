/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VerticalLayout.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/09/22 13:12:43 by jaguillo          #+#    #+#             */
/*   Updated: 2015/10/05 14:30:12 by jaguillo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VERTICALLAYOUT_HPP
# define VERTICALLAYOUT_HPP

# include <vector>

# include "ftui/ALayout.hpp"
# include "ftui/IViewHolder.hpp"

namespace ftui
{

/*
** VerticalLayout
** -
** Childs:
** * Are ordered vertically
** * Can be horizontally aligned
** * Support marginTop and marginBottom
** * Requested height is always used
** * Requested width can be clamp to layout's width
** * Are not shrink if height go outside layout's height
**    but are partially hidden
*/
class	VerticalLayout : public ALayout
{
protected:
	class	ViewHolder;
	typedef std::vector<ViewHolder*>	child_container_t;
	
public:
	enum class	Align
	{
		LEFT,
		CENTER,
		RIGHT
	};

	virtual ~VerticalLayout(void);

	virtual void			inflate(XmlParser &xml, Activity &a);

	virtual void			onUpdate(void);
	virtual void			onMeasure(void);
	virtual void			onDraw(ACanvas &canvas);

	virtual void			onSizeChange(void);

/*
** Childs
*/
	virtual void			addView(AView *v);
	virtual AView			*popView(AView *v);

	virtual AView			*at(int i);
	virtual AView const		*at(int i) const;

	virtual int				size(void) const;

protected:

	std::vector<ViewHolder*>	_childs;

	VerticalLayout(XmlParser const &xml, Activity &act);

	virtual IViewHolder		*holderAt(int i);

private:
	VerticalLayout(void) = delete;
	VerticalLayout(VerticalLayout const &src) = delete;
	VerticalLayout			&operator=(VerticalLayout const &rhs) = delete;

/*
** Static
*/
public:

	static AView			*createView(XmlParser const &xml, Activity &act);
};

/*
** VerticalLayout::ViewHolder
** -
*/
class	VerticalLayout::ViewHolder : public IViewHolder
{
public:
	virtual ~ViewHolder(void);
	ViewHolder(VerticalLayout *p, AView *v);

/*
** Impl
*/
	virtual AView			*getView(void);
	virtual AView const		*getView(void) const;

	virtual ALayout			*getParent(void);
	virtual ALayout const	*getParent(void) const;

	virtual ft::Vec2<int>	getPos(void) const;
	virtual ft::Vec2<int>	getSize(void) const;

	virtual ft::Vec2<int>	getRequestedSize(void) const;
	virtual void			setRequestedSize(ft::Vec2<int> size);

	virtual void			setParam(std::string const &k,
								std::string const &v);

/*
** -
*/
	void					setPosX(int x);
	void					setPosY(int y);

	/*
	** Automatically call onSizeChange if size is different than actual
	*/
	void					setSize(ft::Vec2<int> size);

	ft::Vec2<int>			getVerticalMargin(void) const;
	Align					getHorizontalAlign(void) const;

protected:

	AView					*_view;
	VerticalLayout			*_parent;

	ft::Vec2<int>			_pos;
	ft::Vec2<int>			_size;
	ft::Vec2<int>			_requestedSize;

	ft::Vec2<int>			_verticalMargin;
	Align					_horizontalAlign;

private:
	ViewHolder(void) = delete;
	ViewHolder(ViewHolder const &src) = delete;
	ViewHolder				&operator=(ViewHolder const &rhs) = delete;
};

};

#endif
