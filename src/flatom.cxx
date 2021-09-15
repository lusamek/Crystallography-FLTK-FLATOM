



/*
   - LOGICIEL LIBRE - EDU - 
   MIT Lic.
   auteur: moi 
   compilation sous linux (devuan):    
        c++ -lfltk -lm flatom.cxx -o flatom
   run: ./flatom 
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>  
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Button.H>


#define _Bool char                                                                           
char  charo[2500];
char  crossstr[2500];
char  vectorstr[2500];
char  zoneaxisstr[2500];
#define PI 3.14159265359f
#define LINE 1    
#define CHARACTER_ASPECT_RATIO .7f 




int p1xc, p1yc;                                                              
int p2xc, p2yc;                                                              
int p3xc, p3yc;                                                              
int p4xc, p4yc;                                                              
int p5xc, p5yc;                                                              
int p6xc, p6yc;                                                              
int p7xc, p7yc;                                                              
int p8xc, p8yc;                                                              

typedef struct {  
	float x, y, z; 
} vector_t;                                                                                  


typedef struct { 
	vector_t p1, p2, p3, p4, p5, p6, p7, p8; 
} cube_t;                                                                                    

float msin(float); 
float mcos(float);                                                                           

vector_t transform(vector_t v,    float m[3][3]);
cube_t   transform_cube(cube_t c, float m[3][3]);


vector_t vec1 = { 0 , 0 , 0 };
vector_t vec2 = { 1 , 1 , 1 };
vector_t vek =  { 1 , 1 , 1 };
int vecp1xc;  
int vecp1yc;  
int vecp2xc;  
int vecp2yc;  
int mode_debug = 0;
int vsetunset(int x)       
{                        
	if      (x == 0 )   x = 1;
	else if (x == 1 )   x = 2; // 2:red, for 1st plane
	else if (x == 2 )   x = 3; // 3:magenta, for 2nd plane 
	else if (x == 3 )   x = 4; // 4:green, for line 
	else if (x == 4 )   x = 0; // 0:vacancy
	printf( "Un/Reset Atom %d\n", x );
	return x;   
}                                                                                            



void rotate_x( float m[3][3], float r);
void rotate_y( float m[3][3], float r);
void rotate_z( float m[3][3], float r);



cube_t transform_cube(cube_t c, float m[3][3])
{
	c.p1=transform(c.p1, m); 
	c.p2=transform(c.p2, m); 
	c.p3=transform(c.p3, m); 
	c.p4=transform(c.p4, m); 
	c.p5=transform(c.p5, m); 
	c.p6=transform(c.p6, m); 
	c.p7=transform(c.p7, m); 
	c.p8=transform(c.p8, m); 
	return c;              
}                                                                                            




vector_t transform( vector_t v, float m[3][3])
{                                    
	vector_t r;  
	r.x=v.x*m[0][0]+v.y*m[0][1]+v.z*m[0][2];
	r.y=v.x*m[1][0]+v.y*m[1][1]+v.z*m[1][2];
	r.z=v.x*m[2][0]+v.y*m[2][1]+v.z*m[2][2];
	return r;                     
}                                                                                            





void rotate_x(float m[3][3], float r)
{                       
	m[0][0]=1; 
	m[0][1]=0; 
	m[0][2]=0; 
	m[1][0]=0; 
	m[1][1]=mcos(r);
	m[1][2]=-msin(r);
	m[2][0]=0;  
	m[2][1]=msin(r); 
	m[2][2]=mcos(r); 
}                                                                                            


void rotate_y(float m[3][3], float r)
{                                  
	m[0][0]=mcos(r); 
	m[0][1]=0;      
	m[0][2]=msin(r);
	m[1][0]=0;     
	m[1][1]=1;    
	m[1][2]=0;   
	m[2][0]=-msin(r);
	m[2][1]=0;       
	m[2][2]=mcos(r); 
}                                                                                            

void rotate_z(float m[3][3], float r)
{                                   
	m[0][0]=mcos(r);           
	m[0][1]=-msin(r);         
	m[0][2]=0;               
	m[1][0]=msin(r);        
	m[1][1]=mcos(r);       
	m[1][2]=0;            
	m[2][0]=0;           
	m[2][1]=0;          
	m[2][2]=1;         
}                                                                                            


float mcos(float x)       
{                        
	x+=PI/2;        
	if (x>PI/2) {     
		x=PI-x;   
	}                 
	return msin(x);   
}                                                                                            


float msin(float x)      
{                        
	float x2 = x*x;  
	float x4 = x2*x2;
	float t1 = x * (1.0f - x2 / (2*3)); 
	float x5 = x * x4;                  
	float t2 = x5 * (1.0f - x2 / (6*7)) / (1.0f* 2*3*4*5);  
	float x9 = x5 * x4;                                    
	float t3 = x9 * (1.0f - x2 / (10*11)) / (1.0f* 2*3*4*5*6*7*8*9); 
	float x13 = x9 * x4;                                            
	float t4 = x13 * (1.0f - x2 / (14*15)) / (1.0f* 2*3*4*5*6*7*8*9*10*11*12*13);            
	float result = t4;  
	result += t3;      
	result += t2;     
	result += t1;     
	return result;   
}                                                                                            


double x1 = 10 ; double ly1 = 10 ; 
double x2 = 200; double y2 = 200; 
double z1 = 10;  double z2 = 10 ;   

int show_line     = 1;
int line_weight   = 0;
int mode_settings = 0;
int show_planes  = 0;
int show_custom_direction1  = 0;
int show_custom_plane1 = 0;
int show_custom_plane2 = 0;
int show_plane   = 0;
int show_vector  = 1;
int show_labels  = 0;
int show_atoms   = 1;
int show_atom[ 10 ];
int show_atom_tracer  = 0;

double rot_x = 0; 
double rot_y = 0; 
double rot_z = 0; 
double px[10];
double py[10];
double pz[10];



double do_rot_x( double point )
{
	rot_x = rot_x + 0.2; 
	double foorot = rot_x * 3.14/180 ; 
	double fx  = point * cos( foorot ) - point * sin( foorot ) ;
	double fy  = point * sin( foorot ) + point * cos( foorot ) ;
	return fx; 
}
double do_rot_y( double point )
{
	rot_x = rot_x + 0.2; 
	double foorot = rot_x * 3.14/180 ; 
	double fx  = point * cos( foorot ) - point * sin( foorot ) ;
	double fy  = point * sin( foorot ) + point * cos( foorot ) ;
	return fy; 
}




// SIMPLE WIDGET THAT DRAWS AN 'X'
class DrawX : public Fl_Widget {
	public:
		DrawX( int X, int Y, int W, int H, const char*L=0) : Fl_Widget(X,Y,W,H,L) {
		}

		void drawcube( int foox1, int fooy1, int foox2, int fooy2 )
		{
			int foo = 100;
			fl_line(foox1, fooy1, foox1, fooy2);
			fl_line(foox2, fooy1, foox2, fooy2);
			fl_line(foox1, fooy1, foox2, fooy1);
			fl_line(foox1, fooy2, foox2, fooy2);
			fl_line( (int) foox1+foo,  (int)fooy1+foo, (int) foox1+foo, (int) fooy2+foo);
			fl_line( (int)foox2+foo,  (int)fooy1+foo,  (int)foox2+foo,  (int)fooy2+foo);
			fl_line( (int)foox1+foo,  (int)fooy1+foo,  (int)foox2+foo,  (int)fooy1+foo);
			fl_line( (int)foox1+foo,  (int)fooy2+foo,  (int)foox2+foo,  (int)fooy2+foo);
			fl_line( foox1, fooy1,  (int)foox1+foo,  (int)fooy1+foo);
			fl_line( foox2, fooy1,  (int)foox2+foo,  (int)fooy1+foo);
			fl_line( foox1, fooy2,   (int)foox1+foo,  (int)fooy2+foo);
			fl_line( foox2, fooy2,   (int)foox2+foo,  (int)fooy2+foo);
		}


		void draw() 
		{
		      //fl_line_style(2);
	 	      fl_line_style(0 , 0 );




                      // place custom planes
                      if ( show_custom_plane1 == 1 ) 
		      {
		          int psxy[10];   int psxx[10];
                          int i; int j; int rx[10]; int ry[10];
  			  for( i = 0 ; i <= 8 ; i++ ) 
  			  {
			       rx[i]  = 0;
			       ry[i]  = 0;
			  }
			  psxx[1] = p1xc; psxy[1] = p1yc;
			  psxx[2] = p2xc; psxy[2] = p2yc;
			  psxx[3] = p3xc; psxy[3] = p3yc;
			  psxx[4] = p4xc; psxy[4] = p4yc;
			  psxx[5] = p5xc; psxy[5] = p5yc;
			  psxx[6] = p6xc; psxy[6] = p6yc;
			  psxx[7] = p7xc; psxy[7] = p7yc;
			  psxx[8] = p8xc; psxy[8] = p8yc;
			  j = 1;
  			  for( i = 0 ; i <= 8 ; i++ ) 
  			  {
			     if ( show_atom[i] == 2 ) 
			     {
			       rx[j]  = psxx[i];
			       ry[j]  = psxy[i];
			       j++;
			     }
  			  }
  		          fl_color(FL_RED);
			  if (rx[1] > 0) 
			  if (rx[2] > 0) 
			  if (rx[3] > 0) 
			  if (rx[4] > 0) 
			  if (ry[1] > 0) 
			  if (ry[2] > 0) 
			  if (ry[3] > 0) 
			  if (ry[4] > 0) 
			  {
                            fl_polygon( rx[1], ry[1], rx[2], ry[2] , rx[3] , ry[3], rx[4], ry[4] );
                            fl_polygon( rx[1], ry[1], rx[2], ry[2] , rx[4] , ry[4], rx[3], ry[3] );
			  }
		      }



                      // place custom planes
                      if ( show_custom_plane2 == 1 ) 
		      {
		          int psxy[10];   int psxx[10];
                          int i; int j; int rx[10]; int ry[10];
  			  for( i = 0 ; i <= 8 ; i++ ) 
  			  {
			       rx[i]  = 0;
			       ry[i]  = 0;
			  }
			  psxx[1] = p1xc; psxy[1] = p1yc;
			  psxx[2] = p2xc; psxy[2] = p2yc;
			  psxx[3] = p3xc; psxy[3] = p3yc;
			  psxx[4] = p4xc; psxy[4] = p4yc;
			  psxx[5] = p5xc; psxy[5] = p5yc;
			  psxx[6] = p6xc; psxy[6] = p6yc;
			  psxx[7] = p7xc; psxy[7] = p7yc;
			  psxx[8] = p8xc; psxy[8] = p8yc;
			  j = 1;
  			  for( i = 0 ; i <= 8 ; i++ ) 
  			  {
			     if ( show_atom[i] == 3 ) 
			     {
			       rx[j]  = psxx[i];
			       ry[j]  = psxy[i];
			       j++;
			     }
  			  }
  		          fl_color(FL_MAGENTA);
			  if (rx[1] > 0) 
			  if (rx[2] > 0) 
			  if (rx[3] > 0) 
			  if (rx[4] > 0) 
			  if (ry[1] > 0) 
			  if (ry[2] > 0) 
			  if (ry[3] > 0) 
			  if (ry[4] > 0) 
			  {
                            fl_polygon( rx[1], ry[1], rx[2], ry[2] , rx[3] , ry[3], rx[4], ry[4] );
                            fl_polygon( rx[1], ry[1], rx[2], ry[2] , rx[4] , ry[4], rx[3], ry[3] );
			  }
		      }
		      




                      /// place lines 
			fl_line_style(0 , 0 );
			fl_color(FL_BLACK);
	                fl_line(p1xc, p1yc, p2xc, p2yc);                                                
			// if ( show_line == 1 ) 
		        //    drawcube( x1, ly1 , x2, y2  );
			fl_color(FL_BLUE);
			   fl_line( p2xc, p2yc, p4xc, p4yc);                                                
                           //fl_draw( "a3",  p2xc, p2yc );
			fl_color(FL_BLACK);
			fl_line(p4xc, p4yc, p3xc, p3yc);                                                
			fl_line(p3xc, p3yc, p1xc, p1yc);                                                
			fl_line(p5xc, p5yc, p6xc, p6yc);                                                
			fl_line(p6xc, p6yc, p8xc, p8yc);                                                
			fl_line(p8xc, p8yc, p7xc, p7yc);                                                
			fl_line(p7xc, p7yc, p5xc, p5yc);                                                
			fl_line(p1xc, p1yc, p5xc, p5yc);                                                
			fl_line(p2xc, p2yc, p6xc, p6yc);                                                
			fl_line(p3xc, p3yc, p7xc, p7yc);                                                

			fl_color(FL_RED);
			fl_line(p4xc,  p4yc,  p8xc, p8yc);                                                
                        //fl_draw( "a2",  p8xc, p8yc );

			fl_color(FL_MAGENTA);
			  fl_line(p4xc,  p4yc, p3xc, p3yc);                                                
                          //fl_draw( "a1",  p3xc, p3yc );

                      // place planes
                      if ( show_planes == 1 ) 
		      {
		        fl_color(FL_BLUE);
                        if ( show_plane == 1 ) 
                         fl_polygon( p1xc, p1yc, p2xc, p2yc , p4xc , p4yc, p3xc, p3yc );
                        if ( show_plane == 2 ) 
                         fl_polygon( p5xc, p5yc, p6xc, p6yc , p8xc , p8yc, p7xc, p7yc );
                        if ( show_plane == 3 ) 
                         fl_polygon( p1xc, p1yc, p2xc, p2yc , p6xc , p6yc, p5xc, p5yc );
                        if ( show_plane == 4 ) 
                         fl_polygon( p4xc, p4yc, p3xc, p3yc , p5xc , p5yc, p6xc, p6yc );
                        if ( show_plane == 5 ) 
                         fl_polygon( p2xc, p2yc, p5xc, p5yc , p7xc , p7yc, p4xc, p4yc );
		      }


                      // place atoms
                      if ( show_atoms == 1 ) 
		      {
		        fl_color(FL_BLUE);
		        fl_line_style(0 , line_weight );
			fl_circle(  p1xc, p1yc , 20 ); 
			fl_circle(  p2xc, p2yc , 20 ); 
			fl_circle(  p3xc, p3yc , 20 ); 
			fl_circle(  p4xc, p4yc , 20 ); 
			fl_circle(  p5xc, p5yc , 20 ); 
			fl_circle(  p6xc, p6yc , 20 ); 
			fl_circle(  p7xc, p7yc , 20 ); 
			fl_circle(  p8xc, p8yc , 20 ); 
		      }


                      // place atoms
                      if ( show_atoms == 2 ) 
		      {
		        fl_color(FL_BLUE);
		        fl_line_style(0 , line_weight );
                        if ( show_atom[1] == 1 ) 
			{ fl_color(FL_BLUE); fl_circle(  p1xc, p1yc , 20 ); }
                        if ( show_atom[1] == 2 ) 
			{ fl_color(FL_RED);   fl_circle(  p1xc, p1yc , 20 ); }
                        if ( show_atom[1] == 3 ) 
			{ fl_color(FL_MAGENTA);  fl_circle(  p1xc, p1yc , 20 ); }
                        if ( show_atom[1] == 4 ) 
			{ fl_color(FL_GREEN);  fl_circle(  p1xc, p1yc , 20 ); }

                        if ( show_atom[2] == 1 ) 
			{ fl_color(FL_BLUE); fl_circle(  p2xc, p2yc , 20 ); }
                        if ( show_atom[2] == 2 ) 
			{ fl_color(FL_RED);  fl_circle(  p2xc, p2yc , 20 ); }
                        if ( show_atom[2] == 3 ) 
			{ fl_color(FL_MAGENTA);  fl_circle(  p2xc, p2yc , 20 ); }
                        if ( show_atom[2] == 4 ) 
			{ fl_color(FL_GREEN);  fl_circle(  p2xc, p2yc , 20 ); }

                        if ( show_atom[3] == 1 ) 
			{ fl_color(FL_BLUE); fl_circle(    p3xc, p3yc , 20 ); }
                        if ( show_atom[3] == 2 ) 
			{ fl_color(FL_RED);  fl_circle(    p3xc, p3yc , 20 ); }
                        if ( show_atom[3] == 3 ) 
			{ fl_color(FL_MAGENTA);  fl_circle(  p3xc, p3yc , 20 ); }
                        if ( show_atom[3] == 4 ) 
			{ fl_color(FL_GREEN);  fl_circle(  p3xc, p3yc , 20 ); }

                        if ( show_atom[4] == 1 ) 
			{ fl_color(FL_BLUE); fl_circle(  p4xc, p4yc , 20 ); }
                        if ( show_atom[4] == 2 ) 
			{ fl_color(FL_RED);  fl_circle(  p4xc, p4yc , 20 ); }
                        if ( show_atom[4] == 3 ) 
			{ fl_color(FL_MAGENTA);  fl_circle(  p4xc, p4yc , 20 ); }
                        if ( show_atom[4] == 4 ) 
			{ fl_color(FL_GREEN);  fl_circle(  p4xc, p4yc , 20 ); }

                        if ( show_atom[5] == 1 ) 
			{ fl_color(FL_BLUE); fl_circle(  p5xc, p5yc , 20 ); }
                        if ( show_atom[5] == 2 ) 
			{ fl_color(FL_RED);  fl_circle(  p5xc, p5yc , 20 ); }
                        if ( show_atom[5] == 3 ) 
			{ fl_color(FL_MAGENTA);  fl_circle(  p5xc, p5yc , 20 ); }
                        if ( show_atom[5] == 4 ) 
			{ fl_color(FL_GREEN);  fl_circle(  p5xc, p5yc , 20 ); }

                        if ( show_atom[6] == 1 ) 
			{ fl_color(FL_BLUE); fl_circle(  p6xc, p6yc , 20 ); }
                        if ( show_atom[6] == 2 ) 
			{ fl_color(FL_RED);  fl_circle(  p6xc, p6yc , 20 ); }
                        if ( show_atom[6] == 3 ) 
			{ fl_color(FL_MAGENTA);  fl_circle(  p6xc, p6yc , 20 ); }
                        if ( show_atom[6] == 4 ) 
			{ fl_color(FL_GREEN);  fl_circle(  p6xc, p6yc , 20 ); }

                        if ( show_atom[7] == 1 ) 
			{ fl_color(FL_BLUE); fl_circle(  p7xc, p7yc , 20 ); }
                        if ( show_atom[7] == 2 ) 
			{ fl_color(FL_RED);  fl_circle(  p7xc, p7yc , 20 ); }
                        if ( show_atom[7] == 3 ) 
			{ fl_color(FL_MAGENTA);  fl_circle(  p7xc, p7yc , 20 ); }
                        if ( show_atom[7] == 4 ) 
			{ fl_color(FL_GREEN);  fl_circle(  p7xc, p7yc , 20 ); }

                        if ( show_atom[8] == 1 ) 
			{ fl_color(FL_BLUE); fl_circle(  p8xc, p8yc , 20 ); }
                        if ( show_atom[8] == 2 ) 
			{ fl_color(FL_RED);  fl_circle(  p8xc, p8yc , 20 ); }
                        if ( show_atom[8] == 3 ) 
			{ fl_color(FL_MAGENTA);  fl_circle(  p8xc, p8yc , 20 ); }
                        if ( show_atom[8] == 4 ) 
			{ fl_color(FL_GREEN);  fl_circle(  p8xc, p8yc , 20 ); }
		      }





                      // place custom direction1
                      if ( show_custom_direction1 == 1 ) 
		      {
		          int psxy[10];   int psxx[10];
                          int i; int j; int rx[10]; int ry[10];
  			  for( i = 0 ; i <= 8 ; i++ ) 
  			  {
			       rx[i]  = 0;
			       ry[i]  = 0;
			  }
			  psxx[1] = p1xc; psxy[1] = p1yc;
			  psxx[2] = p2xc; psxy[2] = p2yc;
			  psxx[3] = p3xc; psxy[3] = p3yc;
			  psxx[4] = p4xc; psxy[4] = p4yc;
			  psxx[5] = p5xc; psxy[5] = p5yc;
			  psxx[6] = p6xc; psxy[6] = p6yc;
			  psxx[7] = p7xc; psxy[7] = p7yc;
			  psxx[8] = p8xc; psxy[8] = p8yc;
			  j = 1;
  			  for( i = 0 ; i <= 8 ; i++ ) 
  			  {
			     if ( show_atom[i] == 4 )  // 4:green line  
			     {
			       rx[j]  = psxx[i];
			       ry[j]  = psxy[i];
			       j++;
			     }
  			  }
  		          fl_color(FL_GREEN);

			  if (rx[1] > 0) 
			  if (rx[2] > 0) 
			  if (ry[1] > 0) 
			  if (ry[2] > 0) 
			  {
		            fl_line_style(0 , 4 );
                            fl_line( rx[1], ry[1], rx[2], ry[2] );
                            fl_line( rx[1], ry[1], rx[2], ry[2] );
		            fl_line_style( 0 );
			    fl_color(FL_GREEN);
                            fl_draw( "A",  rx[1]-5, ry[1]+12 );
                            fl_draw( "B",  rx[2]-5, ry[2]+12 );
			  }

			  if (rx[3] > 0) 
			  if (rx[4] > 0) 
			  if (ry[3] > 0) 
			  if (ry[4] > 0) 
			  {
		            fl_line_style(0 , 4 );
                            fl_line( rx[3], ry[3], rx[4], ry[4] );
                            fl_line( rx[3], ry[3], rx[4], ry[4] );
		            fl_line_style( 0 );
			    fl_color(FL_GREEN);
                            fl_draw( "C",  rx[3]-5, ry[3]+12 );
                            fl_draw( "D",  rx[4]-5, ry[4]+12 );
			  }

			  if (rx[5] > 0) 
			  if (rx[6] > 0) 
			  if (ry[5] > 0) 
			  if (ry[6] > 0) 
			  {
		            fl_line_style(0 , 4 );
                            fl_line( rx[5], ry[5], rx[6], ry[6] );
                            fl_line( rx[5], ry[5], rx[6], ry[6] );
		            fl_line_style( 0 );
			    fl_color(FL_GREEN);
                            fl_draw( "E",  rx[5]-5, ry[5]+12 );
                            fl_draw( "F",  rx[6]-5, ry[6]+12 );
			  }

		      }
  		      fl_color(FL_BLACK);
		      fl_line_style( 0 , 0 );
		      fl_line_style( 0 );



   		        fl_color(FL_BLUE);
   		        fl_line_style( 0 , 0 );
   		        fl_line_style( 0 );
                        // vector [1,1,1]
			//fl_color(FL_RED);
			//fl_line( p4xc, p4yc, p5xc, p5yc);                                                

			fl_color(FL_BLACK);
                        snprintf( charo , sizeof( charo ), "[F1:Help/Info] [%d %d]", vecp1xc, vecp1yc );
                        fl_draw( charo ,  10 , 10 );

                        snprintf( charo , sizeof( charo ), "[M:%d][P:%d,%d][A:%d][R:%d][C:%d]", mode_settings,
			show_planes, show_plane, show_atoms, show_custom_plane1, show_custom_plane2 );
                        fl_draw( charo ,  10 , 50 );

                        snprintf( charo , sizeof( charo ), "%s", crossstr );
                        fl_draw( charo ,  10 , 70 );
                        snprintf( charo , sizeof( charo ), "%s", vectorstr );
                        fl_draw( charo ,  10 , 90 );
                        snprintf( charo , sizeof( charo ), "%s", zoneaxisstr );
                        //fl_draw( charo ,  10 , 90+30 );
                        fl_draw( charo ,  130 , 90+30 );


			fl_color(FL_RED);
			if ( show_line == 1 ) 
			   fl_line( vecp1xc, vecp1yc, vecp2xc, vecp2yc);
                        if ( show_atom_tracer == 1 ) 
			   fl_circle( vecp1xc , vecp1yc , 20 );



                      // place text labels
                      if ( show_labels == 1 ) 
		      {
			  fl_color(FL_BLACK);
                          fl_draw( "At.#1",  p1xc, p1yc+12 );
                          fl_draw( "At.#2",  p2xc, p2yc+12 );
                          fl_draw( "At.#3",  p3xc, p3yc+12 );
                          fl_draw( "At.#4",  p4xc, p4yc+12 );
                          fl_draw( "At.#5",  p5xc, p5yc+12 );
                          fl_draw( "At.#6",  p6xc, p6yc+12 );
                          fl_draw( "At.#7",  p7xc, p7yc+12 );
                          fl_draw( "At.#8",  p8xc, p8yc+12 );
		      }

			fl_color(FL_BLACK);
                          fl_draw( "a3",  p2xc, p2yc );
			fl_color(FL_RED);
                         fl_draw(  "a2",  p8xc, p8yc );
			fl_color(FL_MAGENTA);
                          fl_draw( "a1",  p3xc, p3yc );
			fl_color(FL_BLACK);
                          fl_draw( "0",  p4xc, p4yc );


			fl_line_style(0);        // must reset if we changed it
		}
};

















//// new for vector finder 
Fl_Input  *zoneaxiswin_in;
Fl_Output *zoneaxiswin_out;
Fl_Double_Window* zoneaxiswin;
void zoneaxis_win_but1( Fl_Widget* obj, void*)
{
   //printf(  "Vector: [%f %f %f]\n" , p4-p1, p5-p2, p6-p3 );  
   //snprintf( vectorstr , sizeof( vectorstr ), "Vector: %.2f %.2f %.2f" , p4-p1, p5-p2, p6-p3 );
   //vecoutput1->value(   );
   strncpy( zoneaxisstr  , zoneaxiswin_in->value() ,  sizeof( zoneaxisstr ) );
   zoneaxiswin_out->value( zoneaxisstr );
}

void zoneaxis_win_hide()
{
   zoneaxiswin->hide();
}
void zoneaxis_win_show()
{
    zoneaxiswin = new Fl_Double_Window( 310, 300, "Zone Axis"); //280
    Fl_Button *button2 = new Fl_Button( 70, 260, 180, 24 , "Cancel" );
    button2->callback( (Fl_Callback*) zoneaxis_win_hide );
    zoneaxiswin_in =   new Fl_Input( 70, 20,  180, 24,   "E.B.");
    zoneaxiswin_out =  new Fl_Output( 70, 200, 180, 24, "=");
    Fl_Button *button1 = new Fl_Button( 70, 230, 180, 24 , "Store!" );
    zoneaxiswin_out->color((Fl_Color)48);
    button1->callback( (Fl_Callback*) zoneaxis_win_but1 );
    zoneaxiswin->show();
    while( zoneaxiswin->shown() ) Fl::wait();
}




//// new for vector finder 
Fl_Input *vecinput1;
Fl_Input *vecinput2;
Fl_Input *vecinput3;
Fl_Input *vecinput4;
Fl_Input *vecinput5;
Fl_Input *vecinput6;
Fl_Output *vecoutput1;
Fl_Double_Window* vecmwin;
void vecmwin_but1_press( Fl_Widget* obj, void*)
{
   float p1 = atof(vecinput1->value());
   float p2 = atof(vecinput2->value());
   float p3 = atof(vecinput3->value());
   float p4 = atof(vecinput4->value());
   float p5 = atof(vecinput5->value());
   float p6 = atof(vecinput6->value());
   printf(  "Vector: [%f %f %f]\n" , p4-p1, p5-p2, p6-p3 );  
   snprintf( vectorstr , sizeof( vectorstr ), "Vector: %.2f %.2f %.2f" , p4-p1, p5-p2, p6-p3 );
   vecoutput1->value( vectorstr );
}

void vecmwin_press_hide()
{
   vecmwin->hide();
}
void vecmwin_calc_vector()
{
    vecmwin = new Fl_Double_Window(310, 300, "Vector AB"); //280
    Fl_Button *button2 = new Fl_Button( 70, 260, 180, 24 , "Cancel" );
    button2->callback( (Fl_Callback*) vecmwin_press_hide );
    vecinput1 = new Fl_Input( 70, 20,  180, 24,   "A.X");
    vecinput2 = new Fl_Input( 70, 50,  180, 24,   "A.Y");
    vecinput3 = new Fl_Input( 70, 80,  180, 24,   "A.Z");
    vecinput4 = new Fl_Input( 70,  110, 180, 24,   "B.X");
    vecinput5 = new Fl_Input( 70,  140, 180, 24, "B.Y");
    vecinput6 = new Fl_Input(  70, 170, 180, 24, "B.Z");
    vecoutput1 =         new Fl_Output( 70, 200, 180, 24, "=");
    Fl_Button *button1 = new Fl_Button( 70, 230, 180, 24 , "Store!" );
    vecoutput1->color((Fl_Color)48);
    button1->callback( (Fl_Callback*) vecmwin_but1_press );
    vecmwin->show();
    while( vecmwin->shown() ) Fl::wait();
}





Fl_Double_Window* mq_win_doublewindow;
void mq_but_quit( Fl_Widget* obj, void*)
{
   mq_win_doublewindow->hide();
   exit( 0 );
}
void mq_but_cancel( Fl_Widget* obj, void*)
{
    mq_win_doublewindow->hide();
}
void mq_win()
{
    mq_win_doublewindow = new Fl_Double_Window(  310, 100, "System" );
    Fl_Button *button2 = new Fl_Button( 70, 15 , 180, 24 , "Cancel" );
    button2->callback( (Fl_Callback*) mq_but_cancel );
    Fl_Button *button1 = new Fl_Button( 70, 55, 180, 24 , "Quit!" );
    button1->callback( (Fl_Callback*) mq_but_quit );
    mq_win_doublewindow->show();
    while( mq_win_doublewindow->shown() ) Fl::wait();
}




//// new for cross product 
Fl_Input *input1;
Fl_Input *input2;
Fl_Input *input3;
Fl_Input *input4;
Fl_Input *input5;
Fl_Input *input6;
Fl_Double_Window* mwin;
Fl_Output *crpoutput1;
void but1_press( Fl_Widget* obj, void*)
{
   float u1 = atof(input1->value());
   float v1 = atof(input2->value());
   float w1 = atof(input3->value());
   float u2 = atof(input4->value());
   float v2 = atof(input5->value());
   float w2 = atof(input6->value());
   printf( "[%f %f %f]\n" ,         u1, v1 , w1 );
   printf( "[%f %f %f]\n" ,         u2, v2 , w2 );
   printf( "Cross product: [%f %f %f]\n" ,  v1*w2 - w1 * v2 , w1*u2-u1*w2, u1*v2-v1*u2 );
   //mwin->hide();
   //printf(  "CSP: [%f %f %f]\n" , p4-p1, p5-p2, p6-p3 );  
   snprintf( crossstr , sizeof( crossstr ), "Cr.-Prd.: %.2f %.2f %.2f" ,  v1*w2 - w1 * v2 , w1*u2-u1*w2, u1*v2-v1*u2 );
   crpoutput1->value( crossstr );
   snprintf( crossstr , sizeof( crossstr ), "Cross-product: %.2f %.2f %.2f" ,  v1*w2 - w1 * v2 , w1*u2-u1*w2, u1*v2-v1*u2 );
}
void press_hide()
{
   mwin->hide();
}
void mwin_calc_cross()
{
    //vecmwin = new Fl_Double_Window(310, 300, "Vector AB"); //280
    //Fl_Button *button2 = new Fl_Button( 70, 260, 180, 24 , "Cancel" );
    //vecmwin = new Fl_Double_Window(310, 300, "Vector AB"); //280
    mwin = new Fl_Double_Window(  310, 300, "Cross-Product" );
    Fl_Button *button2 = new Fl_Button( 70, 260, 180, 24 , "Cancel" );
    button2->callback( (Fl_Callback*) press_hide );
    input1 = new Fl_Input(70, 20,  180, 24, " u1");
    input2 = new Fl_Input(70, 50,  180, 24, " v1");
    input3 = new Fl_Input(70, 80,  180, 24, " w1");
    input4 = new Fl_Input(70, 110, 180, 24, " u2");
    input5 = new Fl_Input(70,       140, 180, 24, " v2");
    input6 = new Fl_Input(  70,     170, 180, 24, " w2");
    crpoutput1 = new Fl_Output( 70, 200, 180, 24, "=");
    crpoutput1->color((Fl_Color)48);
    Fl_Button *button1 = new Fl_Button( 70, 230, 180, 24 , "Store!" );
    button1->callback( (Fl_Callback*) but1_press );
    mwin->show();
    while( mwin->shown() ) Fl::wait();
}









//// starts
//////////////////////////////////////////
//////////////////////////////////////////
int main( int argc, char *argv[])
{
	int ch; 
	int i=0; 
	int x, y;
	cube_t c={ 
		{ 0, 0, 0},  //  
		{ 0, 0, 1},  // z
		{ 0, 1, 0}, // x 
		{ 0, 1, 1}, // 0
		{ 1, 0, 0}, //   
		{ 1, 0, 1}, //  
		{ 1, 1, 0}, //  
		{ 1, 1, 1}  // y
	};                                                                                   


	float mxp[3][3];
	float myp[3][3];
	float mzp[3][3];
	float mxn[3][3];
	float myn[3][3];
	float mzn[3][3];

	float (*m)[3];                                                                       
	//float (*bm)[3];                                                                       
	float bm[3][3];

	int    height, width;                                                                   
	float  size_w, size_h;                                                                
	int    off_x, off_y;                                                                    
	int    origin_x = 0;
	int    origin_y = 0;

	height =  33; 
	width =   119; 
	size_w =  11; 
	size_h =  7.7; 
	off_x =   59; 
	off_y =   16; 

	//////////////////////////
	rotate_x( mxp, .1f); 
	rotate_y( myp, .1f); 
	rotate_z( mzp, .1f); 
	//////////////////////////
	rotate_x( mxn, -.1f);
	rotate_y( myn, -.1f);
	rotate_z( mzn, -.1f);
	//////////////////////////
	c=transform_cube( c, mxp ); 
	c=transform_cube( c, mxp ); 
	c=transform_cube( c, mzp ); 
	c=transform_cube( c, mzp ); 
	m=myp;     


	Fl_Window *win = new Fl_Window(400,500, "FTLK EDUCATION ATOMS (SAMEK)" );
	px[1]=50;
	py[1]=50;
	pz[1]=50;
	px[ 1 ] = 50 +50;   
	py[ 1 ] = 50 +50;   
	px[ 2 ] = 250 +50;   
	py[ 2 ] = 250 +50;   
	DrawX draw_x(0, 0,   500, 500 );
	win->resizable(win);
        win->color(FL_WHITE);
	win->show();

        // DEFINIITIONS (new)
        strncpy( crossstr  , "",  sizeof( crossstr ) );
        strncpy( vectorstr , "",  sizeof( vectorstr ) );
        strncpy( zoneaxisstr  , "",  sizeof( zoneaxisstr ) );
	show_atom[ 1 ] =  1 ; 
	show_atom[ 2 ] =  1 ; 
	show_atom[ 3 ] =  1 ; 
	show_atom[ 4 ] =  1 ; 
	show_atom[ 5 ] =  1 ; 
	show_atom[ 6 ] =  1 ; 
	show_atom[ 7 ] =  1 ; 
	show_atom[ 8 ] =  1 ; 
	//height=182; width=312;  size_w=47; size_h=362;
	//height=505; width=76;  size_h=72; size_w=182;
	height=505; width=365;  size_h=76; size_w=72;
	// place car
	//printf( "[car: %02d:%02d:%02f:%02f:%d:%d]\n",  height, width, size_w , size_h , off_x , off_y );
	height=305; width=365; size_w=181; size_h=185; origin_x=-120 ; origin_y = 0;
	height=305; width=365; size_w=181; size_h=185; origin_x=-80 ;  origin_y = 0;
	height=305; width=365; size_w=181; size_h=185; origin_x=-90 ;  origin_y = 40;
	//height=305; width=365; size_w=181; size_h=185; origin_x=390 ; origin_y = 160;
        vec2.x     = 1;
        vec2.y     = 1;
        vec2.z     = 1;
			    vec1.x     =  0;   vec1.y     = 0; vec1.z     = 0;
			    vec2.x     =  0;   vec2.y     = 0; vec2.z     = 0;
                            show_atom[ 1 ] =  1 ; 
                            show_atom[ 2 ] =  1 ; 
                            show_atom[ 3 ] =  1 ; 
                            show_atom[ 4 ] =  1 ; 
                            show_atom[ 5 ] =  1 ; 
                            show_atom[ 6 ] =  1 ; 
                            show_atom[ 7 ] =  1 ; 
                            show_atom[ 8 ] =  1 ; 

	//off_x = 62;
	//off_y = 152;
	int main_gameover = 0;
	while( main_gameover == 0 )
	{
                off_x= width/2   + origin_x; 
 	        off_y= height/2  + origin_y; 
		//i++;
		//c=transform_cube(c, m); 
		p1xc=(int)(c.p1.x*size_w)+off_x;
		p1yc=(int)(c.p1.y*size_h)+off_y;
		p2xc=(int)(c.p2.x*size_w)+off_x;
		p2yc=(int)(c.p2.y*size_h)+off_y;
		p3xc=(int)(c.p3.x*size_w)+off_x;
		p3yc=(int)(c.p3.y*size_h)+off_y;
		p4xc=(int)(c.p4.x*size_w)+off_x;
		p4yc=(int)(c.p4.y*size_h)+off_y;
		p5xc=(int)(c.p5.x*size_w)+off_x;
		p5yc=(int)(c.p5.y*size_h)+off_y;
		p6xc=(int)(c.p6.x*size_w)+off_x;
		p6yc=(int)(c.p6.y*size_h)+off_y;
		p7xc=(int)(c.p7.x*size_w)+off_x;
		p7yc=(int)(c.p7.y*size_h)+off_y;
		p8xc=(int)(c.p8.x*size_w)+off_x;
		p8yc=(int)(c.p8.y*size_h)+off_y;


		//////////////////////////////////
		//////////////////////////////////
	        //c.p1=transform(c.p1, m); 
         	bm[0][0]=1; 
         	bm[0][1]=0; 
         	bm[0][2]=0; 
         	bm[1][0]=0; 
         	bm[1][1]=1;
         	bm[1][2]=0;
         	bm[2][0]=0;  
         	bm[2][1]=0;
         	bm[2][2]=1;
		///two 
                vek  = transform( vec2 , bm );
		vec2 = vek;
                vek  = transform( vec1 , bm );
	        vec1 = vek;
		vecp1xc=(int)(vec1.x*size_w)+off_x;
		vecp1yc=(int)(vec1.y*size_h)+off_y;
		vecp2xc=(int)(vec2.x*size_w)+off_x;
		vecp2yc=(int)(vec2.y*size_h)+off_y;
		if (mode_debug == 1 )
		{
                 printf( "> vec1:  %f %f %f\n" , vec1.x, vec1.y , vec1.z  );
                 printf( "> vec2:  %f %f %f\n" , vec2.x, vec2.y , vec2.z  );
		}

		DrawX draw_x( 0, 0,   500, 500 );
		win->redraw();
                win->callback( (Fl_Callback*) mq_win );

		int ev = Fl::event();

                int mouse_but = Fl::event_button();
                int mouse_y = Fl::event_y();
                int mouse_x = Fl::event_x();
		printf( "x = %d\n" , mouse_x );
		printf( "y = %d\n" , mouse_y );
		printf( "m = %d\n" , mouse_but );
		printf( "L = %d\n" , FL_MOVE );

		int lastkey = 0;


	     if ( mode_debug == 1 )
	     { 	
     		printf( "[p1 :%02f:%02f:%02d:%02d]\n",     c.p1.x, c.p1.y, p1xc, p1yc );
     		printf( "[p2 :%02f:%02f:%02d:%02d]\n",     c.p2.x, c.p2.y, p2xc, p2yc );
     		printf( "[p3 :%02f:%02f:%02d:%02d]\n",     c.p3.x, c.p3.y, p3xc, p3yc );
     		printf( "[p4 :%02f:%02f:%02d:%02d]\n",     c.p4.x, c.p4.y, p4xc, p4yc );
     		printf( "[p5 :%02f:%02f:%02d:%02d]\n",     c.p5.x, c.p5.y, p5xc, p5yc );
     		printf( "[p6 :%02f:%02f:%02d:%02d]\n",     c.p6.x, c.p6.y, p6xc, p6yc );
     		printf( "[p7 :%02f:%02f:%02d:%02d]\n",     c.p7.x, c.p7.y, p7xc, p7yc );
     		printf( "[p8 :%02f:%02f:%02d:%02d]\n",     c.p8.x, c.p8.y, p8xc, p8yc );
	    }

		printf(" Usage: hjkl keys\n" );
		printf( "[car: %02d:%02d:%02f:%02f:%d:%d:%d:%d]\n",  height, width, size_w , 
		 size_h , off_x , off_y , origin_x, origin_y );

		if ( mouse_but == 1 )
		{
		          printf( "Button 1 \n" );
			  int psxx[10];
			  int psxy[10];
			  psxx[1] = p1xc; psxy[1] = p1yc;
			  psxx[2] = p2xc; psxy[2] = p2yc;
			  psxx[3] = p3xc; psxy[3] = p3yc;
			  psxx[4] = p4xc; psxy[4] = p4yc;
			  psxx[5] = p5xc; psxy[5] = p5yc;
			  psxx[6] = p6xc; psxy[6] = p6yc;
			  psxx[7] = p7xc; psxy[7] = p7yc;
			  psxx[8] = p8xc; psxy[8] = p8yc;
  			  for( i = 0 ; i <= 8 ; i++ ) 
  			  {
			     if ( psxx[i] - 20 <=  mouse_x )
			     if ( mouse_x <=      psxx[i] + 20 )
			     if ( psxy[i] - 20 <=  mouse_y )
			     if ( mouse_y <=      psxy[i] + 20 )
			     {
			          printf( "Atom #%d !\n", i );
			          //if ( show_atom[ i ] == 0 ) 
			          //   show_atom[ i ] = 1 ; 
 			          //else
			          //   show_atom[ i ] = 0 ; 
			     }
  			  }
 	        }



		////////////////////////////////////////////////////
		Fl::wait();
		{


		      if (Fl::event_key() == 65481 )
		      {
		                Fl::wait();
				if ( mode_settings == 1 ) mode_settings = 0;
				else mode_settings = 1;
		      }


                      if ( mode_settings == 1 )
                      {
         			if      (Fl::event_key() == '1' )   height++;
         			else if (Fl::event_key() == '2' )   height--;
         			else if (Fl::event_key() == '3' )   width++;
         			else if (Fl::event_key() == '4' )   width--;
         			else if (Fl::event_key() == '5' )   size_w++;
         			else if (Fl::event_key() == '6' )   size_w--;
         			else if (Fl::event_key() == '7' )   size_h++;
         			else if (Fl::event_key() == '8' )   size_h--;
                      }



                       if ( mode_settings == 0 )
	 	       if (Fl::event_key() == FL_Escape)
		       {
		                //win->hide();
				printf(" escape \n" );
                                //mq_win();
		                win->show();
 		       }

			else if (Fl::event_key() == 'q' )
			{
		                Fl::wait();
				if      ( show_plane == 0 ) show_plane= 1;
				else if ( show_plane == 1 ) show_plane= 2;
				else if ( show_plane == 2 ) show_plane= 3;
				else if ( show_plane == 3 ) show_plane= 4;
				else if ( show_plane == 4 ) show_plane= 5;
				else if ( show_plane == 5 ) show_plane= 1;
				show_planes = 1;
			}

			else if (Fl::event_key() == 't' )
			{
		                Fl::wait();
				if ( show_atom_tracer    == 1 ) 
					show_atom_tracer = 0;
				else
					show_atom_tracer = 1;
			}


			else if (Fl::event_key() == 'w' )   origin_y = origin_y - 20;
			else if (Fl::event_key() == 's' )   origin_y = origin_y + 20;

			else if (Fl::event_key() == 't' ) 
			{
                          vek = transform( vec1 , m );
		          vec1 = vek;
                          vek = transform( vec2 , m );
		          vec2 = vek;
		        }



         		else if (Fl::event_key() == '1' )  
			{
			     Fl::wait();
			     show_atom[ 1 ] =  vsetunset( show_atom[ 1 ] );  
			}
         		else if (Fl::event_key() == '2' ) 
			{
			     Fl::wait();
			     show_atom[ 2 ] =  vsetunset( show_atom[ 2 ] );  
			}
         		else if (Fl::event_key() == '3' )  
			{
			     Fl::wait();
			     show_atom[ 3 ] =  vsetunset( show_atom[ 3 ] );   
			}
         		else if (Fl::event_key() == '4' ) 
			{
			     Fl::wait();
			     show_atom[ 4 ] =  vsetunset( show_atom[ 4 ] );  
			}
         	        else if (Fl::event_key() == '5' ) 
			{
			     Fl::wait();
			     show_atom[ 5 ] =  vsetunset( show_atom[ 5 ] );  
			}
         		else if (Fl::event_key() == '6' ) 
			{
			     Fl::wait();
			     show_atom[ 6 ] =  vsetunset( show_atom[ 6 ] );  
			}
         		else if (Fl::event_key() == '7' ) 
			{
			     Fl::wait();
			     show_atom[ 7 ] =  vsetunset( show_atom[ 7 ] );  
			}
         		else if (Fl::event_key() == '8' )
			{
			     Fl::wait();
			     show_atom[ 8 ] =  vsetunset( show_atom[ 8 ] );  
			}

			else if (Fl::event_key() == 'g' ) 
			{
			    vec1.x     =  0;   vec1.y     = 0; vec1.z     = 0;
			    vec2.x     =  0;   vec2.y     = 0; vec2.z     = 0;
                            show_atom[ 1 ] =  1 ; 
                            show_atom[ 2 ] =  1 ; 
                            show_atom[ 3 ] =  1 ; 
                            show_atom[ 4 ] =  1 ; 
                            show_atom[ 5 ] =  1 ; 
                            show_atom[ 6 ] =  1 ; 
                            show_atom[ 7 ] =  1 ; 
                            show_atom[ 8 ] =  1 ; 
	    	        }
			else if (Fl::event_key() == 44 ) 
			{
			    printf( "line weight : %d\n", line_weight );
			    line_weight -= 1; 
			}
			else if (Fl::event_key() == 46 ) 
			{
			    printf( "line weight : %d\n", line_weight );
			    line_weight += 1; 
			}


			else if (Fl::event_key() == 'a' )   origin_x -= 20;
			else if (Fl::event_key() == 'd' )   origin_x += 20;
			//else if (Fl::event_key() == 'e' )   m=mzp;
			//else if (Fl::event_key() == 'q' )   m=mzn;

			else if (Fl::event_key() == 'k' ) 
			{
			     m=mxn;
		             c=transform_cube(c, m); 
                             vek = transform( vec1 , m );
		             vec1 = vek;
                             vek = transform( vec2 , m );
		             vec2 = vek;
			}
			else if (Fl::event_key() == 'j' )   
			{
			     m=mxp;
		             c=transform_cube(c, m); 
                          vek = transform( vec1 , m );
		          vec1 = vek;
                          vek = transform( vec2 , m );
		          vec2 = vek;
			}    
			else if (Fl::event_key() == 'h' ) 
			{ 
			    m=myp;
		            c=transform_cube(c, m); 
                          vek = transform( vec1 , m );
		          vec1 = vek;
                          vek = transform( vec2 , m );
		          vec2 = vek;
                        }
			else if (Fl::event_key() == 'l' ) 
			{
			    m=myn;
		            c=transform_cube(c, m); 
                          vek = transform( vec1 , m );
		          vec1 = vek;
                          vek = transform( vec2 , m );
		          vec2 = vek;
                        }
			else if (Fl::event_key() == 'u' )
			{
			    m=mzp;
		            c=transform_cube(c, m); 
                          vek = transform( vec1 , m );
		          vec1 = vek;
                          vek = transform( vec2 , m );
		          vec2 = vek;
                        }
			else if (Fl::event_key() == 'n' ) 
			{
			     m=mzn;
		             c=transform_cube(c, m); 
                          vek = transform( vec1 , m );
		          vec1 = vek;
                          vek = transform( vec2 , m );
		          vec2 = vek;
                        }



			else if (Fl::event_key() == 65453 )
			{  size_w-=10; size_h-=10; }
			else if (Fl::event_key() == 65451 )
			{  size_w+=10; size_h+=10; }
			else if (Fl::event_key() == '+' )
			{  size_w++; size_h++; }
			else if (Fl::event_key() == '-' )
			{  size_w--; size_h--; }


			else if (Fl::event_key() == 'c' )
			{    
                             mwin_calc_cross();
		             Fl::wait();
			}    
			else if (Fl::event_key() == 'v' )
			{    
                             vecmwin_calc_vector();
		             Fl::wait();
			}    
			else if (Fl::event_key() == 'z' )
			{
                                zoneaxis_win_show();
		                Fl::wait();
			}

			else if (Fl::event_key() == 'b' )
			{
		                Fl::wait();
				if ( show_atoms         == 0 ) show_atoms = 1;
				else if ( show_atoms    == 1 ) show_atoms = 2;
				else if ( show_atoms    == 2 ) show_atoms = 0;
			}
			else if (Fl::event_key() == '#' )
			{
		                Fl::wait();
				if (      show_labels         == 0 ) show_labels = 1;
				else if ( show_labels    == 1 ) show_labels = 0;
			}




			else if (Fl::event_key() == 'x' )
			{
		                Fl::wait();
				printf("GREEN DIRECTION\n");
				if (      show_custom_direction1 == 0 )      show_custom_direction1 = 1;
				else if ( show_custom_direction1 == 1 )      show_custom_direction1 = 0;
			}

			else if (Fl::event_key() == 'r' )
			{
		                Fl::wait();
				printf("RED PLANE\n");
				if (      show_custom_plane1 == 0 )      show_custom_plane1 = 1;
				else if ( show_custom_plane1 == 1 )      show_custom_plane1 = 0;
			}
			else if (Fl::event_key() == 'm' )
			{
		                Fl::wait();
				printf("MAGENTA PLANE\n");
				if (      show_custom_plane2 == 0 )      show_custom_plane2 = 1;
				else if ( show_custom_plane2 == 1 )      show_custom_plane2 = 0;
			}



			else if (Fl::event_key() == 'p' )
			{
		                Fl::wait();
				if ( show_planes == 1 ) 
				{
					show_planes= 0;
					show_custom_direction1= 0;
					show_custom_plane1= 0;
					show_custom_plane2= 0;
				}
				else
				{
					show_planes= 1;
				}
			}




			else if (Fl::event_key() == 65470 )
			{
		                Fl::wait();
				vec1.x -=0.5;
				if ( show_line == 1 ) 
					show_line = 0;
				else
					show_line = 1;
			}

			else if (Fl::event_key() == 65288 ) // BACKSPACE
			{
                                strncpy( crossstr , "",   sizeof( crossstr ) );
                                strncpy( vectorstr , "",  sizeof( vectorstr ) );
				printf( "Backspace: Clear the cross-product and vector infos \n" );
		                Fl::wait();
			}


			else if (Fl::event_key() == 65471 ) // F1
			{
		                Fl::wait();
				vec1.x -=0.5;
			}
			else if (Fl::event_key() == 65472 )  //F2
			{
		                Fl::wait();
				vec1.x +=0.5;
			}
			else if (Fl::event_key() == 65473 )  //F3
			{
		                Fl::wait();
				vec1.y -=0.5;
			}
			else if (Fl::event_key() == 65474 )  //F4
			{
		                Fl::wait();
				vec1.y +=0.5;
			}
			else if (Fl::event_key() == 65475 )  //F5
			{
		                Fl::wait();
				vec1.z -=0.5;
			}
			else if (Fl::event_key() == 65476 )  //F6
			{
		                Fl::wait();
				vec1.z +=0.5;
			}

			else if (Fl::event_key() == 65477 )
			{
		                Fl::wait();
				vec2.x +=0.5;
			}
			else if (Fl::event_key() == 65478 )
			{
		                Fl::wait();
				vec2.y -=0.5;
			}
			else if (Fl::event_key() == 65479 )
			{
		                Fl::wait();
				vec2.y +=0.5;
			}
			else if (Fl::event_key() == 65480 )
			{
		                Fl::wait();
				vec2.z -=0.5;
			}
			else if (Fl::event_key() == 65481 )
			{
		                Fl::wait();
				vec2.z +=0.5;
			}


			else if (Fl::event_key() == 65293 )
				printf(" Enter key Linux \n" );
			else if (Fl::event_key() == 65470 )
				printf(" F1 key Linux \n" );
			else 
				printf(" Pressed key\n");

			printf(" KEY=%d (%f,%f,%f) \n", Fl::event_key() , rot_x, rot_y , rot_z);
			lastkey = Fl::event_key();
		}
		Fl::check();
	}


	win->end();
	// Run and return
	return Fl::run();
}





