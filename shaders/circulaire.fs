#version 330
uniform float dt;
uniform sampler2D tex0;
uniform sampler2D tex1;
in  vec2 vsoTexCoord;
out vec4 fragColor;

void main(void) {

  


  vec2 c  = vec2(0.5);
  vec2 p = vsoTexCoord;
  vec2 v = p - c;
  float theta = atan(v.y , v.x);
if(int(abs(theta * 57.2958))%10 < 10*dt)
{
   fragColor = texture(tex1, vsoTexCoord);
}else{
   fragColor = texture(tex0, vsoTexCoord);
}



}
