// ************************************************************************** //
//                                                                            //
//                                                        :::      ::::::::   //
//   GridParser.hpp                                     :+:      :+:    :+:   //
//                                                    +:+ +:+         +:+     //
//   By: jaguillo <jaguillo@student.42.fr>          +#+  +:+       +#+        //
//                                                +#+#+#+#+#+   +#+           //
//   Created: 2015/11/18 17:13:52 by jaguillo          #+#    #+#             //
//   Updated: 2015/11/18 18:02:30 by jaguillo         ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

#ifndef GRIDPARSER_HPP
# define GRIDPARSER_HPP

# include "Tokenizer.hpp"
# include <fstream>

class	GridParser
{
public:
	enum class Token
	{
		NUMBER,
		ENDL,
		END_OF_FILE
	};

	GridParser(std::string const &fileName);
	virtual ~GridParser(void);

	Token			next(void);

	std::string		getStrToken(void) const;
	int				getIntToken(void) const;

	int				getLine(void) const;

	void			error(std::string const &err) const;

protected:
	std::string const	&_fileName;
	std::ifstream		_in;
	Tokenizer			_tokenizer;

	int					_line;

	static Tokenizer::token_def_s const	gridTokens[];

	enum BaseToken
	{
		TOKEN_COMMENT,
		TOKEN_ENDL,
		TOKEN_SPACE,
		TOKEN_NUMBER
	};

private:
	GridParser(GridParser const &src);
	GridParser		&operator=(GridParser const &rhs);
};

#endif
