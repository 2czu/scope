/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Transform.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 16:46:45 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/27 15:29:41 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Transform.hpp"

Matrix4f Transform::getMatrix()
{
	return this->m;
}

void	 Transform::setMatrix(const Matrix4f &m)
{
	this->m = m;
}