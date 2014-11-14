// fragment shader
#version 150

// this is how we receive the texture
uniform sampler2DRect mainTex;
uniform sampler2DRect bumpTex;
uniform float bumpAmount;

in vec2 uvmain;
in vec2 uvbump;
uniform float scroll1;
uniform float scroll2;
uniform float scroll3;

out vec4 outputColor;



void main(){
    // decode bump map
    vec4 bumpTex = 2.0 * texture(bumpTex, uvmain) - 1.0f;

    
    // this creates the plasma stuff - its basically three difference cloud textures superimposed
    // I've hardcoded a bunch of values that should be uniforms.
    
    // this hacks the UV wrapping - because its not a POW2 texture the OPENGL won't do it for you
    vec2 uv1 = vec2(fract((uvmain.x + scroll1)/1280.0)*1280.0,uvmain.y);
    vec2 uv2 = vec2(fract((uvmain.x + scroll2)/1280.0)*1280.0,uvmain.y);
    vec2 uv3 = vec2(fract((uvmain.x + scroll3)/1280.0)*1280.0,uvmain.y);
    
    
    // the bump map distorts the texture reads
    // there are three textures that are compressed into the RGB channels of one texture
    vec4 col;
    float intensity;
    intensity = texture(mainTex, uv1 + bumpTex.xy * bumpAmount).r;
    intensity += texture(mainTex, uv2 + bumpTex.xy * bumpAmount).g;
    intensity += texture(mainTex, uv3 + bumpTex.xy * bumpAmount).b;

    // replace this with a color ramp texture and use intensity off that
    col.b = intensity;
    col.g = intensity*0.5f;
    col.r = 0.0f;
    
    // this adds the 'shine' back to the ice faking lighting
    col += clamp(pow(bumpTex.x,2.5),0,1)*0.4f;
    col.a = 1.0f;
    
    
//    vec2 newUV = uv + bumpTex.xy * bumpAmount;
 //   outputColor = texture(mainTex,newUV);  //vec4(0.0,uv.x/1280,0.0,1.0); //
   
    outputColor = col;
    
}