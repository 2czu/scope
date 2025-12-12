/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object3D.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:03:55 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/12 16:54:43 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Mesh.hpp"
#include "Material.hpp"
#include "Parser.hpp"
#include "Transform.hpp"
#include <unordered_map>
#include <memory>

struct Object3D
{
	Mesh										mesh;
	Transform									transform;
	ShaderProgram								shader;

	Object3D(const std::string &meshpath, const std::string &shaderf, const std::string &texture);
	~Object3D() {};
};