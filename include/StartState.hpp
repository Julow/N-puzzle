// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   StartState.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/07 09:02:42 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/07 09:34:44 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef STARTSTATE_HPP
# define STARTSTATE_HPP

//# include <string>
# include <iostream>
//# include <stdexcept>
# include "IState.hpp"
# include "tiles/Tiles.hpp"
# include "ftui/Activity.hpp"

class StartState final : public IState
{
public:
	StartState();
	StartState(StartState const &src) = delete;
	StartState					&operator=(StartState const &rhs) = delete;
	virtual ~StartState();

	void						loop(
		std::unique_ptr<IState> &ptr, ftui::Canvas &can) override;

	static IState				*create(void);
	static void					globalInit(void);

private:

	void						_render(ftui::Canvas &can);

	static ftui::Activity		act;
	static Tiles				tiles;

};
//std::ostream					&operator<<(std::ostream &o, StartState const &rhs);

#endif // **************************************************** STARTSTATE_HPP //
