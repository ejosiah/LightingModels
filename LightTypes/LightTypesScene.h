#pragma once

#include <ncl/gl/Scene.h>

using namespace std;
using namespace glm;
using namespace ncl;
using namespace gl;

static const float FOV = pi<float>() * third<float>();
static const float speed = one_over_pi<float>();
static const vec3 angularV = vec3{ 0, 1, 0 } * speed;

class LigthTypesScene : public Scene {
public:
	LigthTypesScene() :Scene("Light types scene") {
		_useImplictShaderLoad = true;
		sphericalCoord = { 0, 0.66f, -1.0f };
	}

	virtual void init() override {
		model = new Model("C:\\Users\\joebh\\OneDrive\\media\\models\\ChineseDragon.obj", true);
		crosshairs = new CrossHair(0.1);
		Material& m = model->material();
		m.ambient = { 0.329412f, 0.223529f, 0.027451f,1.0f };
		m.diffuse = { 0.780392f, 0.568627f, 0.113725f, 1.0f };
		m.specular = { 0.992157f, 0.941176f, 0.807843f, 1.0f };
		m.shininess = 128.0f * 0.4F;
		float z = model->bound->m.length;
		sphericalCoord.x = distance(model->bound->min(), model->bound->max());
		z *= 2;
		cam.view = lookAt({ 0, 0, 1.25}, vec3(0), { 0, 1, 0 });
		light[0].on = true;
		light[0].transform = true;
		light[0].position = inverse(cam.view) * vec4(0, 0, 0, 1);
		lightModel.useObjectSpace = false;
		normalMap = new Texture2D("C:\\Users\\joebh\\OneDrive\\media\\models\\Game_model\\Character_Normals.png", 13);
		colorMap = new Texture2D("C:\\Users\\joebh\\OneDrive\\media\\models\\Game_model\\Character_Albedo.tif", 11);
		shader("render")([&](Shader& s) {
		//	normalMap->sendTo(s);
		//	colorMap->sendTo(s);
		//	glActiveTexture(GL_TEXTURE10);
		//	glBindTexture(GL_TEXTURE_2D, colorMap->bufferId());
		//	s.sendUniform1ui("ambient", 10);
		//	glActiveTexture(TEXTURE(0));
		//	s.send(lightModel);
		
		});

	}

	virtual void display() override {

		//light[0].position = toCartesian(sphericalCoord);
		cam.model = mat4_cast(orientation);
		shader("render")([&](Shader& s) {
			s.sendComputed(cam);
			s.sendUniformLight("light[0]", light[0]);
			model->draw(s);
		});

		shader("flat")([&](Shader& s) {
			s.sendComputed(cam);
			model->bound->draw(s);

			vec3 p = light[0].position.xyz;
			cam.model = translate(mat4(1), p);
			s.sendComputed(cam);
			crosshairs->draw(s);
		});
	}

	virtual void resized() override {
		cam.projection = perspective(radians(75.f), aspectRatio, 0.3f, 1000.f);
	}

	virtual void update(float dt) {
		quat w(0, angularV * dt);

		Orientation q = orientation;
		orientation = q + (w * q) * 0.5f;
	}

	vec4 toCartesian(vec3 spherical) {
		float r = spherical.x;
		float zineth = spherical.z;
		float azumith = spherical.y;
		return vec4{
			r * sin(zineth) * sin(azumith),
			r * cos(zineth),
			r * sin(zineth) * cos(azumith),
			1
		};
	}

private:
	Model* model;
	Orientation orientation;
	CrossHair* crosshairs;
	Texture2D* normalMap;
	Texture2D* colorMap;
	vec3 sphericalCoord;
};