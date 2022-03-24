/*!\file animations.c
 *
 * \brief Votre espace de liberté : c'est ici que vous pouvez ajouter
 * vos fonctions de transition et d'animation avant de les faire
 * référencées dans le tableau _animations du fichier \ref window.c
 *
 * Des squelettes d'animations et de transitions sont fournis pour
 * comprendre le fonctionnement de la bibliothèque. En bonus des
 * exemples dont un fondu en GLSL.
 *
 * \author Farès BELHADJ, amsi@ai.univ-paris8.fr
 * \date May 05, 2014
 */

#include "audioHelper.h"
#include "scenes.h"
#include "voronoi.h"
#include <GL4D/gl4dg.h>
#include <GL4D/gl4dh.h>
#include <GL4D/gl4dhAnimeManager.h>
#include <GL4D/gl4dm.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4du.h>
#include <SDL_image.h>
#include <assert.h>
#include <stdlib.h>

/*!\brief identifiant de la géométrie QUAD GL4Dummies */
static GLint _quadId = 0;
static GLint _cubeId = 0;
static GLint _sphereId = 0;
static GLint _cylindreId = 0;

void transition_rideau(void (*a0)(int), void (*a1)(int), Uint32 t, Uint32 et,
                       int state) {
  /* INITIALISEZ VOS VARIABLES */
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch (state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for (i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/rideau.fs",
                             NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if (tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if (a0)
      a0(state);
    if (a1)
      a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                          &tId);
    /* JOUER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tex[0], 0);
    if (a0)
      a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tex[1], 0);
    if (a1)
      a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tId, 0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if (et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "width"), gl4dpGetWidth());
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}
void transition_rideau2(void (*a0)(int), void (*a1)(int), Uint32 t, Uint32 et,
                        int state) {
  /* INITIALISEZ VOS VARIABLES */
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch (state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for (i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/rideau2.fs",
                             NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if (tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if (a0)
      a0(state);
    if (a1)
      a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                          &tId);
    /* JOUER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tex[0], 0);
    if (a0)
      a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tex[1], 0);
    if (a1)
      a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tId, 0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if (et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "hauteur"), gl4dpGetHeight());
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}
void transition_careaux(void (*a0)(int), void (*a1)(int), Uint32 t, Uint32 et,
                        int state) {
  /* INITIALISEZ VOS VARIABLES */
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch (state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for (i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/carreaux.fs",
                             NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if (tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if (a0)
      a0(state);
    if (a1)
      a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                          &tId);
    /* JOUER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tex[0], 0);
    if (a0)
      a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tex[1], 0);
    if (a1)
      a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tId, 0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if (et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "hauteur"), gl4dpGetHeight());
    glUniform1i(glGetUniformLocation(pId, "largeur"), gl4dpGetWidth());
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}

void transition_cercles(void (*a0)(int), void (*a1)(int), Uint32 t, Uint32 et,
                        int state) {
  /* INITIALISEZ VOS VARIABLES */
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch (state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for (i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/cercles.fs",
                             NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if (tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if (a0)
      a0(state);
    if (a1)
      a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                          &tId);
    /* JOUER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tex[0], 0);
    if (a0)
      a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tex[1], 0);
    if (a1)
      a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tId, 0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if (et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "hauteur"), gl4dpGetHeight());
    glUniform1i(glGetUniformLocation(pId, "largeur"), gl4dpGetWidth());
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}

void transition_circulaire(void (*a0)(int), void (*a1)(int), Uint32 t,
                           Uint32 et, int state) {
  /* INITIALISEZ VOS VARIABLES */
  int vp[4], i;
  GLint tId;
  static GLuint tex[2], pId;
  switch (state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE TRANSITION (SES VARIABLES <STATIC>s) */
    glGetIntegerv(GL_VIEWPORT, vp);
    glGenTextures(2, tex);
    for (i = 0; i < 2; i++) {
      glBindTexture(GL_TEXTURE_2D, tex[i]);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, vp[2], vp[3], 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, NULL);
    }
    pId = gl4duCreateProgram("<vs>shaders/basic.vs",
                             "<fs>shaders/circulaire.fs", NULL);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if (tex[0]) {
      glDeleteTextures(2, tex);
      tex[0] = tex[1] = 0;
    }
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR LES DEUX ANIMATIONS EN FONCTION DU SON */
    if (a0)
      a0(state);
    if (a1)
      a1(state);
    return;
  default: /* GL4DH_DRAW */
    /* RECUPERER L'ID DE LA DERNIERE TEXTURE ATTACHEE AU FRAMEBUFFER */
    glGetFramebufferAttachmentParameteriv(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                                          GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME,
                                          &tId);
    /* JOUER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tex[0], 0);
    if (a0)
      a0(state);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tex[1], 0);
    if (a1)
      a1(state);
    /* MIXER LES DEUX ANIMATIONS */
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           tId, 0);
    glDisable(GL_DEPTH);
    glUseProgram(pId);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex[0]);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex[1]);
    if (et / (GLfloat)t > 1) {
      fprintf(stderr, "%d-%d -- %f\n", et, t, et / (GLfloat)t);
      exit(0);
    }
    glUniform1f(glGetUniformLocation(pId, "dt"), et / (GLfloat)t);
    glUniform1i(glGetUniformLocation(pId, "tex0"), 0);
    glUniform1i(glGetUniformLocation(pId, "tex1"), 1);
    gl4dgDraw(_quadId);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  }
}

void animation_spirales(int state) {
  static GLuint _pId = 0;
  static GLfloat son = 0;
  static int increment = 0;
  int l, i;
  Uint16 *s;

  switch (state) {
  case GL4DH_INIT:
    glUseProgram(0);
    _pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/spirale.fs",
                              NULL);

    return;
  case GL4DH_FREE:
    gl4duClean(GL4DU_ALL);

    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    s = (Uint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    if (l >= 60)
      for (i = 0; i < 60; i++)
        son += s[i] / ((1 << 16) - 1.0);
    son /= 60;
    return;
  default: /* GL4DH_DRAW */

    glUseProgram(_pId);
    glUniform1i(glGetUniformLocation(_pId, "modulo"), 4);
    glUniform1i(glGetUniformLocation(_pId, "increment"), increment);
    glUniform1f(glGetUniformLocation(_pId, "hauteurs"), son);
    gl4dgDraw(_quadId);
    glUseProgram(0);

    increment += 1;
    increment %= 10;

    return;
  }
}

void animation_voronoi(int state) {
  /* INITIALISEZ VOS VARIABLES */

  static GLuint pId = 0, nb_sites = 15;
  static voronoi diag;
  static GLfloat son = 0;
  static double t0 = 0.0;
  static double elapcedtime =0.0;
  double t, dt;
  int l, i;
  Uint16 *s;

  switch (state) {
  case GL4DH_INIT:
    glUseProgram(0);
    pId = gl4duCreateProgram("<vs>shaders/basic.vs", "<fs>shaders/voronoi.fs",
                             NULL);
    initdiag(&diag, nb_sites);
    diag.coords[0] = 0.01;
    diag.coords[1] = 0.01;
    return;
  case GL4DH_FREE:
    freediag(&diag);
    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    s = (Uint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    if (l >= 60)
      for (i = 0; i < 60; i++)
        son += s[i] / ((1 << 16) - 1.0);
    son /= 60;
    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */
    t = gl4dGetElapsedTime() / 1000.0;
    dt = t - t0;
    t0 = t;
    elapcedtime += dt;
    glUseProgram(pId);
    int nb_envoye = MIN(MAX(1,(int)nb_sites*(elapcedtime - 20.0)/10.0),nb_sites);
    glUniform2fv(glGetUniformLocation(pId, "coords"), nb_envoye , diag.coords);
    glUniform3fv(glGetUniformLocation(pId, "colors"), nb_envoye , diag.colors);
    glUniform1i(glGetUniformLocation(pId, "nb_sites"), nb_envoye );
    glUniform1f(glGetUniformLocation(pId, "hauteur"), son);
    gl4dgDraw(_quadId);
    return;
  }
}

void animation_disco(int state) {
  static GLuint _pId = 0;
  static GLuint _texId[2] = {0, 0};
  static GLfloat _son = 0;

  static double t0 = 0.0;
  double t, dt;
  static GLfloat a = 0.0f;

  int l, i;
  Uint16 *st;

  SDL_Surface *s;

  switch (state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */

    s = IMG_Load("images/brique.jpeg");

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    _pId = gl4duCreateProgram("<vs>shaders/hello.vs", "<fs>shaders/hello.fs",
                              NULL);
    gl4duGenMatrix(GL_FLOAT, "proj");
    gl4duGenMatrix(GL_FLOAT, "mod");
    gl4duGenMatrix(GL_FLOAT, "view");
    gl4duBindMatrix("proj");
    gl4duLoadIdentityf();

    gl4duFrustumf(-1, 1, -1, 1, 2, 100);
    glGenTextures(2, _texId);

    glBindTexture(GL_TEXTURE_2D, _texId[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    /* transfert CPU-GPU */
    {
      /* conversion de format pour s'assurer d'avoir du RGBA en 32 bits */
      SDL_Surface *d = SDL_CreateRGBSurface(0, s->w, s->h, 32, 0xFF, 0xFF00,
                                            0xFF0000, 0xFF000000);
      SDL_BlitSurface(s, NULL, d, NULL);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, d->w, d->h, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, d->pixels);
      SDL_FreeSurface(d);
    }
    SDL_FreeSurface(s);
    s = IMG_Load("images/disco.jpeg");

    glBindTexture(GL_TEXTURE_2D, _texId[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    /* transfert CPU-GPU */
    {
      SDL_Surface *d = SDL_CreateRGBSurface(0, s->w, s->h, 32, 0xFF, 0xFF00,
                                            0xFF0000, 0xFF000000);
      SDL_BlitSurface(s, NULL, d, NULL);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, d->w, d->h, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, d->pixels);
      SDL_FreeSurface(d);
    }
    SDL_FreeSurface(s);
    glBindTexture(GL_TEXTURE_2D, 0);
    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if (_texId[0]) {
      glDeleteTextures(1, _texId);
      _texId[0] = 0;
    }
    if (_texId[1]) {
      glDeleteTextures(1, _texId + 1);
      _texId[1] = 0;
    }

    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    _son = 0;
    st = (Uint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    if (l >= 1024) {
      for (i = 0; i < 1024; i++)
        _son += st[i];
    }
    _son = _son / 1024;
    _son = _son / 3000;

    return;
  default: /* GL4DH_DRAW */
    /* JOUER L'ANIMATION */

    glEnable(GL_DEPTH_TEST);

    t = gl4dGetElapsedTime() / 1000.0;
    dt = t - t0;
    t0 = t;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    gl4duBindMatrix("view");
    gl4duLoadIdentityf();
    gl4duLookAtf(0.0f, 0, 15.0f, 0, 0, 0, 0, 1.0f, 0);

    scene2(a, dt, _pId, _cubeId,_sphereId, _texId, (GLfloat)_son);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_DEPTH_TEST);
    a += 180.0f * dt;
    return;
  }
}
void animation_intro(int state) {
  static GLuint _pId = 0;
  static GLuint _texId[2] = {0, 0};
  static GLfloat _son = 0;
  static double t0 = 0.0;
  double t, dt;
  static GLfloat a = 0.0f;

  int l, i;
  Uint16 *st;
  SDL_Surface *s;

  switch (state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */

    _pId = gl4duCreateProgram("<vs>shaders/hello.vs", "<fs>shaders/hello.fs",
                              NULL);

    gl4duGenMatrix(GL_FLOAT, "proj");
    gl4duGenMatrix(GL_FLOAT, "mod");
    gl4duGenMatrix(GL_FLOAT, "view");
    gl4duBindMatrix("proj");
    gl4duLoadIdentityf();
    gl4duFrustumf(-1, 1, -1, 1, 2, 100);

    glGenTextures(2, _texId);

    s = IMG_Load("images/colore.jpeg");
    assert(s);

    glBindTexture(GL_TEXTURE_2D, _texId[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    /* transfert CPU-GPU */
    {
      /* conversion de format pour s'assurer d'avoir du RGBA en 32 bits */
      SDL_Surface *d = SDL_CreateRGBSurface(0, s->w, s->h, 32, 0xFF, 0xFF00,
                                            0xFF0000, 0xFF000000);
      SDL_BlitSurface(s, NULL, d, NULL);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, d->w, d->h, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, d->pixels);
      SDL_FreeSurface(d);
    }
    SDL_FreeSurface(s);
    glBindTexture(GL_TEXTURE_2D, 0);
    gl4dpInitScreen();
    s = IMG_Load("images/noir.tif");
    assert(s);

    glBindTexture(GL_TEXTURE_2D, _texId[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    /* transfert CPU-GPU */
    {
      /* conversion de format pour s'assurer d'avoir du RGBA en 32 bits */
      SDL_Surface *d = SDL_CreateRGBSurface(0, s->w, s->h, 32, 0xFF, 0xFF00,
                                            0xFF0000, 0xFF000000);
      SDL_BlitSurface(s, NULL, d, NULL);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, d->w, d->h, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, d->pixels);
      SDL_FreeSurface(d);
    }
    SDL_FreeSurface(s);
    glBindTexture(GL_TEXTURE_2D, 0);

    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if (_texId[0]) {
      glDeleteTextures(1, _texId);
      _texId[0] = 0;
    }
    if (_texId[1]) {
      glDeleteTextures(1, _texId + 1);
      _texId[1] = 0;
    }
    gl4duClean(GL4DU_ALL);

    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    _son = 0;
    st = (Uint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    if (l >= 16)
      for (i = 0; i < 16; i++)
        _son += st[i];

    _son /= 16;
    _son = _son / 30000;

    return;
  default: /* GL4DH_DRAW */

    t = gl4dGetElapsedTime() / 1000.0;

    dt = t - t0;
    t0 = t;
    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl4duBindMatrix("view");
    gl4duLoadIdentityf();
    gl4duLookAtf(10*sin(a)/*0.0f*/, 10*cos(a), 10.0f, 0, 0, 0, 0, 1.0f, 0);
    scene1(a, dt, _pId, _cubeId,_quadId, _texId, (a <= 3.5) ? 0 : _son);
    a += dt ;
    glDisable(GL_DEPTH_TEST);
  }
}

void animation_Pendule_de_Newton(int state) {
  static GLuint _pId = 0;
  static GLuint _texd[3] = {0, 0, 0};
  static double t0 = 0.0;
  double t, dt;
  static GLfloat x = 0;

  SDL_Surface *s;
  switch (state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */
    gl4dpInitScreen();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    _pId = gl4duCreateProgram("<vs>shaders/hello.vs", "<fs>shaders/hello.fs",
                              NULL);
    gl4duGenMatrix(GL_FLOAT, "proj");
    gl4duGenMatrix(GL_FLOAT, "mod");
    gl4duGenMatrix(GL_FLOAT, "view");
    gl4duBindMatrix("proj");
    gl4duLoadIdentityf();
    gl4duFrustumf(-1, 1, -1, 1, 2, 100);
    glGenTextures(3, _texd);
    s = IMG_Load("images/alu_borsse.tif");

    glBindTexture(GL_TEXTURE_2D, _texd[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    /* transfert CPU-GPU */
    {
      /* conversion de format pour s'assurer d'avoir du RGBA en 32 bits */
      SDL_Surface *d = SDL_CreateRGBSurface(0, s->w, s->h, 32, 0xFF, 0xFF00,
                                            0xFF0000, 0xFF000000);
      SDL_BlitSurface(s, NULL, d, NULL);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, d->w, d->h, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, d->pixels);
      SDL_FreeSurface(d);
    }
    SDL_FreeSurface(s);

    s = IMG_Load("images/corde.tif");

    glBindTexture(GL_TEXTURE_2D, _texd[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    /* transfert CPU-GPU */
    {
      /* conversion de format pour s'assurer d'avoir du RGBA en 32 bits */
      SDL_Surface *d = SDL_CreateRGBSurface(0, s->w, s->h, 32, 0xFF, 0xFF00,
                                            0xFF0000, 0xFF000000);
      SDL_BlitSurface(s, NULL, d, NULL);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, d->w, d->h, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, d->pixels);
      SDL_FreeSurface(d);
    }
    SDL_FreeSurface(s);

    s = IMG_Load("images/bois_clair.tif");

    glBindTexture(GL_TEXTURE_2D, _texd[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    /* transfert CPU-GPU */
    {
      /* conversion de format pour s'assurer d'avoir du RGBA en 32 bits */
      SDL_Surface *d = SDL_CreateRGBSurface(0, s->w, s->h, 32, 0xFF, 0xFF00,
                                            0xFF0000, 0xFF000000);
      SDL_BlitSurface(s, NULL, d, NULL);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, d->w, d->h, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, d->pixels);
      SDL_FreeSurface(d);
    }
    SDL_FreeSurface(s);

    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if (_texd[1]) {
      glDeleteTextures(1, _texd);
      _texd[1] = 0;
    }
    if (_texd[2]) {
      glDeleteTextures(1, _texd + 1);
      _texd[2] = 0;
    }
    if (_texd[0]) {
      glDeleteTextures(1, _texd + 1);
      _texd[0] = 0;
    }
    gl4duClean(GL4DU_ALL);

    return;
  case GL4DH_UPDATE_WITH_AUDIO:

    return;
  default: /* GL4DH_DRAW */

    t = gl4dGetElapsedTime() / 1000.0;

    dt = t - t0;
    t0 = t;
    x += dt;
    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl4duBindMatrix("view");
    gl4duLoadIdentityf();
    gl4duLookAtf(20 * sin(x), 0, 20.0f, 1, 0, 0, 0, 1.0f, 0);
    scene3(dt, _pId, _cubeId, _sphereId, _cylindreId, _texd);
    glDisable(GL_DEPTH_TEST);
  }
}
void animation_outro(int state)
{
  static GLuint _pId = 0;
  static GLuint _texId[2] = {0, 0};
  static GLfloat _son = 0;
  static double t0 = 0.0;
  double t, dt;
  static GLfloat a = 0.0f;

  int l, i;
  Uint16 *st;
  SDL_Surface *s;

  switch (state) {
  case GL4DH_INIT:
    /* INITIALISEZ VOTRE ANIMATION (SES VARIABLES <STATIC>s) */

    _pId = gl4duCreateProgram("<vs>shaders/hello.vs", "<fs>shaders/hello.fs",
                              NULL);

    gl4duGenMatrix(GL_FLOAT, "proj");
    gl4duGenMatrix(GL_FLOAT, "mod");
    gl4duGenMatrix(GL_FLOAT, "view");
    gl4duBindMatrix("proj");
    gl4duLoadIdentityf();
    gl4duFrustumf(-1, 1, -1, 1, 2, 100);

    glGenTextures(2, _texId);

    s = IMG_Load("images/colore.jpeg");
    assert(s);

    glBindTexture(GL_TEXTURE_2D, _texId[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    /* transfert CPU-GPU */
    {
      /* conversion de format pour s'assurer d'avoir du RGBA en 32 bits */
      SDL_Surface *d = SDL_CreateRGBSurface(0, s->w, s->h, 32, 0xFF, 0xFF00,
                                            0xFF0000, 0xFF000000);
      SDL_BlitSurface(s, NULL, d, NULL);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, d->w, d->h, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, d->pixels);
      SDL_FreeSurface(d);
    }
    SDL_FreeSurface(s);
    glBindTexture(GL_TEXTURE_2D, 0);
    gl4dpInitScreen();
    s = IMG_Load("images/noir.tif");
    assert(s);

    glBindTexture(GL_TEXTURE_2D, _texId[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
    /* transfert CPU-GPU */
    {
      /* conversion de format pour s'assurer d'avoir du RGBA en 32 bits */
      SDL_Surface *d = SDL_CreateRGBSurface(0, s->w, s->h, 32, 0xFF, 0xFF00,
                                            0xFF0000, 0xFF000000);
      SDL_BlitSurface(s, NULL, d, NULL);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, d->w, d->h, 0, GL_RGBA,
                   GL_UNSIGNED_BYTE, d->pixels);
      SDL_FreeSurface(d);
    }
    SDL_FreeSurface(s);
    glBindTexture(GL_TEXTURE_2D, 0);

    return;
  case GL4DH_FREE:
    /* LIBERER LA MEMOIRE UTILISEE PAR LES <STATIC>s */
    if (_texId[0]) {
      glDeleteTextures(1, _texId);
      _texId[0] = 0;
    }
    if (_texId[1]) {
      glDeleteTextures(1, _texId + 1);
      _texId[1] = 0;
    }
    gl4duClean(GL4DU_ALL);

    return;
  case GL4DH_UPDATE_WITH_AUDIO:
    /* METTRE A JOUR VOTRE ANIMATION EN FONCTION DU SON */
    _son = 0;
    st = (Uint16 *)ahGetAudioStream();
    l = ahGetAudioStreamLength();
    if (l >= 16)
      for (i = 0; i < 16; i++)
        _son += st[i];

    _son /= 16;
    _son = _son / 30000;

    return;
  default: /* GL4DH_DRAW */

    t = gl4dGetElapsedTime() / 1000.0;

    dt = t - t0;
    t0 = t;
    glEnable(GL_DEPTH_TEST);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    gl4duBindMatrix("view");
    gl4duLoadIdentityf();
    gl4duLookAtf(10*cos(a),10*sin(a), 10.0f, 0, 0, 0, 0, 1.0f, 0);
    scene4(a, dt, _pId, _cubeId,_quadId, _texId, (a <= 89.5) ? 0 : _son);
    a += dt ;
    glDisable(GL_DEPTH_TEST);
  }
}

void animationsInit(void) {
  if (!_quadId)
    _quadId = gl4dgGenQuadf();
  if (!_cubeId)
    _cubeId = gl4dgGenCubef();
  if (!_sphereId)
    _sphereId = gl4dgGenSpheref(30, 30);
  if (!_cylindreId)
    _cylindreId = gl4dgGenCylinderf(20, 20);
}
