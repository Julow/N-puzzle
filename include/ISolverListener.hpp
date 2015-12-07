// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   ISolverListener.hpp                                :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 15:39:19 by jaguillo          #+#    #+#             //
//   Updated: 2015/12/07 15:36:26 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef ISOLVERLISTENER_HPP
# define ISOLVERLISTENER_HPP

# include "ft/Vec.hpp"
# include <vector>
# include <string>
# include "Grid.hpp"

class	ISolverListener
{
public:
    struct report_s
	{
		float				time;

		int                 g;
		int                 init_h;
		float               avg_h;

		int                 nodes;
		int                 max_open;
		int                 max_closed;
		ft::Vec2<int>       max_both;

		std::vector<Grid>   steps;
	};
	struct progress_s
	{
		std::string         str;
		float               val;
	};

	virtual ~ISolverListener(void) {}

	virtual void	onSuccess(report_s rep) = 0;
	virtual void	onProgress(progress_s prog) = 0;
	virtual void	onFail(std::string const &str) = 0;

protected:

private:
};

inline std::ostream	&operator<<(std::ostream &o,
							ISolverListener::report_s const &rep)
{
	return o << ft::f("time(%) g/init/avg(% % %) "
					  "nodes/maxo/maxc/both(% % % %)",
					  rep.time, rep.g, rep.init_h, rep.avg_h,
					  rep.nodes, rep.max_open, rep.max_closed,
					  rep.max_both.x + rep.max_both.y);
}


#endif
