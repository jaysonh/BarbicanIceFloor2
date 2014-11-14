// fragment shader
#version 150

// this is how we receive the texture
uniform sampler2DRect tex0;
uniform sampler2DRect tex1;
uniform float cutoff;
uniform float alpha;
in vec2 varyingtexcoord;
out vec4 outputColor;

void main(){
   
    //outputColor = vec4(1.0,1.0,1.0,1.0);
    vec4 texel0 = texture(tex0,varyingtexcoord);
    vec4 texel1 = texture(tex1,varyingtexcoord);

    // basically this is an alpha test algorithm
    if (texel1.r<(1.0-cutoff)){
        discard;
    }else
    {
        outputColor = texel0 * alpha;
    }
    
}
