#version 330
uniform float dt;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform int width;
in  vec2 vsoTexCoord;
out vec4 fragColor;

void main(void) {
 if(int(vsoTexCoord.x * width) %30 < int((1-dt)*29))
 {
    fragColor = texture(tex0, vsoTexCoord);
 }else{
    fragColor = texture(tex1, vsoTexCoord);
  }

}
