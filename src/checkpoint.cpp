#include "checkpoint.h"
#include "main.h"

Checkpoint::Checkpoint(float x, float y, float z, color_t color) {
	this->position = glm::vec3(x, y, z);
	this->rotation = rand() % 360;
	this->claimed = 0;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

	float size = 5.0;
	this->tip_x = -size + (rand() % 20*size)/10.0;
	this->tip_z = -size + (rand() % 20*size)/10.0;
	this->tip_y = (rand() % 20)/10.0;
	GLfloat vertex_buffer_data_body[] = {
        -size, 0.0f, -size,
        -size, 0.0f, size,
        size, 0.0f, -size,
        -size, 0.0f, size,
        size, 0.0f, -size,
        size, 0.0f, size,
        -size, 0.0f, -size,
        -size, 0.0f, size,
        this->tip_x, this->tip_y, this->tip_z,
        -size, 0.0f, -size,
        size, 0.0f, -size,
        this->tip_x, this->tip_y, this->tip_z,
        -size, 0.0f, size,
        size, 0.0f, size,
        this->tip_x, this->tip_y, this->tip_z,
        size, 0.0f, -size,
        size, 0.0f, size,
        this->tip_x, this->tip_y, this->tip_z,
	};


	this->object_body = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data_body, color, GL_FILL);
}

void Checkpoint::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(0, 1, 0));
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object_body);
}

void Checkpoint::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

