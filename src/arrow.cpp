#include "arrow.h"
#include "main.h"

Arrow::Arrow(float x, float y, float z, color_t color) {
	this->position = glm::vec3(x, y, z);
	this->rotation = 0;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

	float size = 1.0f;
	GLfloat vertex_buffer_data_tail[] = {
                -size,-size,-size, // triangle 1 : begin
                -size,-size, size,
                -size, size, size, // triangle 1 : end
                size, size,-size, // triangle 2 : begin
                -size,-size,-size,
                -size, size,-size, // triangle 2 : end
                size,-size, size,
                -size,-size,-size,
                size,-size,-size,
                size, size,-size,
                size,-size,-size,
                -size,-size,-size,
                -size,-size,-size,
                -size, size, size,
                -size, size,-size,
                size,-size, size,
                -size,-size, size,
                -size,-size,-size,
                -size, size, size,
                -size,-size, size,
                size,-size, size,
                size, size, size,
                size,-size,-size,
                size, size,-size,
                size,-size,-size,
                size, size, size,
                size,-size, size,
                size, size, size,
                size, size,-size,
                -size, size,-size,
                size, size, size,
                -size, size,-size,
                -size, size, size,
                size, size, size,
                -size, size, size,
                size,-size, size
	};

        GLfloat vertex_buffer_data_head[] = {
                -2*size, -size, -2*size,
                -2*size, -size, 2*size,
                0.0f, -2*size, 0.0f,
                -2*size, -size, -2*size,
                2*size, -size, -2*size,
                0.0f, -2*size, 0.0f,
                2*size, -size, -2*size,
                2*size, -size, 2*size,
                0.0f, -2*size, 0.0f,
                -2*size, -size, 2*size,
                2*size, -size, 2*size,
                0.0f, -2*size, 0.0f,       
        };

	this->object_tail = create3DObject(GL_TRIANGLES, 36, vertex_buffer_data_tail, color, GL_FILL);
        this->object_head = create3DObject(GL_TRIANGLES, 12, vertex_buffer_data_head, color, GL_FILL);
}

void Arrow::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
	// No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object_tail);
        draw3DObject(this->object_head);
}

void Arrow::set_position(float x, float y, float z) {
	this->position = glm::vec3(x, y, z);
}

