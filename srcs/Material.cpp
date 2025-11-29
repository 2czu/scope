/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:58:07 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/27 13:47:42 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Material.hpp"

void Material::print() const {
	std::cout << "Material properties:\n";
	std::cout << "Ka: (" << ka.x << ", " << ka.y << ", " << ka.z << ")\n";
	std::cout << "Kd: (" << kd.x << ", " << kd.y << ", " << kd.z << ")\n";
	std::cout << "Ks: (" << ks.x << ", " << ks.y << ", " << ks.z << ")\n";
	std::cout << "Ns: " << ns << "\n";
	std::cout << "d: " << d << "\n";
	std::cout << "illum: " << illum << "\n";
	std::cout << "name: " << name << "\n";
}