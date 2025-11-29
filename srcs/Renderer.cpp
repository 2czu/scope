/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:30:07 by pacda-si          #+#    #+#             */
/*   Updated: 2025/11/29 19:41:13 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Renderer.hpp"

void	Renderer::renderScene(Scene &scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	scene.light->shader.use();
	scene.light->shader.setUniformMat4("view", scene.camera->getViewMatrix());
    scene.light->shader.setUniformMat4("projection", scene.camera->getProjMatrix());
	scene.light->shader.setUniformMat4("model", Matrix4f().translation(scene.light->getPos()) * Matrix4f().scaling(Vector3f(0.5f, 0.5f, 0.5f)));
	scene.light->shader.setUniformVec3("lightColor", scene.light->getColor());
	scene.light->mesh.draw();
	

	for (std::shared_ptr<Object3D> obj : scene.objs)
	{
		obj->shader.use();
        obj->shader.setUniformMat4("view", scene.camera->getViewMatrix());
        obj->shader.setUniformMat4("projection", scene.camera->getProjMatrix());
		obj->transform.setMatrix(Matrix4f().rotationY(-0.5f));
        obj->shader.setUniformMat4("model", obj->transform.getMatrix());

		obj->shader.setUniformVec3("inLightPos", scene.light->getPos());
		obj->shader.setUniformVec3("lightColor", scene.light->getColor());
		// obj.material.texture.bind();
		
        obj->mesh.draw();
		
		// obj.material.texture.unbind();
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