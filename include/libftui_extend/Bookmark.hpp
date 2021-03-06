// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bookmark.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/15 09:14:49 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/07 15:53:04 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef BOOKMARK_HPP
# define BOOKMARK_HPP

# include "ftui/Activity.hpp"
# include "ftui/ALayout.hpp"

/* BOOKMARK ************************* */
class Bookmark : public ftui::ALayout
{
public:

	/* CONSTRUCTION ***************** */
	static void				declare_libftui(void);
	static ftui::AView		*createView(ftui::Activity &act);

	Bookmark(ftui::Activity &act, std::string const &viewName = "Bookmark");
	virtual ~Bookmark();

	Bookmark() = delete;
	Bookmark(Bookmark const &src) = delete;
	Bookmark(Bookmark &&src) = delete;
	Bookmark				&operator=(Bookmark const &rhs) = delete;
	Bookmark				&operator=(Bookmark &&rhs) = delete;

	/* DRAW ************************* */
	void					onUpdate(void);
	void					onMeasure(void);
	void					onDraw(ftui::ACanvas &can);

	/* ALAYOUT LEGACY *************** */
	void					addView(AView *v);
	AView					*popView(AView *v);

	AView					*at(int i);
	AView const				*at(int i) const;
	ftui::IViewHolder		*holderAt(int i);

	int						size(void) const;

	bool					onMouseDown(int x, int y, int button, int mods);
	bool					onMouseUp(int x, int y, int button, int mods);

	/* FUNCTIONALITIES ************** */
	static int				setTextG(lua_State *l);
	void					setText(std::string const &str);

	bool					onBordel(int i, std::string const &str);

	/* HOLDER *********************** */
	class ViewHolder;

private:
	std::string				_text;
	ViewHolder				*_selHolder;
	ViewHolder				*_delHolder;

	void					_genSlaveButton(void);

};

/* HOLDER *************************** */
class Bookmark::ViewHolder : public ftui::IViewHolder
{
public:

	/* CONSTRUCTION ***************** */
	ViewHolder(Bookmark *p, AView *v);
	~ViewHolder();

	ViewHolder() = delete;
	ViewHolder(ViewHolder const &src) = delete;
	ViewHolder(ViewHolder &&src) = delete;
	ViewHolder				&operator=(ViewHolder const &rhs) = delete;
	ViewHolder				&operator=(ViewHolder &&rhs) = delete;


	/* IVIEWHOLDER LEGACY *********** */
	AView					*getView(void);
	AView const				*getView(void) const;

	ALayout					*getParent(void);
	ALayout const			*getParent(void) const;

	ft::Vec2<int>			getPos(void) const;
	ft::Vec2<int>			getSize(void) const;

	ft::Vec2<int>			getRequestedSize(void) const;
	void					setRequestedSize(ft::Vec2<int> size);

	void					setParam(std::string const &k,
									std::string const &v);

	void					setSize(ft::Vec2<int> sz);
	void					setPos(ft::Vec2<int> pos);

private:
	AView				*_view;
	Bookmark			*_parent;
	ft::Vec2<int>		_size;
	ft::Vec2<int>		_pos;

};

#endif /* ****************************************************** BOOKMARK_HPP */
