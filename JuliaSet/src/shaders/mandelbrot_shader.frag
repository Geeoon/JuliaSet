uniform sampler2D texture;
uniform vec2 viewportSize;
uniform int maxIteration;
uniform float zoom;
uniform vec2 position;

void main() {
vec2 uv = gl_FragCoord.xy / viewportSize;
	vec2 z0 = vec2((uv.x + position.x) * 2.0 * zoom, (uv.y + position.y) * 2.0 * zoom);
	vec2 z = vec2(0.0, 0.0);
	int i = 0;
	while (length(z) < 2.0 && i < maxIteration) {
		float xtemp = z.x * z.x - z.y * z.y + z0.x;
		z.y = 2 * z.x * z.y + z0.y;
		z.x = xtemp;
		i++;
	}
	
	if (i == maxIteration) {
		gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);
	} else {
		vec2 color = vec2(pow(1.085, i) - 1.0, log((i + 0.2) * 5.0) / 10.0 + 1.0);
		color.x /= length(color);
		color.y /= length(color);
		//color.y *= 0.0;  // makes it look like a black hole.
		color.y *= 0.5;
		gl_FragColor = vec4(color.x, 0.0, color.y, 1.0);
	}
}