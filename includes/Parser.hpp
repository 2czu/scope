/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:02:52 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/22 17:10:08 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include "Mesh.hpp"
#include <cfloat>

class Parser
{
	public :
		Parser() {};
		~Parser() {};

		static Mesh	parseObjFile(const std::string &filepath);
};