#include "GLSnowmanWindow.h"
#include "Primitives.h"
#include <stdexcept>
#include <SDL2/SDL_image.h>

GLSnowmanWindow::GLSnowmanWindow(int width, int height)
: Window(width, height),
  _house_Texture("house.png"), _roof_Texture("roof.png"),
  _orange("orange.png"), _green("green.png")
{
	SDL_GL_SetSwapInterval(1);
}

//Коробка дома

static VertexVector house_cube_vertices {
	{  4.0,  4.0,  2.0 },
	{  4.0,  0.0,  2.0 },
	{  0.0,  0.0,  2.0 },
	{  0.0,  4.0,  2.0 },
	{  4.0,  4.0,  0.0 },
	{  4.0,  0.0,  0.0 },
	{  0.0,  0.0,  0.0 },
	{  0.0,  4.0,  0.0 },
};

static FaceVector house_cube_faces {
	{ 4, 0, 1, 2, 3 },
	{ 4, 7, 6, 5, 4 },
	{ 4, 1, 0, 4, 5 },
	{ 4, 3, 2, 6, 7 },
	{ 4, 0, 3, 7, 4 },
	{ 4, 2, 1, 5, 6 },
};

static NormalVector house_cube_normals {
	{  0.0,  0.0,  1.0 },
	{  0.0,  0.0, -1.0 },
	{  1.0,  0.0,  0.0 },
	{ -1.0,  0.0,  0.0 },
	{  0.0,  1.0,  0.0 },
	{  0.0, -1.0,  0.0 },
};

static ColorVector house_cube_colors {
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
};

static TexCoordVector house_cube_tex_coords {
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.50, 0.50 }, { 1.00, 0.50 }, { 1.00, 1.00 }, { 0.50, 1.00 } },
	{ { 0.50, 0.00 }, { 1.00, 0.00 }, { 1.00, 0.50 }, { 0.50, 0.50 } },
	{ { 0.00, 0.00 }, { 0.50, 0.00 }, { 0.50, 0.50 }, { 0.00, 0.50 } },
	{ { 0.00, 0.50 }, { 0.50, 0.50 }, { 0.50, 1.00 }, { 0.00, 1.00 } },
};

//Крыша дома

static VertexVector house_roof_vertices {
	{  4.0,   0.0,  2.0 },
	{  4.0,   4.0,  2.0 },
	{  0.0,   4.0,  2.0 },
	{  0.0,   0.0,  2.0 },
	{  4.0,   2.0,  4.0 },
	{  0.0,   2.0,  4.0 },
};

static FaceVector house_roof_faces {
	{ 4, 0, 1, 2, 3 },
	{ 4, 1, 4, 5, 2 },
	{ 4, 0, 3, 5, 4 },
	{ 3, 0, 4, 1 },
	{ 3, 2, 5, 3 },
};

static NormalVector house_roof_normals {
	{  0.0,  0.0, -1.0 },
	{  0.0,  1.0,  1.0 },
	{  0.0, -1.0,  1.0 },
	{  1.0,  0.0,  0.0 },
	{ -1.0,  0.0,  0.0 },
};

static ColorVector house_roof_colors {
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
};

static TexCoordVector house_roof_tex_coords {
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 1.00 }, { 0.00, 0.00 }, { 0.50, 0.00 }, { 0.50, 1.00 } },
	{ { 0.50, 1.00 }, { 0.00, 1.00 }, { 0.00, 0.00 }, { 0.50, 0.00 } },
	{ { 0.50, 1.00 }, { 0.75, 0.7 },  { 1.00, 1.00 } },
	{ { 0.50, 1.00 }, { 0.75, 0.7 },  { 1.00, 1.00 } },
};

//Дымоход

static VertexVector house_chimney_vertices {
	{  3.75,  0.75, 4.4 },
	{  3.75,  0.5,  4.4 },
	{  3.5,   0.5,  4.4 },
	{  3.5,   0.75, 4.4 },
	{  3.75,  0.75, 2.0 },
	{  3.75,  0.5,  2.0 },
	{  3.5,   0.5,  2.0 },
	{  3.5,   0.75, 2.0 },
};

static FaceVector house_chimney_faces {
	{ 4, 0, 1, 2, 3 },
	{ 4, 7, 6, 5, 4 },
	{ 4, 1, 0, 4, 5 },
	{ 4, 3, 2, 6, 7 },
	{ 4, 0, 3, 7, 4 },
	{ 4, 2, 1, 5, 6 },
};

static NormalVector house_chimney_normals {
	{  0.0,  0.0,  1.0 },
	{  0.0,  0.0, -1.0 },
	{  1.0,  0.0,  0.0 },
	{ -1.0,  0.0,  0.0 },
	{  0.0,  1.0,  0.0 },
	{  0.0, -1.0,  0.0 },
};

static ColorVector house_chimney_colors {
	{  0.0f,  0.0f,  0.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
	{  1.0f,  1.0f,  1.0f },
};

static TexCoordVector house_chimney_tex_coords {
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 }, { 0.00, 0.00 } },
	{ { 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00 }, { 0.00, 1.00 } },
	{ { 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00 }, { 0.00, 1.00 } },
	{ { 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00 }, { 0.00, 1.00 } },
	{ { 0.00, 0.00 }, { 1.00, 0.00 }, { 1.00, 1.00 }, { 0.00, 1.00 } },
};

