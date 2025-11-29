/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LightSource.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 18:05:41 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/29 19:27:39 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "ShaderProgram.hpp"
#include "Mesh.hpp"
#include "Parser.hpp"

class LightSource
{
	
	public:
		LightSource(std::string meshpath, std::string shaderf);
		~LightSource()	{};

		Vector3f		position;
		Vector3f		color;
		ShaderProgram	shader;
		Mesh			mesh;

		void			setColor(const Vector3f &color) { this->color = color; };
		Vector3f		&getColor() { return this->color; };

		void			setPos(const Vector3f &position) { this->position = position; };
		Vector3f		&getPos() { return this->position; };
};