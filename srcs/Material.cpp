/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:58:07 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/02 14:59:06 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Material.hpp"

void Material::print() const {
	std::cout << "Material properties:\n";
	std::cout << "Ka: " << ka << "\n";
	std::cout << "Kd: " << kd << "\n";
	std::cout << "Ks: " << ks << "\n";
	std::cout << "Ns: " << ns << "\n";
	std::cout << "d: " << d << "\n";
	std::cout << "illum: " << illum << "\n";
	std::cout << "name: " << name << "\n";
}