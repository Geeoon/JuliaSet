uniform sampler2D texture;
uniform float R;
uniform vec2 c;
uniform vec2 viewportSize;
uniform int maxIteration;

void main() {
vec2 uv = gl_FragCoord.xy / viewportSize;
	vec2 z = vec2((uv.x - 0.5) * 2 * R, (uv.y - 0.5) * 2 * R);
	int i = 0;
	while (length(z) < R && i < maxIteration) {
		float xtemp = z.x * z.x - z.y * z.y;
		z.y = 2 * z.x * z.y + c.y;
		z.x = xtemp + c.x;
		i++;
	}
	
	if (i == maxIteration) {
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	} else {
		gl_FragColor = vec4(i / maxIteration, 1.0, 1.0, 1.0);
	}
}