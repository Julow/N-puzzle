// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bookmark.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/15 09:14:49 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/16 14:46:51 by ngoguey          ###   ########.fr       //
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
	static ftui::AView		*createView(ft::XmlParser const &xml
										, ftui::Activity &act);
	void					setViewHolder(ftui::IViewHolder *holder);

	Bookmark(ft::XmlParser const &xml, ftui::Activity &act);
	~Bookmark();

	Bookmark() = delete;
	Bookmark(Bookmark const &src) = delete;
	Bookmark(Bookmark &&src) = delete;
	Bookmark				&operator=(Bookmark const &rhs) = delete;
	Bookmark				&operator=(Bookmark &&rhs) = delete;

	/* DRAW ************************* */
	void					onUpdate(void);
	void					onMeasure(void);
	void					onDraw(ftui::Canvas &can);

	/* ALAYOUT LEGACY *************** */
	void					addView(AView *v);
	AView					*popView(AView *v);

	AView					*at(int i);
	AView const				*at(int i) const;
	ftui::IViewHolder		*holderAt(int i);

	int						size(void) const;

	/* HOLDER *********************** */
	class ViewHolder;

private:
	std::string				_text;
	ViewHolder				*_buttonHolder;

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

private:
	AView				*_view;
	Bookmark			*_parent;

};

#endif /* ****************************************************** BOOKMARK_HPP */
