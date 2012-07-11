attribute vec2 pos;
attribute vec2 tpos;
uniform sampler2D tex;
uniform vec2 vsize;
uniform vec2 vpos;
varying vec3 texc;
void main(void) {
	vec2 t = (pos+tpos+vpos)*32/vsize;
	gl_Position = vec4(t.x, -t.y, 0, 1);
	texc = vec3(tpos, texture(tex, pos/256).x*5);
	//texc = vec3(tpos, 0);
}