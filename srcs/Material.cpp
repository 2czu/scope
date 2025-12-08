/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:58:07 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/08 16:00:20 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Material.hpp"

Material::Material(const Material &other)
{
	this->ns = other.ns;
	this->kd = other.kd;
	this->ka = other.ka;
	this->ks = other.ks;
	this->d = other.d;
	this->illum = other.illum;
	this->name = other.name;
}

Material *Material::clone(void)
{
	return (new Material(*this));
}

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

void Material::bind(ShaderProgram *shader)
{
	shader->setUniformVec3("material.ambient", ka);
	shader->setUniformVec3("material.diffuse", kd);
	shader->setUniformVec3("material.specular", ks);
	shader->setUniformFloat("material.shininess", ns);
	shader->setUniformFloat("material.alpha", d);
	shader->setUniformFloat("material.illum", illum);
}