/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdMode.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdidelot <fdidelot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:23:40 by psemsari          #+#    #+#             */
/*   Updated: 2022/03/03 17:49:55 by fdidelot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_mode(std::stringstream& completeCommand, User& user) {

	std::string	target;
	std::string	modes;

	completeCommand >> target;
	completeCommand >> modes;
	if (user.getServer().findByNickName(user, target) == NULL
		&& user.getChannel(target) == NULL)
	{
		sendCommand(user, ERRCODE_NOSUCHNICK, ERR_NOSUCHNICK(target));
		return ;
	}
	if (modes.empty() && target.c_str()[0] == '#')
	{
		sendCommand(user, RPLCODE_CHANNELMODEIS,
				RPL_CHANNELMODEIS(user.getChannel(target)->getName(),
				"", ""));
	}
	else
	{
		user.setMode((*modes.c_str() == '-' ? false : true), modes.c_str());
		sendCommand(user, RPLCODE_UMODEIS, RPL_UMODEIS(user.getModes()));
	}
}
