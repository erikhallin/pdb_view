#include "master.h"

master::master()
{
    //ctor
}

int master::init(void)
{
    //load temp file
    bool retval=load_protein("tempfile.pdb");
    if(!retval)
    {
        cout<<"ERROR: Protein could not be loaded\n";
    }

    return 0;
}

int master::update(void)
{


    return 0;
}

void master::draw(void)
{
    //draw atoms
    //Icosahed shape
    float vertices[] = {
        0.276f,  0.851f,  0.447f, 0.894f,  0.000f,  0.447f, 0.000f,  0.000f,  1.000f,
        -0.724f,  0.526f,  0.447f, 0.276f,  0.851f,  0.447f, 0.000f,  0.000f,  1.000f,
        -0.724f, -0.526f,  0.447f, -0.724f,  0.526f,  0.447f, 0.000f,  0.000f,  1.000f,
        0.276f, -0.851f,  0.447f, -0.724f, -0.526f,  0.447f, 0.000f,  0.000f,  1.000f,
        0.894f,  0.000f,  0.447f, 0.276f, -0.851f,  0.447f, 0.000f,  0.000f,  1.000f,
        0.000f,  0.000f, -1.000f, 0.724f,  0.526f, -0.447f,  -0.276f,  0.851f, -0.447f,
        0.000f,  0.000f, -1.000f, -0.276f,  0.851f, -0.447f,  -0.894f,  0.000f, -0.447f,
        0.000f,  0.000f, -1.000f, -0.894f,  0.000f, -0.447f,  -0.276f, -0.851f, -0.447f,
        0.000f,  0.000f, -1.000f, -0.276f, -0.851f, -0.447f,  0.724f, -0.526f, -0.447f,
        0.000f,  0.000f, -1.000f, 0.724f, -0.526f, -0.447f, 0.724f,  0.526f, -0.447f,
        0.894f,  0.000f,  0.447f, 0.276f,  0.851f,  0.447f, 0.724f,  0.526f, -0.447f,
        0.276f,  0.851f,  0.447f, -0.724f,  0.526f,  0.447f, -0.276f,  0.851f, -0.447f,
        -0.724f,  0.526f,  0.447f, -0.724f, -0.526f,  0.447f, -0.894f,  0.000f, -0.447f,
        -0.724f, -0.526f,  0.447f, 0.276f, -0.851f,  0.447f, -0.276f, -0.851f, -0.447f,
        0.276f, -0.851f,  0.447f, 0.894f,  0.000f,  0.447f, 0.724f, -0.526f, -0.447f,
        0.276f,  0.851f,  0.447f,  -0.276f,  0.851f, -0.447f, 0.724f,  0.526f, -0.447f,
        -0.724f,  0.526f,  0.447f,  -0.894f,  0.000f, -0.447f, -0.276f,  0.851f, -0.447f,
        -0.724f, -0.526f,  0.447f,  -0.276f, -0.851f, -0.447f, -0.894f,  0.000f, -0.447f,
        0.276f, -0.851f,  0.447f, 0.724f, -0.526f, -0.447f, -0.276f, -0.851f, -0.447f,
        0.894f,  0.000f,  0.447f, 0.724f,  0.526f, -0.447f, 0.724f, -0.526f, -0.447f };
    float normals[] = {
        -0.275974,-0.850921,-0.446958,-0.894427,-0,-0.447214,-0,-0,-1,0.723761,-0.525826,
        -0.446852,-0.275974,-0.850921,-0.446958,-0,-0,-1,0.723761,0.525826,-0.446852,0.723761,
        -0.525826,-0.446852,-0,-0,-1,-0.275974,0.850921,-0.446958,0.723761,0.525826,-0.446852,
        -0,-0,-1,-0.894427,-0,-0.447214,-0.275974,0.850921,-0.446958,-0,-0,-1,-0,-0,1,-0.723761,
        -0.525826,0.446852,0.275974,-0.850921,0.446958,-0,-0,1,0.275974,-0.850921,0.446958,
        0.894427,-0,0.447214,-0,-0,1,0.894427,-0,0.447214,0.275974,0.850921,0.446958,-0,-0,
        1,0.275974,0.850921,0.446958,-0.723761,0.525826,0.446852,-0,-0,1,-0.723761,0.525826,
        0.446852,-0.723761,-0.525826,0.446852,-0.894427,-0,-0.447214,-0.275974,-0.850921,
        -0.446958,-0.723761,-0.525826,0.446852,-0.275974,-0.850921,-0.446958,0.723761,-0.525826,
        -0.446852,0.275974,-0.850921,0.446958,0.723761,-0.525826,-0.446852,0.723761,0.525826,
        -0.446852,0.894427,-0,0.447214,0.723761,0.525826,-0.446852,-0.275974,0.850921,-0.446958,
        0.275974,0.850921,0.446958,-0.275974,0.850921,-0.446958,-0.894427,-0,-0.447214,-0.723761,
        0.525826,0.446852,-0.275974,-0.850921,-0.446958,0.275974,-0.850921,0.446958,-0.723761,
        -0.525826,0.446852,0.723761,-0.525826,-0.446852,0.894427,-0,0.447214,0.275974,-0.850921,
        0.446958,0.723761,0.525826,-0.446852,0.275974,0.850921,0.446958,0.894427,-0,0.447214,
        -0.275974,0.850921,-0.446958,-0.723761,0.525826,0.446852,0.275974,0.850921,0.446958,
        -0.894427,-0,-0.447214,-0.723761,-0.525826,0.446852,-0.723761,0.525826,0.446852};

    //color
    GLfloat LightAmbientGray[]=		{ 0.3f, 0.3f, 0.4f, 0.9f };
    GLfloat LightDiffuseGray[]=		{ 0.5f, 0.5f, 0.5f, 0.9f };
    GLfloat LightSpecularGray[]=	{ 0.2f, 0.3f, 0.2f, 0.9f };

    GLfloat LightAmbientWhite[]=	{ 0.6f, 0.6f, 0.6f, 0.9f };
    GLfloat LightDiffuseWhite[]=	{ 0.8f, 0.8f, 0.8f, 0.9f };
    GLfloat LightSpecularWhite[]=	{ 0.9f, 0.9f, 0.9f, 0.9f };

    GLfloat LightAmbientRed[]=		{ 0.5f, 0.2f, 0.2f, 0.9f };
    GLfloat LightDiffuseRed[]=		{ 0.7f, 0.3f, 0.3f, 0.9f };
    GLfloat LightSpecularRed[]=	    { 0.3f, 0.2f, 0.2f, 0.9f };

    GLfloat LightAmbientBlue[]=		{ 0.3f, 0.3f, 0.5f, 0.9f };
    GLfloat LightDiffuseBlue[]=		{ 0.3f, 0.3f, 0.8f, 0.9f };
    GLfloat LightSpecularBlue[]=	{ 0.2f, 0.2f, 0.3f, 0.9f };

    GLfloat LightAmbientYellow[]=	{ 0.5f, 0.5f, 0.2f, 0.9f };
    GLfloat LightDiffuseYellow[]=	{ 0.5f, 0.5f, 0.1f, 0.9f };
    GLfloat LightSpecularYellow[]=	{ 0.3f, 0.3f, 0.2f, 0.9f };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glNormalPointer(GL_FLOAT, 0, normals);

    //drawing
    for (int i=0;i<(int)m_vec_atoms.size();i++)
    {
        glPushMatrix();
        //set color
        switch(m_vec_atoms[i].type)
        {
            case 'C':
            {
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,LightAmbientGray);
                glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,LightDiffuseGray);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,LightSpecularGray);
            }break;
            case 'O':
            {
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,LightAmbientRed);
                glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,LightDiffuseRed);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,LightSpecularRed);
            }break;
            case 'N':
            {
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,LightAmbientBlue);
                glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,LightDiffuseBlue);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,LightSpecularBlue);
            }break;
            case 'S':
            {
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,LightAmbientYellow);
                glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,LightDiffuseYellow);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,LightSpecularYellow);
            }break;
            case 'H':
            {
                glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,LightAmbientWhite);
                glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,LightDiffuseWhite);
                glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,LightSpecularWhite);
            }break;
        }

        glTranslatef(m_vec_atoms[i].x,m_vec_atoms[i].y,m_vec_atoms[i].z);
        glScalef(m_vec_atoms[i].radius,m_vec_atoms[i].radius,m_vec_atoms[i].radius);
        glDrawArrays(GL_TRIANGLES, 0, 60);
        glPopMatrix();
    }

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    return;
}

