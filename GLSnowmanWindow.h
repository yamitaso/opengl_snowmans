#pragma once
#ifndef GLSNOWMANWINDOW_H_
#define GLSNOWMANWINDOW_H_

#include "Window.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include "Texture.h"
using VertexVector = std::vector<std::vector<double>>;
using FaceVector = std::vector<std::vector<int>>;
using NormalVector = std::vector<std::vector<double>>;
using ColorVector = std::vector<std::vector<float>>;
using TexCoordVector = std::vector<std::vector<std::vector<double>>>;

struct SimpleModel
{
	VertexVector & vertices;
	FaceVector & faces;
	NormalVector & normals;
	ColorVector & colors;
	TexCoordVector & tex_coords;
};


class GLSnowmanWindow: public Window
{
protected:
	double _angle { 0. };
	double zz = 0., i = 1;
	Texture _house_Texture;
	Texture _roof_Texture;
	Texture _green;
	Texture _orange;

	void draw_model(SimpleModel &model);

public:
	GLSnowmanWindow(
			int width = DEFAULT_WIDTH,
			int height = DEFAULT_HEIGHT);
	virtual ~GLSnowmanWindow() = default;

	virtual void render() override;
	virtual void do_logic() override;
	virtual void handle_keys(const Uint8 *keys) override;
	virtual void setup() override;
};


#endif /* GLSNOWMANWINDOW_H_ */
