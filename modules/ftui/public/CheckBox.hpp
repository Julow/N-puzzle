// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   CheckBox.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/28 12:40:54 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/28 13:10:19 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CHECKBOX_HPP
# define CHECKBOX_HPP

# include "ftui/Button.hpp"
# include "ftui/ACanvas.hpp"

# include <iostream>
# include <chrono>

namespace ftui
{

class CheckBox : public Button
{
public:

	enum class	LuaCallback : uint32_t
	{
		CHECK = static_cast<uint32_t>(Button::LuaCallback::__LAST),
		__LAST
	};

	// CONSTRUCTION ***************** //
	static AView		*createView(
		ftui::Activity &act, ft::XmlParser const *xml, std::string const *id);

	CheckBox(Activity &act, ft::XmlParser const &xml);
	CheckBox(Activity &act, std::string const *id
			, std::string const &viewName = "CheckBox");
	virtual ~CheckBox();

	CheckBox() = delete;
	CheckBox(CheckBox const &src) = delete;
	CheckBox				&operator=(CheckBox const &rhs) = delete;

	// virtual void setParam(std::string const &k, std::string const &v); //TODO: this

	// DRAW ************************* //
	virtual void		onDraw(ACanvas &canvas);

	virtual void		onClick(int mods);
	virtual void		onCheckStateChange(bool state);

	bool				isChecked(void);

	ACanvas::Params const	&getCheckedParams(void) const;
	void					setCheckedParams(ACanvas::Params const &p);

	ACanvas::Params const	&getDisabledCheckedParams(void) const;
	void					setDisabledCheckedParams(ACanvas::Params const &p);

protected:
	bool				_isChecked;
	ACanvas::Params		_checked;
	ACanvas::Params		_disabledChecked;

};
};

#endif // ********************************************************** CHECKBOX //
