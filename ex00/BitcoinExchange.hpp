/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:17:28 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/25 08:29:47 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_H
# define BITCOINEXCHANGE_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <string>
#include <sstream>
# define nullptr 0

enum {
	DATABASE = 44,
	INPUTBASE = 124,
};

struct Data {
	std::string date;
	float		value;

	bool operator>(const Data & other) const;
	bool operator<(const Data & other) const;
	bool operator==(const Data & other) const;
};


class BitcoinExchange {
	public:	
		BitcoinExchange();
		~BitcoinExchange();
		BitcoinExchange(const BitcoinExchange &other);
		BitcoinExchange &operator=(const BitcoinExchange &other);

		void	loadDataBases(char *data_path, char *input_path);

	private:
		std::vector<Data>	_dataBase;
		bool				_checkFile(std::ifstream& inputFile);
		void				_fillBase(int base, std::ifstream &file, char *path);
		Data				*_getData(std::string line, char base);
		void				_printValue(Data *raw_data);
		bool				_checkDateFormat(std::string date);
		bool				_checkValidDate(std::string date);
		bool				_isValid(std::string str);
		bool				_isWhiteSpace(char c);
		std::string			_strTrim(std::string date);


	class ErrorOpeningFile : public std::exception {
	public:
		const char* what() const throw() {
			return "Error: couldn't open file";
		}
	};

	class InvalidDate : public std::exception {
	public:
		const char* what() const throw() {
			return "Error: invalid date";
		}
	};

	class InvalidValue : public std::exception {
	public:
		const char* what() const throw() {
			return "Error: invalid value";
		}
	};

	class DataBaseError : public std::exception {
	public:
		const char* what() const throw() {
			return "Data base error";
		}
	};

	class InputBaseError : public std::exception {
	public:
		const char* what() const throw() {
			return "Input base error";
		}
	};

	class NotANumber : public std::exception {
	public:
		const char* what() const throw() {
			return "Error: not a number";
		}
	};

	class OutOfRange : public std::exception {
	public:
		const char* what() const throw() {
			return "Error: out of range";
		}
	};

};

#endif
