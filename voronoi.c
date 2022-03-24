#include "voronoi.h"
#include <GL4D/gl4du.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>


void initdiag(voronoi *diag ,int nbSites)
{
    srand(time(NULL));
    int i = 0;
    diag->coords = malloc(nbSites * 2 * sizeof(float));
    assert(diag->coords);
    diag->colors = malloc(nbSites* 3 * sizeof(float));
    assert(diag->colors);

    for(i = 0; i<nbSites ; ++i)
    {
        diag->coords[i*2] = gl4dmURand();
        diag->coords[i*2+1] = gl4dmURand();

        diag->colors[i*3] = gl4dmURand();
        diag->colors[i*3+1] = gl4dmURand();
        diag->colors[i*3+2] = gl4dmURand();
    }
}
void freediag(voronoi *diag)
{
    if(diag->coords)
    {
        free(diag->colors);
        diag->coords = NULL;
    }

    if(diag->colors)
    {
        free(diag->colors);
        diag->colors = NULL;
    }

}