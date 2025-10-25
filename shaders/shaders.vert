#version 450 compatibility

//The resolution of the screen (640, 360) in our case.
uniform vec2 iResolution;

//The out keyword will send these variables to the fragment shader.
out vec2 pos;
out vec4 texCoord;

void main() {
	
	//Gives the normalized x,y-axes of our texture (This is called clip-space).
	texCoord = gl_TextureMatrix[0] * gl_MultiTexCoord0;

	//Gives the clip-space coordinates for our vertices.
	vec4 vertex = gl_ModelViewProjectionMatrix * gl_Vertex;
	//Gives us the positions we will use in our fragment shader.
	pos = gl_Vertex.xy / iResolution.xy - 0.5;

	gl_Position = vertex;
	gl_TexCoord[0] = texCoord;
	gl_FrontColor = gl_Color;
}
