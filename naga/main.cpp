#include <stdio.h> 
#include <stdlib.h> 
#include <curses.h>
#include <GL/glut.h> 
void myInit(void) { 
    glClearColor(1.0, 1.0, 1.0, 0.0); 
    glPointSize(4.0); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    // gluOrtho2D(0.0,800.0,0.0,600.0); 
}

void myDisplay(void) { 
    glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_TRIANGLES); 
        //kepala
        glColor3f(0.0f, 0.0f ,1.0f); 
        glVertex2f(-0.300f, 0.168f);
        glVertex2f( -0.322f, 0.044f);
        glVertex2f( -0.270f, 0.107f);
        glColor3f(0.0f, 0.25f ,1.0f); 
        glVertex2f(-0.289f, 0.090f);
        glVertex2f( -0.283f, 0.040f);
        glVertex2f( -0.270f, 0.107f);
        //leher
        glColor3f(0.0f, 0.0f ,0.75f); 
        glVertex2f(-0.270f, 0.107f);
        glVertex2f( -0.195f, 0.200f);
        glVertex2f( -0.125f, -0.140f);
        glColor3f(0.0f, 0.0f ,0.5f); 
        glVertex2f(-0.300f, 0.168f);
        glVertex2f(-0.270f, 0.107f);
        glVertex2f( -0.195f, 0.200f);
        //badan
        glColor3f(1.0f, 0.0f ,0.0f); 
        glVertex2f( -0.125f, -0.140f);
        glVertex2f(0.185f, -0.174f);
        glVertex2f( -0.165f, 0.060f);
        glColor3f(0.0f, 0.0f ,0.25f); 
        glVertex2f( -0.125f, -0.140f);
        glVertex2f(-0.240f, -0.085f);
        glVertex2f( -0.230f, 0.040f);
        glColor3f(0.5f, 0.0f ,0.0f); 
        glVertex2f( -0.085f, 0.010f);
        glVertex2f(0.185f, -0.174f);
        glVertex2f( 0.200f, -0.070f);
        //ekor
        glColor3f(0.0f, 0.2f ,1.0f); 
        glVertex2f( 0.290f, -0.060f);
        glVertex2f(0.185f, -0.174f);
        glVertex2f( 0.200f, -0.070f);
        glColor3f(0.0f, 0.4f ,1.0f); 
        glVertex2f( 0.290f, -0.060f);
        glVertex2f(0.287f, 0.030f);
        glVertex2f( 0.240f, -0.072f);
        glColor3f(0.0f, 0.6f ,1.0f); 
        glVertex2f( 0.285f, -0.036f);
        glVertex2f(0.287f, 0.030f);
        glVertex2f( 0.368f, 0.033f);
        glColor3f(0.0f, 0.8f ,1.0f); 
        glVertex2f( 0.317f, 0.021f);
        glVertex2f(0.344f, 0.120f);
        glVertex2f( 0.368f, 0.033f);
        //sayap
        glColor3f(1.0f, 1.0f ,0.0f); 
        glVertex2f( -0.010f, -0.010f);
        glVertex2f(-0.055f, 0.250f);
        glVertex2f( 0.270f, 0.270f);
        glColor3f(1.0f, 0.5f ,0.0f); 
        glVertex2f( -0.010f, -0.010f);
        glVertex2f(-0.055f, 0.250f);
        glVertex2f( -0.110f, 0.190f);
        //kaki depan
        glColor3f(0.0f, 1.0f ,0.0f); 
        glVertex2f( -0.130f, -0.130f);
        glVertex2f(-0.170f, -0.240f);
        glVertex2f( -0.190f, -0.110f);
        glColor3f(0.0f, 0.75f ,0.0f); 
        glVertex2f( -0.270f, -0.225f);
        glVertex2f(-0.170f, -0.240f);
        glVertex2f( -0.230f, -0.195f);
        glColor3f(0.0f, 0.5f ,0.0f); 
        glVertex2f( -0.295f, -0.250f);
        glVertex2f(-0.290f, -0.205f);
        glVertex2f( -0.230f, -0.195f);
        glColor3f(0.0f, 0.25f ,0.0f); 
        glVertex2f( -0.185f, -0.220f);
        glVertex2f(-0.170f, -0.240f);
        glVertex2f( -0.190f, -0.110f);
        //kaki belakang
        glColor3f(0.0f, 1.0f ,0.0f); 
        glVertex2f( 0.080f, -0.170f);
        glVertex2f(0.060f, -0.240f);
        glVertex2f( 0.040f, -0.160f);
        glColor3f(0.0f, 0.75f ,0.0f); 
        glVertex2f( -0.040f, -0.225f);
        glVertex2f(0.060f, -0.240f);
        glVertex2f( 0.00f, -0.195f);
        glColor3f(0.0f, 0.5f ,0.0f); 
        glVertex2f( -0.065f, -0.250f);
        glVertex2f(-0.04f, -0.205f);
        glVertex2f( 0.020f, -0.195f);
        glColor3f(0.0f, 0.25f ,0.0f); 
        glVertex2f( 0.035f, -0.220f);
        glVertex2f(0.060f, -0.240f);
        glVertex2f( 0.04f, -0.160f);
    glEnd(); 
    glFlush(); 
} 

int main(int argc,char * argv[]) { 
    glutInit(&argc,argv); 
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB); 
    glutInitWindowSize(800,600); 
    glutInitWindowPosition(100,100); 
    glutCreateWindow("opengl Window"); 
    glutDisplayFunc(myDisplay); 
    myInit(); 
    glutMainLoop(); 
    return 0; 
}