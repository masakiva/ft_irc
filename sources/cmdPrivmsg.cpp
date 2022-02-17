/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdPrivmsg.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psemsari <psemsari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:25:17 by psemsari          #+#    #+#             */
/*   Updated: 2022/02/17 11:49:48 by psemsari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Command.hpp"

void	Command::_privmsg(std::stringstream& completeCommand, User& user){

	//:prefix PRIVMSG user/#target | message suitemessage
	//send((*it)->getFd(), str.c_str(), str.size(), NULL);
	std::string target;
	completeCommand >> target;
	std::cout << "OUTPUT target = " << target << std::endl;
	if (target[0] == '#')
	{
		Channel* chan_ptr = user.getChannel(target);
		if (chan_ptr == NULL)
			sendCommand(user, ERRCODE_CANNOTSENDTOCHAN, ERR_CANNOTSENDTOCHAN(target));
		else
			chan_ptr->sendToChannel(completeCommand.str(), *this);
	}
	else
	{
		User *user_ptr = user.getServer().getUser(target);
		std::cout << completeCommand.str() << std::endl;
		if (user_ptr == NULL)
			sendCommand(user, ERRCODE_NOSUCHNICK, ERR_NOSUCHNICK(target));
		else
			sendCommand(*user_ptr, PONG, completeCommand.str());
	}
}
