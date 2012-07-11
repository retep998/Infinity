varying vec3 texc;
uniform sampler2DArray ttex;
void main(void) {
	gl_FragColor = texture(ttex, texc);
}