/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvan-pae <bryan.vanpaemel@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:28:44 by bvan-pae          #+#    #+#             */
/*   Updated: 2024/04/25 08:51:59 by bvan-pae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <cstring>
#include <ios>

bool Data::operator>(const Data &other) const {

	int tYear;
	int tMonth;
	int tDay;
	int oYear;
	int oMonth;
	int oDay;
	std::stringstream tYearss(this->date.substr(0, 4));
	std::stringstream tMonthss(this->date.substr(5, 2));
	std::stringstream tDayss(this->date.substr(8, 2));
	std::stringstream oYearss(other.date.substr(0, 4));
	std::stringstream oMonthss(other.date.substr(5, 2));
	std::stringstream oDayss(other.date.substr(8, 2));
	tYearss >> tYear;
	tMonthss >> tMonth;
	tDayss >> tDay;
	oYearss >> oYear;
	oMonthss >> oMonth;
	oDayss >> oDay;
	if (tYear < oYear)
		return false;
	else if (tYear > oYear)
		return true;
	else if (tMonth < oMonth)
		return false;
	else if (tMonth > oMonth)
		return true;
	else if (tDay < oDay)
		return false;
	else if (tDay > oDay)
		return true;
	return false;
}

bool Data::operator<(const Data &other) const {

	int tYear;
	int tMonth;
	int tDay;
	int oYear;
	int oMonth;
	int oDay;
	std::stringstream tYearss(this->date.substr(0, 4));
	std::stringstream tMonthss(this->date.substr(5, 2));
	std::stringstream tDayss(this->date.substr(8, 2));
	std::stringstream oYearss(other.date.substr(0, 4));
	std::stringstream oMonthss(other.date.substr(5, 2));
	std::stringstream oDayss(other.date.substr(8, 2));
	tYearss >> tYear;
	tMonthss >> tMonth;
	tDayss >> tDay;
	oYearss >> oYear;
	oMonthss >> oMonth;
	oDayss >> oDay;
	if (tYear < oYear)
		return true;
	else if (tYear > oYear)
		return false;
	else if (tMonth < oMonth)
		return true;
	else if (tMonth > oMonth)
		return false;
	else if (tDay < oDay)
		return true;
	else if (tDay > oDay)
		return false;
	return false;
}

bool Data::operator==(const Data &other) const {
	if (this->date == other.date)
		return true;
	return false;
}

BitcoinExchange::BitcoinExchange(): _dataBase(nullptr) {
	return ;
}

BitcoinExchange::~BitcoinExchange() {
	return ;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) {
	this->_dataBase = other._dataBase;
	return ;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other) {
	if (this != &other)
	{
		this->_dataBase = other._dataBase;
	}
	return *this;
}

bool BitcoinExchange::_checkDateFormat(std::string date)
{
	if (date.size() != 10)
		return false;
	for (size_t i = 0; i <= 3; i++)
		if (!std::isdigit(date[i]))
			return false;
	if (date[4] != '-')
		return false;
	for (size_t i = 5; i <= 6; i++)
		if (!std::isdigit(date[i]))
			return false;
	if (date[7] != '-')
		return false;
	for (size_t i = 8; i <= 9; i++)
		if (!std::isdigit(date[i]))
			return false;
	return true;	
}

bool BitcoinExchange::_checkValidDate(std::string date)
{
    int month;
	int day;
	std::stringstream ss1(date.substr(5, 2));
	std::stringstream ss2(date.substr(8, 2));

	ss1 >> month;
	ss2 >> day;
	if (month > 12 || month < 0 || day > 31 || day < 0)
		return false;
	return true;	
}

bool BitcoinExchange::_isValid(std::string str)
{
	size_t i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	for (; i < str.size(); i++)
	{
		if (!std::isdigit(str[i]))
			break;
	}
	if (str[i] == '.')
		i++;
	for (; i < str.size(); i++)
		if (!std::isdigit(str[i]))
			break;
	if (i == str.size() || (str[i] == 'f' && i + 1 == str.size()))
		return true;
	return false;
}

bool BitcoinExchange::_isWhiteSpace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

std::string BitcoinExchange::_strTrim(std::string date)
{
	size_t s = 0;
	size_t e = 0;
	size_t i = 0;

	for (size_t i = 0; date[i] && this->_isWhiteSpace(date[i]); i++, s++) ;
	e = date.size();
	for (i = date.size() - 1; date[i] && this->_isWhiteSpace(date[i]); i--, e--) ;
	return date.substr(s, e - s);
}

Data* BitcoinExchange::_getData(std::string line, char base)
{
    Data* raw_data = new Data;
	char* p;

    std::size_t match = line.find(base);
    if (match == std::string::npos)
    {
        delete raw_data;
        throw InvalidDate();
    }

    raw_data->date = line.substr(0, match);
    raw_data->date = this->_strTrim(raw_data->date);
	
	std::string str_value = line.substr(match + 1, line.size() - match);
	str_value = this->_strTrim(str_value);
	if (!this->_isValid(str_value))
	{
		delete raw_data;
		throw NotANumber();
	}

    raw_data->value = std::strtod(str_value.c_str(), &p);
	if (raw_data->value < 0 || (base == INPUTBASE && raw_data->value > 1000))
    {
		delete raw_data;
		throw OutOfRange();
    }
    if (!this->_checkDateFormat(raw_data->date) || !this->_checkValidDate(raw_data->date))
    {
        delete raw_data;
        throw InvalidDate();
    }
    return raw_data;
}

void BitcoinExchange::_printValue(Data *raw_data)
{
	std::vector<Data>::iterator it;
	for (it = this->_dataBase.begin(); it < this->_dataBase.end();)
	{
		if (*it < *raw_data)
			it++;
		if (!it->date.size() || *it > *raw_data || *it == *raw_data)
		{
			if ((!it->date.size() || *it > *raw_data) && it != this->_dataBase.begin())
				it--;
			std::cout << raw_data->date << " => " << raw_data->value << " = " << (raw_data->value * it->value) << std::endl;
			break;
		}
	}
}

void BitcoinExchange::_fillBase(int base, std::ifstream &file, char *path)
{
	Data				*raw_data;
	std::string			line;
	std::vector<Data>	*ptr;

	if (base == DATABASE)
		ptr = &this->_dataBase;

	std::getline(file, line);
	int i = 2;
	bool error = false;
	while (true)
    {
		std::getline(file, line);
		if (file.eof())
			break ;
		try {
			raw_data = this->_getData(line, base);
			if (base == DATABASE)
				ptr->push_back(*raw_data);
			if (base == INPUTBASE)
				this->_printValue(raw_data);
			delete raw_data;
		} catch (std::exception &e) {
			error = 1;
			std::cerr << e.what() << " {line : " << i << "}"<< " File : " << path << std::endl;
		}
		i++;
    }
	if (error == true && base == DATABASE)
		throw DataBaseError();
	if (error == true && base == INPUTBASE)
		throw InputBaseError();
}

void BitcoinExchange::loadDataBases(char *data_path, char *input_path) {

    std::ifstream dataBase(data_path);
    if (!dataBase)
		throw ErrorOpeningFile();
	this->_fillBase(DATABASE, dataBase, data_path);
    std::ifstream inputBase(input_path);
    if (!inputBase)
		throw ErrorOpeningFile();
	this->_fillBase(INPUTBASE, inputBase, input_path);
}
