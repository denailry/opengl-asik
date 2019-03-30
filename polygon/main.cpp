#include <stdio.h> 
#include <stdlib.h> 
#include <curses.h>
#include <GL/glut.h> 
void myInit(void) { 
    glClearColor(1.0, 1.0, 1.0, 0.0); 
    glColor3f(0.0f, 0.0f ,1.0f); 
    glPointSize(4.0); 
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity(); 
    // gluOrtho2D(0.0,800.0,0.0,600.0); 
}

void myDisplay(void) { 
    glClear(GL_COLOR_BUFFER_BIT); 
    glBegin(GL_POLYGON); 
        glVertex2f(-0.5f, -0.4f);
        glVertex2f( 0.0f, -0.8f);
        glVertex2f( 0.5f, -0.4f);
        glVertex2f( 0.5f,  0.4f);
        glVertex2f( 0.0f,  0.8f);
        glVertex2f(-0.5f,  0.4f);
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