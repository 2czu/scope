/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 13:02:52 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/03 17:08:14 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include "Mesh.hpp"
#include "Material.hpp"
#include <cfloat>

class Parser
{
	public :
		Parser() {};
		~Parser() {};

		static Mesh		loadMesh(const std::string &filepath);
};