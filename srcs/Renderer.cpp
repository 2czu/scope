/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Renderer.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pacda-si <pacda-si@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:30:07 by pacda-si          #+#    #+#             */
/*   Updated: 2025/12/08 15:31:57 by pacda-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Renderer.hpp"

void	Renderer::renderImGui(Scene &scene)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Interface");

	ImGui::Text("FPS : %f", displayFPS);
	ImGui::ColorEdit3("LIGHT COLOR", scene.light->color.data());
	
	ImGui::End();

	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void	Renderer::renderScene(Scene &scene)
{
	static float texOpacity = 0.0f;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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
		obj->transform.setMatrix(Matrix4f::rotationAxis(Vector3f(0.0f, 1.0f, 0.0f), (float)(SDL_GetTicks() / 1000.0f) * (M_PI / 4)));
        obj->shader.setUniformMat4("model", obj->transform.getMatrix());

		// scene.light->setColor(Vector3f(sin((float)(SDL_GetTicks() / 1000.0f)* 2.0f), sin((float)(SDL_GetTicks() / 1000.0f) * 0.7f), sin((float)(SDL_GetTicks() / 1000.0f) * 1.3f)));
		
		Vector3f &lightColor = scene.light->getColor();
		obj->shader.setUniformVec3("light.position", scene.light->getPos());
		obj->shader.setUniformVec3("light.ambient", lightColor * 1.0f);
		obj->shader.setUniformVec3("light.diffuse", lightColor * 1.0f);
		obj->shader.setUniformVec3("light.specular", lightColor * 1.0f);
		obj->shader.setUniformFloat("light.constant", 1.0f);
		obj->shader.setUniformFloat("light.linear", 0.14);
		obj->shader.setUniformFloat("light.quadratic", 0.07f);
		obj->shader.setUniformVec3("viewPos", scene.camera->position);

		if (applyTexture == 1)
		{
			texOpacity += 0.025f;
			if (texOpacity >= 1.0f)
				texOpacity = 1.0f;
		}
		else
		{
			texOpacity -= 0.025f;
			if (texOpacity <= 0.0f)
				texOpacity = 0.0f;
		}

		obj->shader.setUniformFloat("texOpacity", texOpacity);
		// std::cout << "light pos: " << scene.light->getPos() << ", camera pos: " << scene.camera->position << std::endl;
		
        obj->mesh.draw();
		
	}
}