SimpleModel cube { house_cube_vertices, house_cube_faces, house_cube_normals, house_cube_colors, house_cube_tex_coords };
SimpleModel roof { house_roof_vertices, house_roof_faces, house_roof_normals, house_roof_colors, house_roof_tex_coords };
SimpleModel chimney { house_chimney_vertices, house_chimney_faces, house_chimney_normals, house_chimney_colors, house_chimney_tex_coords };




void GLSnowmanWindow::setup()
{
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_TEXTURE);

	glClearColor(0.3f, 0, 0.5f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	gluPerspective(45.0, double(width()) / double(height()), 0.1, 30.0);
	glMatrixMode(GL_MODELVIEW);

}
void GLSnowmanWindow::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(10.0, 10.0, 8.0,
			    -4.0, -2.0, 0.0,
				0.0, 0.0, 2.0);
	glRotated(_angle, 0.0, 0.0, 1.0);

	_green.bind();

	glEnable(GL_TEXTURE_2D);
	draw_tree(64, 6., -2., 1, 0, 1.0);
	draw_tree(64, 6., -2., 1.5, 0.5, 0.9);
	draw_tree(64, 6., -2., 2.0, 1.0, 0.8);
	draw_tree(64, 6., -2., 2.5, 1.5, 0.7);
	draw_tree(64, 6., -2., 3.0, 2.0, 0.6);
	draw_tree(64, 6., -2., 3.5, 2.5, 0.5);
	draw_tree(64, 6., -2., 4.0, 3.0, 0.4);
	draw_tree(64, 6., -2., 4.5, 3.5, 0.3);

	draw_tree(64, 6., 6., 1, 0, 1.0);
	draw_tree(64, 6., 6., 1.5, 0.5, 0.9);
	draw_tree(64, 6., 6., 2.0, 1.0, 0.8);
	draw_tree(64, 6., 6., 2.5, 1.5, 0.7);
	draw_tree(64, 6., 6., 3.0, 2.0, 0.6);

	draw_tree(64, -2., -2., 1, 0, 1.0);
	draw_tree(64, -2., -2., 1.5, 0.5, 0.9);
	draw_tree(64, -2., -2., 2.0, 1.0, 0.8);
	draw_tree(64, -2., -2., 2.5, 1.5, 0.7);
	draw_tree(64, -2., -2., 3.0, 2.0, 0.6);

	draw_tree(64, -2., 6., 1, 0, 1.0);
	draw_tree(64, -2., 6., 1.5, 0.5, 0.9);
	draw_tree(64, -2., 6., 2.0, 1.0, 0.8);
	draw_tree(64, -2., 6., 2.5, 1.5, 0.7);
	draw_tree(64, -2., 6., 3.0, 2.0, 0.6);
	draw_tree(64, -2., 6., 3.5, 2.5, 0.5);
	draw_tree(64, -2., 6., 4.0, 3.0, 0.4);
	draw_tree(64, -2., 6., 4.5, 3.5, 0.3);

	glDisable(GL_TEXTURE_2D);

	draw_sphere_smooth(32, 16, 2, 6, 0.5+zz, 0.5);
	draw_sphere_smooth(32, 16, 2, 6, 1.2+zz, 0.35);
	draw_sphere_smooth(32, 16, 2, 6, 1.7+zz, 0.2);

	draw_sphere_smooth(32, 16, 2, -2, 0.5+zz, 0.5);
	draw_sphere_smooth(32, 16, 2, -2, 1.2+zz, 0.35);
	draw_sphere_smooth(32, 16, 2, -2, 1.7+zz, 0.2);

	draw_sphere_smooth(32, 16, 6, 2, 0.5+zz, 0.5);
	draw_sphere_smooth(32, 16, 6, 2, 1.2+zz, 0.35);
	draw_sphere_smooth(32, 16, 6, 2, 1.7+zz, 0.2);

	_orange.bind();

	glEnable(GL_TEXTURE_2D);

	draw_carrot(32, 1.7+zz, 6, 2.5, 1.9, 0.05);
	draw_carrot(32, 1.7+zz, -2, 2.5, 1.9, 0.05);
	draw_carrot(32, 1.7+zz, 2, 7, 5.9, 0.05);





	glDisable(GL_TEXTURE_2D);

	_house_Texture.bind();
	glEnable(GL_TEXTURE_2D);
	draw_model(cube);
	glDisable(GL_TEXTURE_2D);

	_roof_Texture.bind();
	glEnable(GL_TEXTURE_2D);
	draw_model(roof);
	glDisable(GL_TEXTURE_2D);

	_roof_Texture.bind();
	glEnable(GL_TEXTURE_2D);
	draw_model(chimney);
	glDisable(GL_TEXTURE_2D);
}



void GLSnowmanWindow::draw_model(SimpleModel &model)
{
	for (unsigned i = 0; i < model.faces.size(); ++i) {
		int count = model.faces[i][0];
		if (count == 3)
			glBegin(GL_TRIANGLES);
		else if (count == 4)
			glBegin(GL_QUADS);
		else
			glBegin(GL_POLYGON);

		glNormal3dv(&model.normals[i][0]);
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, &model.colors[i][0]);
		for (int j = 1; j <= count; ++j) {
			glTexCoord2dv(&model.tex_coords[i][j-1][0]);
			glVertex3dv(&model.vertices[model.faces[i][j]][0]);
		}

		glEnd();
	}
}


void GLSnowmanWindow::do_logic()
{
	_angle -= 0.2;
	if (_angle >= 360.)
		_angle = 0.;

	zz += 0.02 * i;
	if (zz >= 0.5) i = -1;
	else if (zz <= 0) i = 1;
}

void GLSnowmanWindow::handle_keys(const Uint8 *keys)
{


}
