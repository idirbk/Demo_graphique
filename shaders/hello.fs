#version 330

in vec4 mvpos;
in vec3 N;

out vec4 fragColor;

uniform int nblum;
uniform vec4 scolor;
uniform vec4 lcolor[10];
uniform vec4 lumpos[10];
uniform sampler2D tex;


in vec2 texCoors;

void main() {
     fragColor = vec4(0,0,0,0);
     for(int i = 0 ; i < nblum ; ++i){
          vec4 ambient = 0.2f * lcolor[i] * scolor * texture(tex,texCoors); /* lacolor, sacolor */
          vec3 Ld = normalize(mvpos.xyz - lumpos[i].xyz);
          float ild = clamp(dot(normalize(N), -normalize(Ld)), 0, 1);
          vec4 diffus = (ild * lcolor[i]) * scolor* texture(tex,texCoors); /* ldcolor, sdcolor */
          vec3 R = reflect(Ld, N);
          vec3 Vue = vec3(0, 0, -1);
          float ils = pow(clamp(dot(R, -Vue), 0, 1),10);   
           vec4 spec = ils * lcolor[i]; /* sscolor */
          fragColor +=  diffus + ambient+spec;
     }
}
