
#include <assert.h>

typedef struct {
    int nb_sites ;
    float * coords,  * colors;
}voronoi;


void initdiag(voronoi *diag ,int nbSites);
void freediag(voronoi *diag);