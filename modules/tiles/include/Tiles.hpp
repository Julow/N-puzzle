// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   Tiles.hpp                                          :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/10/11 11:52:03 by ngoguey           #+#    #+#             //
//   Updated: 2015/11/17 13:11:49 by ngoguey          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef TILES_HPP
# define TILES_HPP

# include <array>
# include <vector>

# include "ft/Vec.hpp"

class Tiles
{
public:

	Tiles();
	virtual ~Tiles();
	Tiles(Tiles &&src);

	Tiles(Tiles const &src) = delete;
	Tiles		&operator=(Tiles const &rhs) = delete;

	void		init(ft::Vec2<int> const rectSize
		  , ft::Vec2<int> const triangleSize = ft::Vec2<int>(95, 95)
		  , int const pointRandomRadius = 30
		  , float const percentGray = 0.33f
		  , ft::Vec3<int> const gray = ft::Vec3<int>(150, 150, 150)
		  , ft::Vec3<int> const pink = ft::Vec3<int>(140, 212, 202)
		  , ft::Vec3<int> const deltaPink = ft::Vec3<int>(10, 10, 52));
	void		render(void) const;

protected:
private:
	typedef ft::Vec2<float>						pos_t;
	typedef ft::Vec3<float>						col_t;
	typedef std::pair<pos_t, col_t>				point_t;

	typedef std::array<point_t, 3>				triangle_t;
	typedef std::vector<triangle_t>				mesh_t;

	typedef std::vector<point_t>				tmp_line_t;
	typedef std::vector<tmp_line_t>				tmp_grid_t;

	typedef std::array<float, 5>				point_vbo_t;
	typedef std::vector<point_vbo_t>			vbo_t;

	unsigned int								_p;
	unsigned int								_vao;
	vbo_t										_vbo;

	class Tmp
	{
	public:

		ft::Vec2<int> const		rectSize;
		ft::Vec2<int> const		triangleSize;
		int const				pointRandomRadius;
		int const				percentGray;
		ft::Vec3<float> const	gray;
		ft::Vec3<float> const	pink;
		ft::Vec3<float> const	deltaPink;

		ft::Vec2<int>			gridDim;
		tmp_grid_t				grid;
		mesh_t					mesh;

		Tmp(ft::Vec2<int> const rectSize
			, ft::Vec2<int> const triangleSize
			, int const pointRandomRadius
			, int const percentGray
			, ft::Vec3<float> const gray
			, ft::Vec3<float> const pink
			, ft::Vec3<float> const deltaPink);
		~Tmp();

		Tmp() = delete;
		Tmp(Tmp const &src) = delete;
		Tmp(Tmp &&src);
		Tmp						&operator=(Tmp const &rhs) = delete;

	private:
		void					_buildGridDim(void);
		void					_buildGrid(void);
		void					_buildMesh();

		ft::Vec2<float>			_pointDeltaPos(void);
		ft::Vec3<float>			_pointDeltaPink(void);

	};

	void						_initGlProgram();
	void						_initGlMesh(Tmp const &);
};

#endif // ********************************************************* TILES_HPP //
