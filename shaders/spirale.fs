#version 330

in vec2 vsoTexCoord;
out vec4 maSortie;



uniform int modulo;
uniform int increment;
uniform float hauteurs;


void main() {
   float d = distance(vsoTexCoord,vec2(0.5,0.5));
  if(d > hauteurs/2)
  {
    maSortie =vec4(0.5,0.5,0.5,1)*(d+0.2);
    return;
  }
 
  if(((int(d*100)+increment)%modulo) < 1 )
  {
    maSortie =vec4(0,0,0,1);
    return;
  }
  maSortie = vec4(1,1,1,1) *(1- d*2);

}
