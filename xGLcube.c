/*shellwave tutorial xGL*/
/*Jonathan Engwall, Tijuana, Mexico July 23, 2019*/
/* compile: gcc -o xGLanimate xGLanimate.c -lX11 -lGL -lGLU */
/* Butterfly */
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>

/* GLX headers */

#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

Display *dpy;
XWindowAttributes winattr;
Window win;
void DrawTriangle(void)
{
	static int angle;
	static float pos = 0.0;

	XGetWindowAttributes(dpy, win, &winattr);
	glViewport(0, 0, winattr.width, winattr.height);

	glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	glRotatef(angle, 1.0, 1.0, 0.0);

	glBegin(GL_QUADS);

		glColor3f(0.0f, 0.9f, 1.0f);

		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glColor3f(0.0f, 0.0f, 1.0f);

		glVertex3f(0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glColor3f(0.0f, 1.0f, 0.0f);

		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glColor3f(1.0f, 0.0f, 9.0f);

		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glColor3f(8.0f, 8.0f, 8.0f);

		glVertex3f(-0.5f, 0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glVertex3f(-0.5f, -0.5f, -0.5f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glColor3f(0.0f, 0.0f, 0.0f);

		glVertex3f(0.5f, 0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glVertex3f(0.5f, 0.5f, -0.5f);

	glEnd();

	glPopMatrix();

	glXSwapBuffers(dpy, win);

	usleep(1000);
	angle += 1;
	if(angle == 360)
		angle = 0;

	pos += 0.001;
	if(pos >= 1.0)
		pos = 0.0;	
}
int main(int argc, char *argv[])
{
	int screen;
	Window root_win;
	XEvent event;

	unsigned int depth;
	XSetWindowAttributes attrs;

	GLint att[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	XVisualInfo *visual;
	GLXContext glc;

	dpy = XOpenDisplay(NULL);

	if(dpy == NULL)
	{
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}

	screen = DefaultScreen(dpy);
	depth = DefaultDepth(dpy, screen);
	root_win = RootWindow(dpy, screen);

	visual = glXChooseVisual(dpy, screen, att);

	attrs.border_pixel = BlackPixel(dpy, screen);
	attrs.background_pixel = WhitePixel(dpy, screen);
	attrs.override_redirect = True;

	attrs.colormap = XCreateColormap(dpy, root_win, visual->visual, AllocNone);
	attrs.event_mask = ExposureMask | KeyPressMask;

	win = XCreateWindow(dpy, root_win,
		200, 200, 800, 600, 0, visual->depth, InputOutput, visual->visual,
		CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &attrs);

	XMapWindow(dpy, win);

	glc = glXCreateContext(dpy, visual, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);

	glEnable(GL_DEPTH_TEST);

	while(1)
	{
		if(XPending(dpy) == 0)
		{
			DrawTriangle();
			continue;
		}
		XNextEvent(dpy, &event);
		if(event.type == Expose)
		{

		}
		if(event.type == KeyPress)
		{
			XDestroyWindow(dpy, win);
			XCloseDisplay(dpy);
			break;
		}
	}
}
