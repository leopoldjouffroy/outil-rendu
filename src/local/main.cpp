
/** TP 5ETI IMI- CPE Lyon - 2015-2016 */



#include "lib/common/error_handling.hpp"

#include "discrete/bresenham.hpp"
#include "discrete/line_discrete.hpp"
#include "discrete/line_interpolation_parameter.hpp"
#include "image/image.hpp"
#include "image/drawer.hpp"
#include "discrete/triangle_scanline.hpp"
#include "image/image_zbuffer.hpp"
#include "lib/mesh/mesh.hpp"
#include "lib/mesh/mesh_io.hpp"
#include "render_engine/render_engine.hpp"
#include "lib/3d/mat4.hpp"
#include "lib/3d/mat3.hpp"
#include "image/texture.hpp"

#include <iostream>
#include <fstream>
#include <cmath>



using namespace cpe;

int main(int argc,char *argv[])
{

    std::cout<<"***********************"<<std::endl;
    std::cout<<"run "<<argv[0]<<" with "<<argc-1<<" parameters ... \n"<<std::endl;


    try
    {
        //int const Nx = 40;
        //int const Ny = 25;

        //image im(Nx,Ny);
        //im.fill({1.0f,1.0f,1.0f});

        //im(20,10) = color(1.0f,1.0f,0.0f);
        //im(21,10) = color(1.0f,0.0f,0.0f);

        //for(int k=0;k<20;++k)
        //    im(10+k,5) = color(k/20.0f,0.0f,1.0f-k/20.0f);

        //for(int k=0;k<10;++k)
        //    im(5,3+k) = color(k/10.0f,k/10.0f,k/10.0f);

        line_discrete line; // creation d’une ligne discrete
        line.push_back(ivec2(4,5)); // ajout d’une position
        line.push_back({5,6}); // autre methode d’ajout
        ivec2 const p(6,7);
        line.push_back(p); // autre methode d’ajout
        //std::cout<<line<<std::endl; // affichage du contenu de la ligne
        //premiere methode de parcours de la ligne
        //for(int k=0;k<line.size();++k)
        //std::cout<<line[k]<<" ";
        //std::cout<<std::endl;
        //deuxieme methode de parcours de la ligne
        //for(ivec2 const& p : line)
        //std::cout<<p<<" ";
        //std::cout<<std::endl;

        line_discrete line2;
        bresenham({0,0},{5,5},line2);
        //std::cout<<line2<<std::endl;

        ivec2 const p0(5,10);
        ivec2 const p1(10,2);
        color const c(1.0f,0.0f,1.0f);

        //draw_line(im,p0,p1,c);

        //Interpolation de couleur
        //ivec2 const p2(2,15);
        //ivec2 const p3(15,15);
        //color const c1(1.0f,0.0f,0.0f);
        //color const c2(0.0f,1.0f,0.0f);

        //draw_line(im,p2,p3,c1,c2);

        //Triangle wireframe
        //ivec2 const p4(20,10);
        //ivec2 const p5(35,10);
        //ivec2 const p6(20,22);
        //color const c3(1.0f,0.75f,0.8f);

        //draw_triangle_wireframe(im,p4,p5,p6,c3);

        //Scanline
        //draw_triangle_wireframe(im , {15,12},{2,17},{6,3} , {0,0,0});
        //auto scanline = triangle_scanline_factory({15,12},{2,17},{6,3} ,
        //color(1,0,0),color(0,1,0),color(0,0,1));
        //std::cout<<scanline<<std::endl;

        //Triangle plein
        //draw_triangle(im, {15,12},{2,17},{6,3},color(1,0,0),color(0,1,0),color(0,0,1));

        //Pixel profondeur
        //image_zbuffer zbuffer = image_zbuffer(Nx,Ny);
        //draw_point(im, zbuffer, {15,12}, -1.0f, color(0,0,0));

        //Ligne profondeur
        //draw_line(im, zbuffer, {0,0}, {20,20}, -1.0f, 1.0f, color(0,0,0), color(1,1,1));
        //std::cout<< zbuffer(0,0)<< zbuffer(20,20) << zbuffer(5,5)<<std::endl;

        //Triangle profondeur
        //draw_triangle(im, zbuffer, {40,20},{2,17},{6,3},color(1,0,0),color(0,1,0),color(0,0,1),-1.0f,0.0f,1.0f);
        //draw_triangle(im, zbuffer, {4,20},{40,17},{38,3},color(1,1,0),color(1,1,0),color(1,1,0),-1.0f,0.0f,1.0f);

        //Projection
        //mat4 model; //identitee
        //mat4 view; //identitee
        //mat4 projection;
        //matrice de projection angle de vue de 60 degres,
        // image de taille carree,
        // sommets visibles entre z=0.1 et z=20.
        //projection.set_projection_perspective(60*M_PI/180.0f,1.0f,0.1f,20.0f);

        //points du triangle
        //vec3 p7(-5.0f,4.0f,-9.0f);
        //vec3 p8(5.0f,4.0f,-9.0f);
        //vec3 p9(0.0f,-5.0f,-9.0f);

        // normale du triangle
        //vec3 n = normalized(cross(p9-p7,p8-p7));

        //std::cout<<"Normale au triangle "<<n<<std::endl;

        //render(im, zbuffer,
        //       p7,p8,p9,
        //       color(1,0,0),color(1,0,0),color(0,0,1),
        //       n,n,n,
        //       model, view, projection);

        //zbuffer.save("buffer.ppm");

        //im.save("mon_image.ppm");

        //MESH
        //chargement du fichier
        mesh m = load_mesh_file("../projet/data/dino.obj");
        //applique potentiellement une rotation, translation
        //(scaling possible egalement)
        m.transform_apply_rotation({0,1,0},-M_PI/4.0f);
        m.transform_apply_translation({0,0,-1.5f});
        m.fill_color({1,1,1}); //applique la couleur blanche a
                               //l’ensemble des sommets
        m.fill_normal();       //calcul automatique des normales


        int const Nx = 4000;
        int const Ny = 2500;
        image im(Nx,Ny);
        im.fill({1.0f,1.0f,1.0f});

        image_zbuffer zbuffer = image_zbuffer(Nx,Ny);

        mat4 model; //identitee
        mat4 view; //identitee
        mat4 projection;
        projection.set_projection_perspective(60*M_PI/180.0f,1.0f,0.1f,20.0f);


        render(im,zbuffer,m,
               model,view, projection);

        im.save("mon_image.ppm");

    }
    catch(cpe::exception_cpe const& e)
    {


        std::cout<<"**********************************"<<std::endl;
        std::cout<<"**********************************"<<std::endl;
        std::cout<<"Exception found"<<std::endl;
        std::cout<<e.info()<<std::endl;
        std::cout<<"\nSaving backtrace in file backtrace_log.txt"<<std::endl;
        std::cout<<"**********************************"<<std::endl;
        std::cout<<"**********************************"<<std::endl;


        std::ofstream back_file("backtrace_log.txt");
        back_file<<e.info()<<std::endl;
        back_file<<e.info_backtrace();
        back_file.close();

        exit(1);
    }

    std::cout<<"Exit Main"<<std::endl;

    return 0;
}
