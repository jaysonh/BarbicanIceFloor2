#version 150


// these are for the programmable pipeline system and are passed in
// by default from OpenFrameworks
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 textureMatrix;
uniform mat4 modelViewProjectionMatrix;

in vec4 position;
in vec4 color;
in vec4 normal;
in vec2 texcoord;
// this is the end of the default functionality

// this is something we're creating for this shader
out vec2 uvmain;
out vec2 uvbump;
//out vec2 uvbump;

// this is coming from our C++ code
//uniform float mouseX;

void main()
{
    vec4 pos = modelViewProjectionMatrix * position;
    // here we move the texture coordinates
    uvmain = vec2(texcoord.x, texcoord.y);
    uvbump = vec2(texcoord.x, texcoord.y);
    
    // send the vertices to the fragment shader
    gl_Position = pos;
}


