#version 330
varying vec3 texc;
uniform sampler2DArray ttex;
void main(void) {
	gl_FragColor = vec4(1, 0, 0, 1);
	gl_FragColor = texture(ttex, texc);
}