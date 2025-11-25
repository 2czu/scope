/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:30:07 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/25 21:07:19 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Renderer.hpp"

void	Renderer::renderScene(Scene &scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);

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
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("frame test");

	ImGui::Text("text test");
	
	ImGui::End();

	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}