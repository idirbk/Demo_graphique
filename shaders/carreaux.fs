#version 330
uniform float dt;
uniform sampler2D tex0;
uniform sampler2D tex1;
uniform int hauteur;
uniform int largeur;
in  vec2 vsoTexCoord;
out vec4 fragColor;

void main(void) {
 if(int(vsoTexCoord.y * hauteur) %30 < int((1-dt)*29)  && int(vsoTexCoord.x * largeur) %30 < int((1-dt)*29))
 {
  
   fragColor = texture(tex0, vsoTexCoord);
   
 }else{
  
       fragColor = texture(tex1, vsoTexCoord);
    
  }

}
