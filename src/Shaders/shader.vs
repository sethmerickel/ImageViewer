#version 410 core
layout (location = 0) in vec3 vertex_coord;
layout (location = 1) in vec3 vertex_color;
layout (location = 2) in vec2 texture_coord;

out vec3 out_color;
out vec2 tex_coord;

void main()
{
   gl_Position = vec4(vertex_coord, 1.0);
   out_color = vertex_color;
   tex_coord = texture_coord;
}


