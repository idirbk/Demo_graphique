#version 330
uniform float dt;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform int hauteur;
uniform int largeur;
in  vec2 vsoTexCoord;
out vec4 fragColor;

void main(void) {

  int y = int(vsoTexCoord.y * hauteur) ;
  int x = int(vsoTexCoord.x * largeur) ;

  float cx = ((x / 50) * 50 +25.0 )/largeur;
  float cy = ((y / 50) *50 +25.0 )/hauteur;

float d = distance(vsoTexCoord , vec2(cx,cy));
 if(d > dt * 0.05)
 {
   fragColor = texture(tex0, vsoTexCoord);
 }else{
    fragColor = texture(tex1, vsoTexCoord);
 }


}
