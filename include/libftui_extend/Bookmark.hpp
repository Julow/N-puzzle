// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Bookmark.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/15 09:14:49 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/15 16:52:57 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef BOOKMARK_HPP
# define BOOKMARK_HPP

// # include <iostream>
// # include <>

# include "ftui/Activity.hpp"
# include "ftui/AView.hpp"

class Bookmark : public ftui::AView
{
public:

	/* CONSTRUCTION ***************** */
	static void				declare_libftui(void);
	static ftui::AView		*createView(ftui::XmlParser const &xml
										, ftui::Activity &act);

	Bookmark(ftui::XmlParser const &xml, ftui::Activity &act);
	~Bookmark();

	Bookmark() = delete;
	Bookmark(Bookmark const &src) = delete;
	Bookmark(Bookmark &&src) = delete;
	Bookmark				&operator=(Bookmark const &rhs) = delete;
	Bookmark				&operator=(Bookmark &&rhs) = delete;

	/* DRAW ************************* */
	void					onMeasure(void);
	void					onDraw(ftui::Canvas &can);

protected:
private:
	std::string				_text;
};
//std::ostream			&operator<<(std::ostream &o, Bookmark const &rhs);

#endif /* ****************************************************** BOOKMARK_HPP */
