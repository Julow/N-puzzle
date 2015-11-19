// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   config_window.hpp                                  :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/11 11:03:51 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/19 12:34:54 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef CONFIG_WINDOW_HPP
# define CONFIG_WINDOW_HPP

# include <type_traits>

# include "ft/Vec.hpp"
# include "ftce/math.hpp"

/*
** LITERAL
*/
typedef std::integral_constant<int, 1200>	win_width_t;
# define WIN_RATIOF (4.f / 3.f)

/*
** CALCULATED
*/
# define WIN_WIDTHI win_width_t()
# define WIN_WIDTHF static_cast<float>(WIN_WIDTHI)
typedef std::integral_constant<int, ftce::round_toi(WIN_WIDTHF / WIN_RATIOF)>
	win_height_t;
# define WIN_HEIGHTI win_height_t()
# define WIN_HEIGHTF static_cast<float>(WIN_HEIGHTI)
# define WIN_SIZEVI ft::Vec2<int>(WIN_WIDTHI, WIN_HEIGHTI)
# define WIN_SIZEVF ft::Vec2<float>(WIN_WIDTHF, WIN_HEIGHTF)

#endif // ************************************************* CONFIG_WINDOW_HPP //
