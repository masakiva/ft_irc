/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 21:44:44 by fdidelot          #+#    #+#             */
/*   Updated: 2021/12/07 19:18:07 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

/************************************************************/
/*					Constructor/Destructor					*/
/************************************************************/
User::User(void) :	_userOrNickCmd(false),
					_commandEnd(false),
					_commandBuf(""),
					_fd(-1),
					_nick(DEFAULT_NICKNAME),
					_server(NULL) {

	_mode.a = false;
	_mode.i = false;
	_mode.w = false;
	_mode.r = false;
	_mode.o = false;
	_mode.O = false;
	_mode.s = false;
	return ;
}

User::User(int fd, Server* server) :	_userOrNickCmd(false),
										_commandEnd(false),
										_commandBuf(""),
										_fd(fd),
										_nick(DEFAULT_NICKNAME),
										_server(server) {

	_mode.a = false;
	_mode.i = false;
	_mode.w = false;
	_mode.r = false;
	_mode.o = false;
	_mode.O = false;
	_mode.s = false;
	return ;
}

User::~User(void) {

	return ;
}

/************************************************************/
/*						Operators							*/
/************************************************************/

/************************************************************/
/*					Getters/Setters							*/
/************************************************************/
/*						Getters								*/
bool	User::getCommandEnd(void) const {

	return (_commandEnd);
}

std::string User::getCommandBuf(void) const {

	return (_commandBuf);
}

int		User::getFd(void) const {

	return (_fd);
}

std::string User::getNick(void) const {

	return (_nick);
}

bool	User::getUserOrNickCmd(void) const {

	return (_userOrNickCmd);
}

bool	User::getMode(char m) const {

	switch (m)
	{
		case 'a':
			return (_mode.a);
		case 'i':
			return (_mode.i);
		case 'w':
			return (_mode.w);
		case 'r':
			return (_mode.r);
		case 'o':
			return (_mode.o);
		case 'O':
			return (_mode.O);
		case 's':
			return (_mode.s);
	}
	return (false);
}

std::string	User::getCurrentWord(void) const {

	return (_currentWord);
}

Server& User::getServer(void) const {

	return (*_server);
}

/*						Setters								*/
void	User::setCommandEnd(bool b) {

	_commandEnd = b;
}

void	User::setNickname(std::string nickname) {

	_nick = nickname;
}

void	User::setUserOrNickCmd(bool b) {

	_userOrNickCmd = b;
}

void	User::setMode(bool onOff, char m) {

	switch (m)
	{
		case 'a':
			_mode.a = onOff;
			break;
		case 'i':
			_mode.i = onOff;
			break;
		case 'w':
			_mode.w = onOff;
			break;
		case 'r':
			_mode.r = onOff;
			break;
		case 'o':
			_mode.o = onOff;
			break;
		case 'O':
			_mode.O = onOff;
			break;
		case 's':
			_mode.s = onOff;
			break;
	}
}

void	User::setCurrentWord(std::string word) {

	_currentWord = word;
}

/************************************************************/
/*					Member functions						*/
/************************************************************/
bool	User::addToBuf(char* buf) {

	size_t	endLine;


	(void)buf;
	endLine = _totalBuf.find("\r\n", 0);
	if ((endLine != std::string::npos))
	{
		_commandBuf = _totalBuf.substr(0, endLine);
		_totalBuf.erase(0, endLine + 2);
		_commandEnd = true;
		return (SUCCESS_ADD);
	}
	return (FAILURE_ADD);
}

void	User::execCommand(std::string commandLine) {

	std::string			commandName;
	std::stringstream	lineStream(commandLine);

	lineStream >> commandName;
	std::cout << "lS = " << lineStream.str() << std::endl << "commandName = " << commandName << std::endl;;

	Command currentCommand(commandName);

	currentCommand.launchCommand(lineStream, *this);
	lineStream.clear();
}

void	User::handleCommand(char* buffer) {

	std::string tmp = buffer;
	std::cout << "Buf receives" << ": " << buffer << std::endl;
	int po = *tmp.c_str();
	std::cout << "Buf tmp" << ": " << po << std::endl;

	if (!(tmp.size() == 1 && *tmp.c_str() == EOT_CODE)) // In case of multiple ctrl+D
		_totalBuf += buffer;
	while (addToBuf(buffer))
	{
		if (getCommandEnd())
		{
			execCommand(getCommandBuf());
			setCommandEnd(false);
			_commandBuf.clear();
		}
	}
}
