#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void display();
void reshape(int,int);
int binarySearch();
void drawArrayRep();
void drawButton();
void menu(int);

void drawTextOverlays();

float winW=499.0,winH=499.0;

int a[10],mid,lb,ub,ind,n;
int key;
int ic=0;
bool dispRes=false;
bool isPresent=false;

bool invokedSearch=false;


GLint xStart=5,yStart=400;
GLint xAPOS[10],yAPOS[10];
GLint Bheight=40,Blength=50;

int main(int argc,char**argv)
{
    printf("Enter the number of elements(Max 10) \n");
    scanf("%d",&n);

    printf("Enter the elements of the array in a sorted fashion\n");
    for(int i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("Enter the key\n");
    scanf("%d",&key);

    ind=binarySearch();

    //printf("Index of found element %d",ind);

    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowSize(500,500);
    glutCreateWindow("Binary search");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutCreateMenu(menu);
    glutAddMenuEntry("Search    ",1);
    glutAddMenuEntry("Exit     ",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
void reshape(int w, int h)
{
    winW=(float)w;
    winH=(float)h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,499.0,0.0,499.0);
    glMatrixMode(GL_MODELVIEW);

}
void display()
{
    glClearColor(1.0,1.0,1.0,1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    drawArrayRep();
    drawTextOverlays();

    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
}
int binarySearch()
{
    ic=0;
    lb=0;
    ub=n-1;
    while(lb<=ub)
    {
        mid=(lb+ub)/2;

        if(a[mid]==key)
        {
            isPresent=true;
            return mid;
        }
        else if(key<a[mid])
        {
            ub=mid-1;
        }
        else
        {
            lb=mid+1;
        }
ic++;

    }

return -1;
}
void drawString(float x, float y, void *font, char *str)
{
  char *c;
  glRasterPos2f(x,y);
  for (c=str; *c != '\0'; c++)
  {

    glutBitmapCharacter(font, *c);
  }
}
void drawElement(GLint x, GLint y, int ai)
{
    GLfloat r=0.1,g=0.5,b=1.0;

    if(dispRes==true && ai==a[ind])
    {
        r=1.0;g=0.5;b=0.1;
    }

    glBegin(GL_POLYGON);
    glColor3f(r,g,b);
    glVertex2i(x,y);
    glVertex2i(x+Blength,y);
    glVertex2i(x+Blength,y+Bheight);
    glVertex2i(x,y+Bheight);
    glEnd();
    char ae[10];
    itoa(ai,ae,10);
    float xPos=x+(Blength/2);
    float yPos=y+(Bheight/2);
    glColor3f(1.0,1.0,1.0);
    drawString(xPos,yPos,GLUT_BITMAP_TIMES_ROMAN_10,ae);
}
void drawArrayRep()
{
   GLint cx=xStart;
   GLint cy=yStart;
   int cnum=a[0];

    for(int i=0;i<n;i++)
    {
       cnum=a[i];
       xAPOS[i]=cx;
       yAPOS[i]=cy;
       drawElement(xAPOS[i],yAPOS[i],cnum);

       cx+=Blength+1;

    }
}
void menu(int id)
{
    if(id==1)
    {
        if(invokedSearch==false)
        {
            invokedSearch=true;
            dispRes=true;
            glutPostRedisplay();
        }
        else
            {
                //do nothing
            }

    }
    else
    {
        exit(0);
    }

}
void drawTextOverlays()
{
    //text top
    glColor3f(0.0,0.0,0.0);
    drawString(5,455,GLUT_BITMAP_TIMES_ROMAN_10,"This is the array you had entered ");

                char k[10];
                itoa(key,k,10);
                char msgK[30] = "The key you entered: ";
                strcat(msgK,k);
    glColor3f(0.0,0.0,0.0);
    drawString(5,295,GLUT_BITMAP_TIMES_ROMAN_24,msgK);


    if(invokedSearch==false)
    {
        glColor3f(0.0,0.0,0.0);
        drawString(5,355,GLUT_BITMAP_TIMES_ROMAN_10,"To search for your entered key, use the menu and click on search");
    }
    else
    {
        if(dispRes==true)
        {
            if(isPresent==true)
            {
                char ae[10];
                itoa(ind+1,ae,10);
                char msg[30] = "Element found at position: ";
                strcat(msg,ae);

                char oi[10];
                itoa(ic+1,oi,10);
                char msg1[50] = "The operation took these many iterations: ";
                strcat(msg1,oi);

                glColor3f(0.0,0.0,0.0);
                drawString(5,355,GLUT_BITMAP_TIMES_ROMAN_10,msg);
                glColor3f(0.0,0.0,0.0);
                drawString(5,340,GLUT_BITMAP_TIMES_ROMAN_10,msg1);
            }
            else
                {
                     glColor3f(0.0,0.0,0.0);
                     drawString(5,355,GLUT_BITMAP_TIMES_ROMAN_10,"Element not found ");

                }
        }

    }

}
