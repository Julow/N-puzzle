// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   HorizontalLayout.hpp                               :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/11 11:47:52 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/11 12:05:49 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef HORIZONTALLAYOUT_HPP
# define HORIZONTALLAYOUT_HPP

# include <vector>

# include "ftui/ALayout.hpp"
# include "ftui/IViewHolder.hpp"

namespace ftui
{

/*
** HorizontalLayout
** -
** Childs:
** * Are ordered horizontally
** * Can be vertically aligned
** * Support marginTop and marginBottom
** * Requested height is always used
** * Requested width can be clamped to layout's width
** * Are not shrinked if height go outside layout's height
**    but are partially hidden
** -
*/
class	HorizontalLayout : public ALayout
{
public:
	class	ViewHolder;
	typedef std::vector<ViewHolder*>	child_container_t;

	enum class	Align
	{
		TOP,
		MIDDLE,
		BOTTOM
	};

	virtual ~HorizontalLayout(void);

	virtual void			inflate(XmlParser &xml, Activity &a);

	virtual void			onUpdate(void);
	virtual void			onMeasure(void);
	virtual void			onDraw(Canvas &canvas);

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

	HorizontalLayout(XmlParser const &xml, Activity &act);

	virtual IViewHolder		*holderAt(int i);

	virtual void			alignChilds(void);

private:
	HorizontalLayout(void) = delete;
	HorizontalLayout(HorizontalLayout const &src) = delete;
	HorizontalLayout			&operator=(HorizontalLayout const &rhs) = delete;

/*
** Static
*/
public:

	static AView			*createView(XmlParser const &xml, Activity &act);
};

/*
** HorizontalLayout::ViewHolder
** -
*/
class	HorizontalLayout::ViewHolder : public IViewHolder
{
public:
	virtual ~ViewHolder(void);
	ViewHolder(HorizontalLayout *p, AView *v);

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

	ft::Vec2<int>			getHorizontalMargin(void) const;
	void					setHorizontalMargin(ft::Vec2<int> margin);
	ft::Vec2<int>			getVerticalMargin(void) const;
	void					setVerticalMargin(ft::Vec2<int> margin);
	Align					getVerticalAlign(void) const;
	void					setVerticalAlign(Align align);

protected:

	AView					*_view;
	HorizontalLayout		*_parent;

	ft::Vec2<int>			_pos;
	ft::Vec2<int>			_size;
	ft::Vec2<int>			_requestedSize;

	ft::Vec2<int>			_horizontalMargin;
	ft::Vec2<int>			_verticalMargin;
	Align					_verticalAlign;

private:
	ViewHolder(void) = delete;
	ViewHolder(ViewHolder const &src) = delete;
	ViewHolder				&operator=(ViewHolder const &rhs) = delete;
};

};

#endif
