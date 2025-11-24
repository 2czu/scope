/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Object3D.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:03:55 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/24 13:38:47 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mesh.hpp"
#include "Material.hpp"
#include "Parser.hpp"
#include "Transform.hpp"

class Object3D
{
	private :
	
	public :
		Mesh		mesh;
		Material	material;
		Transform	transform;

		Object3D(const std::string &filepath, const std::string &shader, const std::string &texture);
		~Object3D() {};

};