#version 330

in vec2 vsoTexCoord;
out vec4 maSortie;



uniform int nb_sites;
uniform vec2 coords[256];
uniform vec3 colors[256];
uniform float hauteur;

float random (vec2 st) {
    return fract(sin(dot(st.xy,
                         vec2(12.9898,78.233)))*
        43758.5453123);
}

void main() {
  
   float dmin = distance(vsoTexCoord, coords[0]);
  float dmin2;

  int imin = 0;
  int imin2 = 0;
  for(int i = 1; i < nb_sites; ++i) {
    float d = distance(vsoTexCoord, coords[i]);
    if(d <= dmin) {
      imin2 = imin;
      dmin2 = dmin;
      imin = i;
      dmin = d;
    }
  }
  
  if( hauteur/2 < dmin)
  {
    maSortie =vec4(1,1,1,1);
        return;
  }
   if((int(dmin*100)%3) == 0 )
  {
    maSortie = vec4(0,0,0,1);//vec4(colors[(imin+1)%nb_sites],1);
    return;
  }
  maSortie = vec4(colors[imin],1) *(1 - (dmin /((dmin+dmin2) / 2)))*2;

}
