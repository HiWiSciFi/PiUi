#version 310 es

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 vertexUv;

layout(location = 0) out vec2 uv;

void main() {
	gl_Position = vec4(pos.x * 2.0 - 1.0, pos.y * -2.0 + 1.0, pos.z, 1.0);
	uv = vertexUv;
}
