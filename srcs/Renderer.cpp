/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:30:07 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/01 17:11:41 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Renderer.hpp"

void	Renderer::renderScene(Scene &scene)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.25f, 0.25f, 0.25f, 1.0f);

	scene.light->shader.use();
	scene.light->shader.setUniformMat4("view", scene.camera->getViewMatrix());
    scene.light->shader.setUniformMat4("projection", scene.camera->getProjMatrix());
	scene.light->shader.setUniformMat4("model", Matrix4f::translation(scene.light->getPos()) * Matrix4f::scaling(Vector3f(0.2f, 0.2f, 0.2f)));
	scene.light->shader.setUniformVec3("lightColor", scene.light->getColor());
	scene.light->mesh.draw();

	for (std::shared_ptr<Object3D> obj : scene.objs)
	{
		obj->shader.use();
        obj->shader.setUniformMat4("view", scene.camera->getViewMatrix());
        obj->shader.setUniformMat4("projection", scene.camera->getProjMatrix());
		obj->transform.setMatrix(Matrix4f::rotationAxis(Vector3f(0.0f, 1.0f, 0.0f), (float)(SDL_GetTicks() / 1000.0f) * (M_PI / 6)));
        obj->shader.setUniformMat4("model", obj->transform.getMatrix());


		// scene.light->setColor(Vector3f(sin((float)(SDL_GetTicks() / 1000.0f)* 2.0f), sin((float)(SDL_GetTicks() / 1000.0f) * 0.7f), sin((float)(SDL_GetTicks() / 1000.0f) * 1.3f)));
		
		obj->shader.setUniformVec3("inLightPos", scene.light->getPos());
		obj->shader.setUniformVec3("lightColor", scene.light->getColor());
		obj->shader.setUniformVec3("viewPos", scene.camera->position);

		obj->shader.setUniformVec3("mtlAmbient", obj->material->ka);
		obj->shader.setUniformVec3("mtlDiffuse", obj->material->kd);
		obj->shader.setUniformVec3("mtlSpecular", obj->material->ks);
		obj->shader.setUniformFloat("mtlShininess", obj->material->ns);


		// std::cout << "light pos: " << scene.light->getPos() << ", camera pos: " << scene.camera->position << std::endl;
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