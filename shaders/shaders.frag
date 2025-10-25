#version 450 core

//The texture being used.
uniform sampler2D image;

//The mouse position.
uniform vec2 mousePos;

//The current accumulated time.
uniform float iTime;

//The clip-space positions [-0.5, 0.5].
in vec2 pos;

//The clip-space texture coordinates [0.0, 1.0].
in vec4 texCoord;

void mainImage(out vec4 fragColor, in vec2 fragCoord){
	
	//vectors may have the coordinates:
	//x, y, z, and w for positions.
	//s, t, p, and q for texture positions.
	//r, g, b, and a for color.
	//Though all of these can be worked with for the vectors,
	//it is just best to use them this way for clarity.
	//The vec2 variable name uv is best used for positions.
	//The vec2 variable name st is best used for texture positions.
	vec2 uv = pos;
	vec2 st = texCoord.st;

	//Initializing a variable for our final color value.
	vec4 color = vec4(0.0);

	//Dimming light
	float len = 1.0 - length(uv);
	len *= abs(sin(iTime));
	color = vec4(vec3(len), 1.0);

	//We may retrieve the color of the input texture ("image" here) using the 'texture' keyword.
	color += texture(image, st);

	//Spotlight
	//Our mouse position
	vec2 mouse = mousePos;
	//Distance from our mouse to a uv position.
	float dist = distance(mouse, uv);
	//To use for the alpha-value for our color variable.
	float c0 = length(abs(dist)) + 0.2;

	//Cut this line out for the light to trail off.
	c0 = step(0.5, c0);

	//For our final rgb value for our spotlight.
	vec3 cRGB = vec3(0.0);

	//Setting the alpha-value as c0,
	//any value of c0 above 0.0 makes the texture in this case transparent.
	color.a = c0;
	//Adding to the color to show off the next part as well.
	color += vec4(cRGB, c0);

	//Scanlines
	//If the model view resolution is divisible by 3 the scan value will be 0.
	float scan = mod(fragCoord.y, 3.0);
	//Keeps the color light instead of dimming the texture.
	scan = smoothstep(0.5, 1.0, scan);
	//Adding the scan value to the final alpha-value.
	color.a += scan;

	fragColor = color;
}
void main(){

	mainImage(gl_FragColor, gl_FragCoord.xy);
}