bool master::load_protein(string file_path_name)
{
    ifstream file(file_path_name.c_str());
    if (file==0)
    {
        cout<<"ERROR: Can not find protein file\n";
        return false;
    }
    else //File OK
    {
        //Read positions and type of atoms
        enum chains{chainA=0,chainB,chainC,chainD,chainE,chainF,
                    chainG,chainH,chainI,chainJ,chainK,chainL};
        char curr_chain='w';
        int curr_chain_ID=-1;
        string line;
        while (getline(file,line)) //read PDB file
        {
            if (line[0]=='A'&&line[1]=='T'&&line[2]=='O'&&line[3]=='M')
            {
                if(line[13]!='C'&&line[13]!='O'&&line[13]!='N'&&line[13]!='S'&&line[13]!='H')//other atom
                {
                    st_atom temp_atom=get_atom_from_string(line);
                    m_vec_atoms_other.push_back(temp_atom);
                }
                else//protein atom
                {
                    st_atom temp_atom=get_atom_from_string(line);
                    m_vec_atoms.push_back(temp_atom);
                    if(line[13]=='C' && line[14]=='A') //atom is alpha carbon
                    {
                        if(curr_chain!=line[21])
                        {
                            curr_chain=line[21];

                            m_vvec_chains.push_back(vector<st_atom>());
                            curr_chain_ID++;
                        }
                        string residue; //get residue
                        residue.append(1,line[17]);
                        residue.append(1,line[18]);
                        residue.append(1,line[19]);
                        temp_atom.residue=residue;
                        m_vvec_chains[curr_chain_ID].push_back(temp_atom);
                    }
                }
            }
        }
        file.close();
        cout<<"\nNumber of chains in protein: "<<m_vvec_chains.size()<<"\n";
        cout<<"Number of atoms in protein: "<<m_vec_atoms.size()<<endl;

        calc_center_pos();//center viewing pos
    }

    return true;
}

