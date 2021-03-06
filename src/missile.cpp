#include "missile.h"
#include "main.h"

Missile::Missile(float x, float y, float z, color_t color) {
	this->position = glm::vec3(x, y, z);
	this->rotation = glm::vec3(0, 0, 0);
	this->speed = 0.1;
	this->g = 0.03;
	// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices

	int n = 100;
	float l = 1.0f, r = 0.2f;
	GLfloat vertex_buffer_data_body[36*n];
	for(int i=0; i<36*n; i+=36){ 
		vertex_buffer_data_body[i]    = (float)r*cos(((i/36))*2*3.14159265/n);
		vertex_buffer_data_body[i+1]  = 0.0f;
		vertex_buffer_data_body[i+2]  = (float)r*sin(((i/36))*2*3.14159265/n);
		vertex_buffer_data_body[i+3]  = (float)r*cos(((i/36)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+4]  = 0.0f;
		vertex_buffer_data_body[i+5]  = (float)r*sin(((i/36)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+6]  = (float)r*cos(((i/36))*2*3.14159265/n);
		vertex_buffer_data_body[i+7]  = l;
		vertex_buffer_data_body[i+8]  = (float)r*sin(((i/36))*2*3.14159265/n);
		vertex_buffer_data_body[i+9]  = (float)r*cos(((i/36))*2*3.14159265/n);
		vertex_buffer_data_body[i+10] = l;
		vertex_buffer_data_body[i+11] = (float)r*sin(((i/36))*2*3.14159265/n);
		vertex_buffer_data_body[i+12] = (float)r*cos(((i/36)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+13] = l;
		vertex_buffer_data_body[i+14] = (float)r*sin(((i/36)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+15] = (float)r*cos(((i/36)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+16] = 0.0f;
		vertex_buffer_data_body[i+17] = (float)r*sin(((i/36)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+18] = (float)r*cos(((i/36))*2*3.14159265/n);
		vertex_buffer_data_body[i+19] = 0.0f;
		vertex_buffer_data_body[i+20] = (float)r*sin(((i/36))*2*3.14159265/n);
		vertex_buffer_data_body[i+21] = (float)r*cos(((i/36)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+22] = 0.0f;
		vertex_buffer_data_body[i+23] = (float)r*sin(((i/36)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+24] = 0.0f;
		vertex_buffer_data_body[i+25] = 0.0f;
		vertex_buffer_data_body[i+26] = 0.0f;
		vertex_buffer_data_body[i+27] = (float)r*cos(((i/36))*2*3.14159265/n);
		vertex_buffer_data_body[i+28] = l;
		vertex_buffer_data_body[i+29] = (float)r*sin(((i/36))*2*3.14159265/n);
		vertex_buffer_data_body[i+30] = (float)r*cos(((i/36)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+31] = l;
		vertex_buffer_data_body[i+32] = (float)r*sin(((i/36)+1)*2*3.14159265/n);
		vertex_buffer_data_body[i+33] = 0.0f;
		vertex_buffer_data_body[i+34] = l;
		vertex_buffer_data_body[i+35] = 0.0f;
	}

	this->object_body = create3DObject(GL_TRIANGLES, 12*n, vertex_buffer_data_body, color, GL_FILL);
}

void Missile::draw(glm::mat4 VP) {
	Matrices.model = glm::mat4(1.0f);
	glm::mat4 translate = glm::translate (this->position);    // glTranslatef
	glm::mat4 rotate_x = glm::rotate((float) (this->rotation.x * M_PI / 180.0f), glm::vec3(1, 0, 0));
	glm::mat4 rotate_y = glm::rotate((float) (this->rotation.y * M_PI / 180.0f), glm::vec3(0, 1, 0));
	// No need as coords centered at 0, 0, 0 of cube around which we waant to rotate
	// rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
	Matrices.model *= (translate * rotate_x * rotate_y);
	glm::mat4 MVP = VP * Matrices.model;
	glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
	draw3DObject(this->object_body);
}

void Missile::set_position(float x, float y, float z, float rotation_x, float rotation_y, float rotation_z) {
	this->position = glm::vec3(x + 3.0 * cos(rotation_y * M_PI / 180.0f) * sin(rotation_x * M_PI / 180.0f), y + 3.0 * sin(rotation_y * M_PI / 180.0f), z + 3.0 * cos(rotation_y * M_PI / 180.0f) * cos(rotation_x * M_PI / 180.0f));
	this->rotation = glm::vec3(90, rotation_y, 0);
}

void Missile::move() {
	if(this->position.y < -2.0) {
		this->position.y = -10.0f;
		this->speed = 0.1;
	}
	else {
		this->speed += g;
		this->position.y -= this->speed;
		this->position.x += (1.0 * (sin(this->rotation.y * M_PI / 180.0)));
		this->position.z += (1.0 * (cos(this->rotation.y * M_PI / 180.0)));
	}
}
