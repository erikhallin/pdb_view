#ifndef MASTER_H
#define MASTER_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <gl\gl.h>

/*TO-DO

test drag and drop ok
load pdb ok
draw spheres ok
drag and drop load files ok... polish
center object

arcball


draw nice spheres
manual align
autoalign
draw backbone
color by ss

*/

using namespace std;

struct st_atom
{
    float  x,y,z,radius;
    char   type;
    string residue;
};

class master
{
    public:
        master();

        int init(void);
        int update(void);
        void draw(void);

        bool        load_protein(string file_path_name);
        st_atom     get_atom_from_string(string line);
        void        calc_center_pos(void);

    private:

        vector< vector<st_atom> >   m_vvec_chains;
        vector<st_atom>             m_vec_atoms;
        vector<st_atom>             m_vec_atoms_other;
        float                       m_center_pos[3];
        float                       m_max_pos[3], m_min_pos[3];
};

#endif // MASTER_H
