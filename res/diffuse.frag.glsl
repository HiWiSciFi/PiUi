#version 310 es

precision mediump float;

uniform vec4 color;

layout(location = 0) out vec4 outColor;

void main() {
	outColor = color;
}
