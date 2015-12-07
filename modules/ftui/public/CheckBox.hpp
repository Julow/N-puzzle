// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   CheckBox.hpp                                       :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/28 12:40:54 by ngoguey           #+#    #+#             //
//   Updated: 2015/12/07 15:46:41 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CHECKBOX_HPP
# define CHECKBOX_HPP

# include "ftui/Button.hpp"
# include "ftui/ACanvas.hpp"

namespace ftui
{

class CheckBox : public Button
{
public:

	// CONSTRUCTION ***************** //
	static AView		*createView(ftui::Activity &act);

	CheckBox(Activity &act, std::string const &viewName = "CheckBox");
	virtual ~CheckBox();

	CheckBox() = delete;
	CheckBox(CheckBox const &src) = delete;
	CheckBox				&operator=(CheckBox const &rhs) = delete;

	virtual void		setParam(std::string const &k, std::string const &v);

	// DRAW ************************* //
	virtual void		onDraw(ACanvas &canvas);

	virtual void		onClick(int mods);

	static int			isCheckedG(lua_State *l);
	bool				isChecked(void) const;

	static int			setCheckedG(lua_State *l);
	void				setChecked(bool b);


	ACanvas::Params const	&getCheckedParams(void) const;
	void					setCheckedParams(ACanvas::Params const &p);
	static int				setCheckedParamsG(lua_State *l);

	ACanvas::Params const	&getDisabledCheckedParams(void) const;
	void					setDisabledCheckedParams(ACanvas::Params const &p);
	static int				setDisabledCheckedParamsG(lua_State *l);

protected:
	bool				_isChecked;
	ACanvas::Params		_checked;
	ACanvas::Params		_disabledChecked;

};
};

#endif // ********************************************************** CHECKBOX //
