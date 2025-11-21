/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Material.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 15:58:07 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/21 16:04:21 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Material.hpp"

void Material::compileShaders()
{
	Shader vertex = Shader("./shaders/shader.vs", GL_VERTEX_SHADER);
    Shader fragment = Shader("./shaders/shader.fs", GL_FRAGMENT_SHADER);
    
    shader.attachShader(vertex);
    shader.attachShader(fragment);
    shader.link();

}