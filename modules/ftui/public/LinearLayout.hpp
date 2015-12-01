// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   LinearLayout.hpp                                   :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/25 13:24:07 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/01 19:22:13 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef LINEARLAYOUT_HPP
# define LINEARLAYOUT_HPP

# include "ftui/Activity.hpp"
# include "ftui/ALayout.hpp"
# include "ftui/IViewHolder.hpp"

namespace ftui
{

/*
** ========================================================================== **
** LinearLayout
** -
** Params:
** 	direction		(enum)	VERTICAL or HORIZONTAL
** -
** Childs params:
** 	align			(enum)	LEFT, TOP, RIGHT, BOTTOM or CENTER
** 								LEFT and RIGHT for VERTICAL layouts
** 								TOP and BOTTOM for HORIZONTAL layouts
** 	width			(uint)	Requested width
** 	height			(uint)	Requested height
** 	marginLeft		(int)	Extra margin at the left of the view
** 	marginTop		(int)
** 	marginRight		(int)
** 	marginBottom	(int)
** -
*/
class	LinearLayout : public ALayout
{
public:

	class	ViewHolder;

	enum class	Align : int
	{
		LEFT = 0,
		TOP = LEFT,
		RIGHT = 1,
		BOTTOM = RIGHT,
		CENTER = 2
	};

	enum class	Direction : int
	{
		VERTICAL = 0,
		HORIZONTAL = 1
	};

	/*
	** Constructs
	*/
	static AView			*createView(Activity &act);

	LinearLayout(Activity &act, std::string const &viewName = "LinearLayout");

	virtual ~LinearLayout(void);

	/*
	** Callbacks
	*/
	virtual void			onUpdate(void);
	virtual void			onMeasure(void);
	virtual void			onDraw(ACanvas &canvas);

	virtual void			onSizeChange(ft::Vec2<int> size);

	/*
	** Childs
	*/
	virtual void			addView(AView *v);
	virtual AView			*popView(AView *v);

	virtual AView			*at(int i);
	virtual AView const		*at(int i) const;

	virtual int				size(void) const;

	virtual IViewHolder		*holderAt(int i);

	/*
	** -
	*/
	Direction				getDirection(void) const;
	void					setDirection(Direction o);

	virtual void			setParam(std::string const &k,
								std::string const &v);

	/*
	** Lua
	*/
	static int				getDirectionG(lua_State *l);
	static int				setDirectionG(lua_State *l);

protected:

	typedef std::vector<ViewHolder*>	child_container_t;

	child_container_t		_childs;

	Direction				_direction;

	ft::Vec2<int>			_fullSize;

	virtual void			alignChilds(void);
	virtual ft::Rect<int>	getRedrawClip(void) const;

private:
	LinearLayout(void) = delete;
	LinearLayout(LinearLayout const &src) = delete;
	LinearLayout			&operator=(LinearLayout const &rhs) = delete;
};

/*
** LinearLayout::ViewHolder
** -
*/
class	LinearLayout::ViewHolder : public IViewHolder
{
public:
	enum	Flags
	{
		FIXED_WIDTH = 1 << 1,
		FIXED_HEIGHT = 1 << 2
	};

	ViewHolder(LinearLayout *p, AView *v);

	virtual ~ViewHolder(void);

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
	void					setPos(ft::Vec2<int> pos);

	/*
	** Automatically call onSizeChange if size is different than actual
	*/
	void					setSize(ft::Vec2<int> size);

	ft::Rect<int> const		&getMargin(void) const;
	void					setMargin(ft::Rect<int> const &margin);

	Align					getAlign(void) const;
	void					setAlign(LinearLayout::Align align);

	uint32_t				getFlags(void) const;

protected:

	AView					*_view;
	LinearLayout			*_parent;

	ft::Vec2<int>			_pos;
	ft::Vec2<int>			_size;
	ft::Vec2<int>			_requestedSize;

	ft::Rect<int>			_margin;
	LinearLayout::Align		_align;

	uint32_t				_flags;

private:
	ViewHolder(void) = delete;
	ViewHolder(ViewHolder const &src) = delete;
	ViewHolder				&operator=(ViewHolder const &rhs) = delete;
};

};

#endif