st_atom master::get_atom_from_string(string line)
{
    //Send string line data to atom object
    st_atom temp_atom;
    //Get coord
    string sNumber;
    sNumber.append(1,line[31]);
    sNumber.append(1,line[32]);
    sNumber.append(1,line[33]);
    sNumber.append(1,line[34]);
    sNumber.append(1,line[35]);
    sNumber.append(1,line[36]);
    sNumber.append(1,line[37]);
    temp_atom.x=atof(sNumber.c_str());
    sNumber.clear();
    sNumber.append(1,line[39]);
    sNumber.append(1,line[40]);
    sNumber.append(1,line[41]);
    sNumber.append(1,line[42]);
    sNumber.append(1,line[43]);
    sNumber.append(1,line[44]);
    sNumber.append(1,line[45]);
    temp_atom.y=atof(sNumber.c_str());
    sNumber.clear();
    sNumber.append(1,line[47]);
    sNumber.append(1,line[48]);
    sNumber.append(1,line[49]);
    sNumber.append(1,line[50]);
    sNumber.append(1,line[51]);
    sNumber.append(1,line[52]);
    sNumber.append(1,line[53]);
    temp_atom.z=atof(sNumber.c_str());
    //Get radius
    temp_atom.type=line[13];
    float radius;
    switch (temp_atom.type)
    {
        case 'C': radius=0.7; break;
        case 'O': radius=0.6; break;
        case 'N': radius=0.65;break;
        case 'S': radius=1.0; break;
        case 'H': radius=0.25;break;
        default: radius=1;
    }
    temp_atom.radius=radius;
    return temp_atom;
}

void master::calc_center_pos(void)
{
    //Calculate the center of the protein
    m_max_pos[0]=m_vec_atoms[0].x; m_max_pos[1]=m_vec_atoms[0].y; m_max_pos[2]=m_vec_atoms[0].z;
    m_min_pos[0]=m_vec_atoms[0].x; m_min_pos[1]=m_vec_atoms[0].y; m_min_pos[2]=m_vec_atoms[0].z;
    //get extreme values
    for (int atom=0;atom<(int)m_vec_atoms.size();atom++)
    {
        if(m_vec_atoms[atom].x>m_max_pos[0]) m_max_pos[0]=m_vec_atoms[atom].x;
        if(m_vec_atoms[atom].x<m_min_pos[0]) m_min_pos[0]=m_vec_atoms[atom].x;
        if(m_vec_atoms[atom].y>m_max_pos[1]) m_max_pos[1]=m_vec_atoms[atom].y;
        if(m_vec_atoms[atom].y<m_min_pos[1]) m_min_pos[1]=m_vec_atoms[atom].y;
        if(m_vec_atoms[atom].z>m_max_pos[2]) m_max_pos[2]=m_vec_atoms[atom].z;
        if(m_vec_atoms[atom].z<m_min_pos[2]) m_min_pos[2]=m_vec_atoms[atom].z;
    }
    //calc center
    m_center_pos[0]=(m_max_pos[0]+m_min_pos[0])/2;
    m_center_pos[1]=(m_max_pos[1]+m_min_pos[1])/2;
    m_center_pos[2]=(m_max_pos[2]+m_min_pos[2])/2;
}
