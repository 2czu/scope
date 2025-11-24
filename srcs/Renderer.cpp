/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:30:07 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/24 16:22:16 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Renderer.hpp"

void	Renderer::renderScene(Scene &scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Object3D &obj : scene.objs)
	{
		obj.material.shader.use();
        obj.material.shader.setUniformMat4("view", scene.camera->getViewMatrix());
        obj.material.shader.setUniformMat4("projection", scene.camera->getProjMatrix());
        obj.material.shader.setUniformMat4("model", obj.transform.getMatrix());
		obj.material.texture.bind();

        obj.mesh.draw();

		obj.material.texture.unbind();
	}
}