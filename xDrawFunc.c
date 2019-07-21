/* Excellent tutorial by Shellwave on xlib completed by
Jonathan Engwall, Tijuana Mexico, July 2019.
I noticed that only the x dimension was useful, so I
implemented the y dimesion as well. However, it does
not like to draw more than two curves at one time.
compile: gcc -o xDrawFun xFun.c -lX11 -lm  */
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <math.h>
/* Range of X axis is -10 to 10 */
#define MAX_X 20.0

/* Range of Y axis is -10 t0 10 */
#define MAX_Y 20.0

/* Draw on X */
float call_function(float x)
{
	return (-1) * (x * x);		
	/*	return (sin(x)/3)+(cos(x))+atan(x)*5;	*/
	//	return cos(x)*4/3;	
	/*	return x*x+4*x-6;	*/
	/*	return -(x*x)-(8*x)-5;	*/
	//	return atan(6-(x*x*x+abs(9*x)*(1/x))+5)/(x*x)/99;		
	/*	return ceil((sin(2019*x)/exp(2*M_PI)-1));	*/
}

/* Draw on Y  */
float draw_yfunc(float y)
{
	return y*y;
}

int draw_graph(Display *display, Window win)
{
	Window root_return;
	int x_return, y_return;
	unsigned int width_return, height_return;
	unsigned int border_width_return, depth_return;
	GC gc;
	XGCValues gcv;

	int blackpixel = BlackPixel(display, DefaultScreen(display));
	int whitepixel = WhitePixel(display, DefaultScreen(display));

	int x, y;

	float x1, y1;
	float x2, y2;

	float y3, x3;
	float y4, x4;

	int w1, h1;
	int w2, h2;

	/* step for larger graph */
	int ws, hs;

	int i;

	gcv.background = whitepixel;
	gcv.foreground = blackpixel;
	gc = XCreateGC (display, DefaultRootWindow(display),
		GCForeground | GCBackground, &gcv);

	XGetGeometry(display, win, &root_return, &x_return, &y_return,
		&width_return, &height_return, &border_width_return, &depth_return);

	XDrawLine(display, win, gc, 0, height_return/2, width_return, height_return/2);

	XDrawLine(display, win, gc, width_return/2, 0, width_return/2, height_return);

	/* draw the X COORD function */

	for(w1 = 0; w1 < width_return; w1++)
	{
		/* x1 is from L0_X to HI_X */

		x1 = (w1*2.0/width_return - 1.0) * MAX_X;
		y1 = call_function(x1);
		h1 = (1.0 - (y1/MAX_Y))*height_return/2.0;

		w2 = w1+1;
		x2 = (w2*2.0/width_return - 1.0) * MAX_X;
		y2 = call_function(x2);
		h2 = (1.0 - (y2/MAX_Y))*height_return/2.0;

		XDrawLine(display, win, gc, w1, h1,w2, h2);
	}
	/* draw the Y COORD function */

	for(h1 = 0; h1 < height_return; h1++)
	{
		/* y1 is from L0_Y to HI_Y */

		y3 = (h1*2.0/height_return - 1.0) * (-1)*MAX_Y;
		x3 = draw_yfunc(y3);
		w1 = (1.0 - ((-1)*(x3)/MAX_X))*width_return/2.0;

		h2 = h1+1;
		y4 = (h2*2.0/height_return - 1.0) * (-1)*MAX_Y;
		x4 = draw_yfunc(y4);
		w2 = (1.0 - ((-1)*(x4)/MAX_X))*width_return/2.0;

		XDrawLine(display, win, gc, w1, h1,w2, h2);
	}
/* Draws the Central Graphing Target and Grid  */
	for(x = -MAX_X; x <= MAX_X; x++)
	{
		w1 = (1.0 + (x/MAX_X))*width_return/2.0;
		ws = w1 * 10;
// Step function for larger or smaller workspace
		XDrawLine(display, win, gc, ws, height_return/2+3, ws, height_return/2-3);
//		XDrawLine(display, win, gc, w1, height_return/2+5, w1, height_return/2-5);
	}
	for(y = -MAX_Y; y <= MAX_Y; y++)
	{
		h1 = (1.0 - (y/MAX_Y))*height_return/2.0;
		hs = h1 * 10;
		XDrawLine(display, win, gc, width_return/2-5, hs, width_return/2+5, hs);
//		XDrawLine(display, win, gc, width_return/2-5, h1, width_return/2+5, h1);
	}
}
int main(int argc, char *argv[])
{
	Display *dpy;
	int screen;
	Window win, root_win;
	XEvent event;

	unsigned int depth;
	XSetWindowAttributes attrs;

	dpy = XOpenDisplay(NULL);

	if(dpy == NULL)
	{
		fprintf(stderr, "Cannot open display\n");
		exit(1);
	}
	
	screen = DefaultScreen(dpy);
	depth = DefaultDepth(dpy, screen);
	root_win = RootWindow(dpy, screen);

	attrs.border_pixel = BlackPixel(dpy, screen);
	attrs.background_pixel = WhitePixel(dpy, screen);
	attrs.override_redirect = True;
	attrs.colormap = CopyFromParent;
	attrs.event_mask = ExposureMask | KeyPressMask;

	/* parent window */
	win = XCreateWindow(dpy, root_win,
		200, 200, 900, 700, 0, depth, InputOutput, CopyFromParent,
		CWBackPixel | CWColormap | CWBorderPixel | CWEventMask, &attrs);

	XMapWindow(dpy, win);

	while(1)
	{
		XNextEvent(dpy, &event);
		if(event.type == Expose)
		{
			draw_graph(dpy, win);
		}
		if(event.type == KeyPress)
		{
			XDestroyWindow(dpy, win);
			XCloseDisplay(dpy);
			break;
		}
	}			

}
