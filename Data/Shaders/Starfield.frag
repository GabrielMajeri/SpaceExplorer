#version 110

// Values: 0.98...0.995
// Higher values = less stars
uniform float starThreshold;
uniform float numSeed;

float rand(vec2 seed)
{
    float dt = dot(seed.xy, vec2(numSeed, 78.233));
    float sn = mod(dt, 3.1415);

    return fract(sin(sn) * 43758.5453);
}

#define starTwinkle (1.0 - starThreshold)

void main()
{
	// Get some random noise
	float rd = rand(gl_FragCoord.xy);

	// Set the color
	vec3 color = vec3(0, 0, 0);

	// If this pixel will become a star
	if(rd > starThreshold)
	{
		float val = pow((rd - starThreshold) / starTwinkle, 6.0);
		color = vec3(val);

		gl_FragColor = vec4(color, 1);
	}
	else
		gl_FragColor = vec4(color, 0);
}
