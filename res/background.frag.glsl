#version 310 es

precision mediump float;

layout(location = 0) in vec2 uv;

layout(location = 0) out vec4 outColor;

void main() {
	vec3 upper = vec3(0.68627, 0.0, 0.92157);
	vec3 lower = vec3(0.0, 0.0, 0.0);
	vec3 mixed = mix(lower, upper, uv.y);

	outColor = vec4(mixed, 1.0);
}
