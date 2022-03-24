/*!\file animations.h
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
#ifndef _ANIMATIONS_H

#define _ANIMATIONS_H

#ifdef __cplusplus
extern "C" {
#endif


 
  extern void transition_rideau(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void transition_rideau2(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void transition_careaux(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void transition_cercles(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
  extern void transition_circulaire(void (* a0)(int), void (* a1)(int), Uint32 t, Uint32 et, int state);
 
  extern void animation_intro(int state);
  extern void animation_voronoi(int state);
  extern void animation_Pendule_de_Newton(int state);
  extern void animation_spirales(int state);
  extern void animation_disco(int state);
  extern void animation_outro(int state);
  extern void animationsInit(void);

#ifdef __cplusplus
}
#endif

#endif
