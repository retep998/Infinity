attribute vec2 pos;
attribute vec2 tpos;
uniform sampler2D tex;
uniform vec2 vsize;
uniform vec2 vpos;
varying vec4 color;
void main(void) {
	gl_Position = vec4((pos+tpos+vpos)*32/vsize, 0, 1);
	color = texture(tex, pos/256);
}