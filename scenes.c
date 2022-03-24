#include "scenes.h"

#include <GL4D/gl4du.h>

void scene1(GLfloat a,GLfloat dt,GLuint _pId , GLint _cube ,GLint _quadId, GLuint *_texId,GLfloat _hauteurs) {
  GLuint lumposId = glGetUniformLocation(_pId, "lumpos");
  GLuint texloc = glGetUniformLocation(_pId, "tex");
  GLuint scolorloc = glGetUniformLocation(_pId, "scolor");
  GLuint lcolorloc = glGetUniformLocation(_pId, "lcolor");
  GLuint nblumloc   = glGetUniformLocation(_pId, "nblum");
  
  static GLfloat x ,y,z,inc = 0.0f;
  GLfloat blanc[] = {1.0, 1.0, 1.0, 1.0f},myColors[] = {gl4dmURand(),gl4dmURand(), gl4dmURand(), 1.0f,gl4dmURand(),gl4dmURand(), gl4dmURand(), 1.0f , 0.5,0.5,0.5,1};
  GLuint nbLum = 3;
  GLfloat lumpos0[]= {0,2,-9.5,0,0,2,-9.5,0,0,10,0} ,   lumpos[12] , *mat;
  lumpos0[0] = 4.0f * sin(inc) - 10 * sin(a);
  lumpos0[1]  = 4.0f * sin(-inc) - 10*cos(a);

  lumpos0[4] = 4.0f * cos(inc)- 10 * sin(a);
  lumpos0[5]  = 4.0f * cos(-inc) - 10*cos(a);
  inc += 4*dt;
  gl4duBindMatrix("view");
  mat = (GLfloat *)gl4duGetMatrixData();
  MMAT4XVEC4(lumpos, mat, lumpos0);
  MMAT4XVEC4(lumpos+4, mat, lumpos0+4);
  MMAT4XVEC4(lumpos+8, mat, lumpos0+8);

  gl4duBindMatrix("mod");
  glUseProgram(_pId);

  // l'arière plan
  gl4duLoadIdentityf();
  gl4duTranslatef(0,0,-1);
  gl4duScalef(5.5,5.5,1);
  gl4duSendMatrices();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId[1]);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_quadId);

  /* pour le D */

  x = MIN(-4,-7.5+a);
  y = 2;
  z = _hauteurs / 4 ;
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duScalef(0.2,1, 0.2);
  gl4duSendMatrices();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId[0]);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(glGetUniformLocation(_pId, "lcolor"), nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.8,0.8,0);
  gl4duScalef(0.6,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(1.4,0,0);
  gl4duScalef(0.2,0.8, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.8,-0.8,0);
  gl4duScalef(0.6,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  /* pour le E */
  
  x = -2;
  y = MAX(2,5.5-a);
  z = -_hauteurs / 4;
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duScalef(0.2,1, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, 1, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, 1, myColors);
  gl4dgDraw(_cube);
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.7,0.8,0);
  gl4duScalef(0.5,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.7,0,0);
  gl4duScalef(0.5,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.7,-0.8,0);
  gl4duScalef(0.5,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  /* pour le M */

  x = -0.3f;
  y = MAX(2,5.5-a);
  z = _hauteurs / 4;
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duScalef(0.2,1, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.55,0,0);
  gl4duRotatef(30, 0, 0, 1);
  gl4duScalef(0.2,1.04, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(1.6,0,0);
  gl4duRotatef(-30, 0, 0, 1);
  gl4duScalef(0.2,1.04, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(2.15,0,0);
  gl4duScalef(0.2,1, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(1.07,-0.8,0);
  gl4duScalef(0.17,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  /* pour le O */
  x = MAX(2.5,6-a);
  y = 2;
  z =  -_hauteurs / 4;
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duScalef(0.2,0.8, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.6,0.8,0);
  gl4duScalef(0.6,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.6,-0.8,0);
  gl4duScalef(0.6,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(1.2,0,0);
  gl4duScalef(0.2,0.8, 0.2);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  /* pour le I */

  x =MIN(-5.5+2*a,1.5);
  y = -3;
  z = _hauteurs / 4;
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duScalef(0.1,0.4, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0,-0.4,0);
  gl4duScalef(0.3,0.1, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0,0.4,0);
  gl4duScalef(0.3,0.1, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  /* pour le petit D */

  x = MIN(-5+2*a,2);
  y = -3;
  z = _hauteurs / 4;
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duScalef(0.1,0.5, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.4,0.4,0);
  gl4duScalef(0.3,0.1, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.7,0,0);
  gl4duScalef(0.1,0.4, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.4,-0.4,0);
  gl4duScalef(0.3,0.1, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  /* pour le dexième I */
  x = MIN(-3.8+2*a,3.2);
  y = -3;
  z = _hauteurs / 4;
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duScalef(0.1,0.4, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0,-0.4,0);
  gl4duScalef(0.3,0.1, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0,0.4,0);
  gl4duScalef(0.3,0.1, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  /* pour le R */
  x =MIN(-3.25+2*a,3.75);
  y = -3;
  z = _hauteurs / 4;
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duScalef(0.1,0.5, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.25,0.4,0);
  gl4duScalef(0.20,0.1, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.45,0.20,0);
  gl4duScalef(0.1,0.20, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.25,0,0);
  gl4duScalef(0.20,0.1, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.49,-0.2,0);
  gl4duRotatef(30, 0,0, 1);
  gl4duScalef(0.1,0.30, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duTranslatef(0.65,-0.46,0);
  gl4duScalef(0.085,0.05, 0.1);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId,nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  glBindTexture(GL_TEXTURE_2D, 0);
  glUseProgram(0);

}


void scene2(GLfloat a, GLfloat dt ,GLint _pId ,GLint _cubeId,GLint _sphereId,GLuint * _texId, GLfloat _son )
{
  static GLfloat time =  0.0;
  time += dt;
  GLuint lumposloc = glGetUniformLocation(_pId, "lumpos");
  GLuint texloc = glGetUniformLocation(_pId, "tex");
  GLuint scolorloc = glGetUniformLocation(_pId, "scolor");
  GLuint lcolorloc = glGetUniformLocation(_pId, "lcolor");
  GLuint nblumloc   = glGetUniformLocation(_pId, "nblum");

  GLuint nblum = 7;
  static GLfloat x = 0.0f;
  GLfloat  blanc[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat    lumpos[28] , *mat,lumpos0 [] = {0,0,-16.0f,0,
                                               0,0,-16.0f,0,
                                               0,0,-16.0f,0,
                                               0,0,-16.0f,0,
                                               0,0,-16.0f,0,
                                               0,0,-16.0f,0,
                                               0,0,-16.0f,0,};
  GLfloat lumcol [] = {0,1,0,1,
                       1,0,0,1,
                       0,0,1,1,
                       1,0,1,1,
                       0,1,1,1,
                       0,1,1,1,
                       1,1,0,1,
                       1,0.5,0.5,1,
                       };

      lumpos0[0] = 8.0f * sin(x);
      lumpos0[5] = 4.0f * sin(x);
      lumpos0[8] = 6.0f * sin(x);
      lumpos0[9] = 4.0f * sin(x);
      lumpos0[12] = -6.0f * sin(x);
      lumpos0[13] = -4.0f * sin(x);
      lumpos0[16] = -6.0f * sin(x);
      lumpos0[17] = 4.0f * sin(x);
      lumpos0[20] = 6.0f * sin(x);
      lumpos0[21] = -4.0f * sin(x);
      lumpos0[24] = -8.0f * sin(x);
      
  x += 4*dt;
  gl4duBindMatrix("view");  
  mat = (GLfloat *)gl4duGetMatrixData();
  for(int i = 0 ; i < nblum ; ++i)
  {
    MMAT4XVEC4(lumpos+4*i, mat, lumpos0+4*i);
  } 
    
  glUseProgram(_pId);
  gl4duBindMatrix("mod");

  /*dessin des murs*/

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId[1]);

  // le mure de face
  gl4duLoadIdentityf();
  gl4duTranslatef(0,0,-3);
  gl4duScalef(7,3,0.5);
  gl4duSendMatrices();
  glUniform1i(nblumloc, nblum);
  glUniform4fv(lumposloc, nblum, lumpos);
  glUniform4fv(lcolorloc, nblum, lumcol);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  gl4dgDraw(_cubeId);

  //le sol
  gl4duLoadIdentityf();
  gl4duTranslatef(0,-3, 0);
  gl4duScalef( 7,0.2,2);
  glUseProgram(_pId);
  gl4duSendMatrices();
  glUniform1i(nblumloc, nblum);
  glUniform4fv(lumposloc, nblum, lumpos);
  glUniform4fv(lcolorloc, nblum, lumcol);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  gl4dgDraw(_cubeId);

  //le mur de gauche
  gl4duLoadIdentityf();
  gl4duTranslatef(-7,0, 0);
  gl4duScalef(0.2, 3,2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,  nblum);
  glUniform4fv(lumposloc, nblum, lumpos);
  glUniform4fv(lcolorloc, nblum, lumcol);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  gl4dgDraw(_cubeId);

  //le murs de droite
  gl4duLoadIdentityf();
  gl4duTranslatef(7,0, 0);
  gl4duScalef(0.2, 3,2);
  gl4duSendMatrices();
  glUniform1i(nblumloc, nblum);
  glUniform4fv(lumposloc, nblum, lumpos);
  glUniform4fv(lcolorloc, nblum, lumcol);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  gl4dgDraw(_cubeId);

  /* dessin de la boule de disco */
  //fprintf(stderr,"time == %f",time);
  gl4duLoadIdentityf();
  gl4duTranslatef(0, 0, -3);
  gl4duScalef((time < 65) ? 1.5 : 1.5*_son/10,(time < 65) ? 1.5 :1.5*_son/10,(time < 65) ? 1.5 :1.5*_son/10);
  gl4duRotatef(a, 0, 1, 0);
  gl4duSendMatrices();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId[0]);
  glUniform1i(nblumloc, nblum);
  glUniform4fv(lumposloc, nblum, lumpos);
  glUniform4fv(lcolorloc, nblum, lumcol);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  gl4dgDraw(_sphereId);
  if(time > 65)
  {
    for(int i = 0 ; i < 10 ; ++ i)
    { gl4duLoadIdentityf();
      gl4duTranslatef(-2.5*sin(((time-63 < 12) ? 2*(M_PI/10) : a)*(i+1)),-2.5*cos(((time-63 < 12) ? 2*(M_PI/10) : a)*(i+1)),-2);
      gl4duScalef(0.2*_son/5, 0.2*_son/5,0.2*_son/5);
      gl4duRotatef(a, 1, 1, 1);
      gl4duSendMatrices();
      glUniform1i(nblumloc, nblum);
      glUniform4fv(lumposloc, nblum, lumpos);
      glUniform4fv(lcolorloc, nblum, lumcol);
      glUniform1i(texloc, 0);
      glUniform4fv(scolorloc, 1, blanc);
      gl4dgDraw(_sphereId);
    }
  }

  if(time > 65 && time-63 < 12)
  {
    for(int i = 1 ; i < 10 ; ++i)
    {
      gl4duLoadIdentityf();
      gl4duTranslatef(sin(time * (i+1) ),cos(time * (i+1)), (time-65) +(i+1));
      gl4duScalef(0.2,0.2,0.2);
      gl4duRotatef(a, 0, 1, 0);
      gl4duSendMatrices();
      glUniform1i(nblumloc, nblum);
      glUniform4fv(lumposloc, nblum, lumpos);
      glUniform4fv(lcolorloc, nblum, lumcol);
      glUniform1i(texloc, 0);
      glUniform4fv(scolorloc, 1, blanc);
      gl4dgDraw(_sphereId);
    }
  }


  
    
  
 
    
  glBindTexture(GL_TEXTURE_2D, 0);
  glUseProgram(0);
}

void scene3( GLfloat dt, GLuint _pId, GLint _cubeId, GLint _sphereId, GLint _cylindreId, GLuint * _texId)
{
  GLuint lumposId = glGetUniformLocation(_pId, "lumpos");
  GLuint texloc = glGetUniformLocation(_pId, "tex");
  GLuint scolorloc = glGetUniformLocation(_pId, "scolor");
  GLuint lcolorloc = glGetUniformLocation(_pId, "lcolor");
  GLuint nblumloc   = glGetUniformLocation(_pId, "nblum");
  
  static GLfloat x  = 0.0f;
  x+=dt;
  GLfloat blanc[] = {0.7, 0.7, 0.7, 1.0f} , gris [] = {1,1,1,1.0f};
  GLuint nbLum = 1;
  GLfloat lumpos0[]= {0,8,-5,0,} ,   lumpos[4] , *mat;
  x+= dt;
  static GLfloat x1 = -2, x2 = -2 , y1 = 2, y2 =0,xa2 = 0 ,ya2 = 0 ,angle[2] ={-0.05,0} ,sumangle[2] = {0,0};
  xa2=(x2-x1)*cos(angle[0] + angle[1])-(y2-y1)*sin(angle[0] + angle[1]) + x1;
  ya2=(x2-x1)*sin(angle[0] + angle[1])+(y2-y1)*cos(angle[0] + angle[1]) + y1;
  x2 = xa2;
  y2 = ya2;
  if(angle[0] != 0 && y2 > 1.5 )
    angle[0] = 0.05;
  if(angle[0] != 0 && x2 > -2 )
  {
      angle[0] = 0;
      angle[1] = 0.05;
      sumangle[0] = 0; 
      x1 = 4;
      y1 = 2;
      x2 = 4;
      y2 = 0;
  }
   if(angle[1] != 0 && y2 > 1.5 )
    angle[1] = -0.05;
  if(angle[1] != 0 && x2 < 4 )
  {
    angle[1] = 0;
      angle[0] = -0.05;
      sumangle[1] = 0;
      x1 = -2;
      y1 = 2;
      x2 = -2;
      y2 = 0;
  }
    
    if(angle[1] != 0)
    {
      sumangle[1] += angle[1];
    }else{
      sumangle[0] += angle[0];
    }
  
  
  gl4duBindMatrix("view");
  mat = (GLfloat *)gl4duGetMatrixData();
  MMAT4XVEC4(lumpos, mat, lumpos0);
  glUseProgram(_pId);
  gl4duBindMatrix("mod");
  



  /* les sphere */ 

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId[0]);

  gl4duLoadIdentityf();
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_sphereId);

  gl4duLoadIdentityf();
  gl4duTranslatef((angle[0] != 0) ? xa2 : -2,(angle[0] != 0) ? ya2 : 0,0);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_sphereId);

  gl4duLoadIdentityf();
  gl4duTranslatef(2,0,0);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_sphereId);

  gl4duLoadIdentityf();
  gl4duTranslatef((angle[1] != 0) ? xa2 : 4,(angle[1] != 0) ? ya2 : 0,0);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_sphereId);

  /* le cadre du pondule */
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId[2]);

  gl4duLoadIdentityf();
  gl4duTranslatef(0.5,-2,0);
  gl4duScalef(6,0.2,4);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cubeId);

  gl4duLoadIdentityf();
  gl4duTranslatef(-5.25,1,3.8);
  gl4duScalef(0.2,3,0.2);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cubeId);

  gl4duLoadIdentityf();
  gl4duTranslatef(6.25,1,3.8);
  gl4duScalef(0.2,3,0.2);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cubeId);

  gl4duLoadIdentityf();
  gl4duTranslatef(6.25,1,-3.8);
  gl4duScalef(0.2,3,0.2);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cubeId);

  gl4duLoadIdentityf();
  gl4duTranslatef(-5.25,1,-3.8);
  gl4duScalef(0.2,3,0.2);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cubeId);

  gl4duLoadIdentityf();
  gl4duTranslatef(0.5,4,3.9);
  gl4duScalef(6,0.2,0.2);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cubeId);

  gl4duLoadIdentityf();
  gl4duTranslatef(0.5,4,-3.7);
  gl4duScalef(6,0.2,0.2);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cubeId);

  /* les cordes */

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId[1]);

  gl4duLoadIdentityf();
  gl4duTranslatef(0,2.2,-2);
  gl4duRotatef(-45, 1, 0, 0);
  gl4duScalef(0.05,2,0.05);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cylindreId);

  gl4duLoadIdentityf();
  gl4duTranslatef(0,2.2,2);
  gl4duRotatef(45, 1, 0, 0);
  gl4duScalef(0.05,2.5,0.05);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cylindreId);
  
  // corde 2
  gl4duLoadIdentityf();
  gl4duTranslatef(2,2.2,-2);
  gl4duRotatef(-45, 1, 0, 0);
  gl4duScalef(0.05,2,0.05);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cylindreId);

  gl4duLoadIdentityf();
  gl4duTranslatef(2,2.2,2);
  gl4duRotatef(45, 1, 0, 0);
  gl4duScalef(0.05,2.5,0.05);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cylindreId);
  
    // corde 3
  gl4duLoadIdentityf();
  gl4duTranslatef(4+sumangle[1]*0.6,2.3+sumangle[1]/2,-2);
  gl4duRotatef(sumangle[1]*30, 0, 0, 1);
  gl4duRotatef(-45-sumangle[1]*7 , 1, 0, 0);
  gl4duScalef(0.05,2.3,0.05);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cylindreId);

  gl4duLoadIdentityf();
  gl4duTranslatef(4+sumangle[1],2.3+sumangle[1]/2,2);
  gl4duRotatef(sumangle[1]*30, 0, 0, 1);
  gl4duRotatef(45+sumangle[1]*7 , 1, 0, 0);
  gl4duScalef(0.05,2.3,0.05);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cylindreId);
  
    // corde 4
  
   gl4duLoadIdentityf();
  gl4duTranslatef(-2+sumangle[0]*0.6,2.3-sumangle[0]/2,-2);
  gl4duRotatef(sumangle[0]*30, 0, 0, 1);
  gl4duRotatef(-45+sumangle[0]*7 , 1, 0, 0);
  gl4duScalef(0.05,2.3,0.05);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cylindreId);

  gl4duLoadIdentityf();
  gl4duTranslatef(-2+sumangle[0],2.3-sumangle[0]/2,2);
  gl4duRotatef(sumangle[0]*30, 0, 0, 1);
  gl4duRotatef(45-sumangle[0]*7 , 1, 0, 0);
  gl4duScalef(0.05,2.3,0.05);
  gl4duSendMatrices();
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, gris);
  glUniform4fv(lcolorloc, nbLum, blanc);
  gl4dgDraw(_cylindreId);


  glBindTexture(GL_TEXTURE_2D, 0);
  glUseProgram(0);
}
void scene4(GLfloat a,GLfloat dt,GLuint _pId , GLint _cube , GLint _quadId,GLuint *_texId,GLfloat _hauteurs)
{
    GLuint lumposId = glGetUniformLocation(_pId, "lumpos");
  GLuint texloc = glGetUniformLocation(_pId, "tex");
  GLuint scolorloc = glGetUniformLocation(_pId, "scolor");
  GLuint lcolorloc = glGetUniformLocation(_pId, "lcolor");
  GLuint nblumloc   = glGetUniformLocation(_pId, "nblum");
  
  static GLfloat x ,y,z,r,inc = 0.0f;
  GLfloat blanc[] = {1.0, 1.0, 1.0, 1.0f},myColors[] = {gl4dmURand(),gl4dmURand(), gl4dmURand(), 1.0f,gl4dmURand(),gl4dmURand(), gl4dmURand(), 1.0f , 0.5,0.5,0.5,1};
  GLuint nbLum = 3;
  GLfloat lumpos0[]= {0,2,-9.5,0,0,2,-9.5,0,0,10,0} ,   lumpos[12] , *mat;
  lumpos0[0] = 4.0f * sin(inc) - 10 * cos(a);
  lumpos0[1]  = 4.0f * sin(-inc) - 10*sin(a);

  lumpos0[4] = 4.0f * cos(inc)- 10 * cos(a);
  lumpos0[5]  = 4.0f * cos(-inc) - 10*sin(a);
  inc += 4*dt;
  gl4duBindMatrix("view");
  mat = (GLfloat *)gl4duGetMatrixData();
  MMAT4XVEC4(lumpos, mat, lumpos0);
  MMAT4XVEC4(lumpos+4, mat, lumpos0+4);
  MMAT4XVEC4(lumpos+8, mat, lumpos0+8);

  gl4duBindMatrix("mod");
  glUseProgram(_pId);

  // l'arière plan
  gl4duLoadIdentityf();
  gl4duTranslatef(0,0,-1);
  gl4duScalef(5.5,5.5,1);
  gl4duSendMatrices();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId[1]);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_quadId);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId[0]);
  
  // le T

  x = -2;
  y = MIN(0,84-5.5+a)+2;
  z = _hauteurs / 4 ;
  r = MAX(0,(84+5.5-a)*100);
  gl4duLoadIdentityf();
  
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duTranslatef(0,0.8,0);
  gl4duScalef(0.6,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duScalef(0.2,1, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(glGetUniformLocation(_pId, "lcolor"), nbLum, myColors);
  gl4dgDraw(_cube);

  // le H

  x = -0.5;
  y = MAX(0,84+5.5-a)+2;
  z = _hauteurs / 4 ;
  r = MAX(0,(84+5.5-a)*100);
  gl4duLoadIdentityf();
  

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duTranslatef(-0.5,0,0);
  gl4duScalef(0.2,1, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(glGetUniformLocation(_pId, "lcolor"), nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duTranslatef(0.5,0,0);
  gl4duScalef(0.2,1, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(glGetUniformLocation(_pId, "lcolor"), nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duScalef(0.6,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);
  
  // LE E
  
  x = 0.7;
  y = MIN(0,84+-5.5+a)+2;
  z = _hauteurs / 4 ;
  r = MAX(0,(84+5.5-a)*100);
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duScalef(0.2,1, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, 1, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, 1, myColors);
  gl4dgDraw(_cube);
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duTranslatef(0.7,0.8,0);
  gl4duScalef(0.5,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duTranslatef(0.7,0,0);
  gl4duScalef(0.5,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duTranslatef(0.7,-0.8,0);
  gl4duScalef(0.5,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  // LE E de END
  
  x = MAX(-1,84+4.5-a);
  y = -1;
  z = _hauteurs / 4 ;
  r = MAX(0,(84+5.5-a)*100);
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duScalef(0.2,1, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, 1, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, 1, myColors);
  gl4dgDraw(_cube);
  
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duTranslatef(0.7,0.8,0);
  gl4duScalef(0.5,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duTranslatef(0.7,0,0);
  gl4duScalef(0.5,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duTranslatef(0.7,-0.8,0);
  gl4duScalef(0.5,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

 // POUR LE N
  x = MAX(0.7,84+6.2-a);
  y = -1;
  z = _hauteurs / 4;
  r = MAX(0,(84+5.5-a)*100);
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duScalef(0.2,1, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duTranslatef(1.1,0,0);
  gl4duScalef(0.2,1, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r, 0, 0, 1);
  gl4duTranslatef(0.55,0,0);
  gl4duRotatef(30, 0, 0, 1);
  gl4duScalef(0.2,1.04, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);


  /* pour le D */

  x =  MAX(2.6,84+8.1-a); //MIN(-4,-7.5+a);
  y = -1;
  z = _hauteurs / 4 ;
  r = MAX(0,(84+5.5-a)*100);
  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r,0, 0, 1);
  gl4duScalef(0.2,1, 0.2);
  gl4duSendMatrices();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _texId[0]);
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(glGetUniformLocation(_pId, "lcolor"), nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r,0, 0, 1);
  gl4duTranslatef(0.8,0.8,0);
  gl4duScalef(0.6,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r,0, 0, 1);
  gl4duTranslatef(1.4,0,0);
  gl4duScalef(0.2,0.8, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);

  gl4duLoadIdentityf();
  gl4duTranslatef(x,y,z);
  gl4duRotatef(r,0, 0, 1);
  gl4duTranslatef(0.8,-0.8,0);
  gl4duScalef(0.6,0.2, 0.2);
  gl4duSendMatrices();
  glUniform1i(nblumloc,nbLum);
  glUniform4fv(lumposId, nbLum, lumpos);
  glUniform1i(texloc, 0);
  glUniform4fv(scolorloc, 1, blanc);
  glUniform4fv(lcolorloc, nbLum, myColors);
  gl4dgDraw(_cube);
  
  

  glBindTexture(GL_TEXTURE_2D, 0);
  glUseProgram(0);

}