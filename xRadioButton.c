#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <assert.h>
#include <unistd.h>
#include <stdlib.h>
#include "Xfs.h"

#define NIL (0)

#define ltbrown3Color 0xe0e0e0
#define ltbrownColor 0xc0c0c0
#define wheatColor 0xF5DEB3
#define brownColor 0x808080

int main(int argc, char *argv[])
{
	Window w, wradio, wradio2, wradio3, wradio4, wradio5, wradio6, wradio7, wradio8, wradio9, wradio10, wradio11, wradio12, wradio13, wradio14, wradio15, wradio16, wradio17, wradio18, wradio19, wradio20;
	Window wgrid;
	GC gc;
	int blackColor;
	int whiteColor;
	Display *dpy;
	XEvent e;
	int width, height;
	XFontStruct *font;
	char *greeting = "Hello, world!";
	XTextProperty ts;
	XClassHint class_hint;
	Window win_ret;
	int k, position, state;

	dpy = XfsInit(NIL);

	blackColor = BlackPixel(dpy, DefaultScreen(dpy));
	whiteColor = WhitePixel(dpy, DefaultScreen(dpy));

	w = XCreateSimpleWindow(dpy, DefaultRootWindow(dpy), 0, 0, 800, 600, 0, wheatColor, wheatColor);
	class_hint.res_name = "one";
	class_hint.res_class = "two";
	XSetClassHint(dpy, w, &class_hint);
	wradio = XfsCreateRadioButton(dpy, w, 5, 20, 100, 25, "Radio 1");
	wradio2 = XfsCreateRadioButton(dpy, w, 5, 50, 100, 25, "Radio 2");
	wradio3 = XfsCreateRadioButton(dpy, w, 5, 80, 100, 25, "Radio 3");
	wradio4 = XfsCreateRadioButton(dpy, w, 5, 110, 100, 25, "Radio 4");
	wradio5 = XfsCreateRadioButton(dpy, w, 5, 140, 100, 25, "Radio 5");

	wradio6 = XfsCreateRadioButton(dpy, w, 135, 20, 100, 25, "Radio 6");
	wradio7 = XfsCreateRadioButton(dpy, w, 135, 50, 100, 25, "Radio 7");
	wradio8 = XfsCreateRadioButton(dpy, w, 135, 80, 100, 25, "Radio 8");
	wradio9 = XfsCreateRadioButton(dpy, w, 135, 110, 100, 25, "Radio 9");
	wradio10 = XfsCreateRadioButton(dpy, w, 135, 140, 100, 25, "Radio 10");

	wradio11 = XfsCreateRadioButton(dpy, w, 265, 20, 100, 25, "Radio 11");
	wradio12 = XfsCreateRadioButton(dpy, w, 265, 50, 100, 25, "Radio 12");
	wradio13 = XfsCreateRadioButton(dpy, w, 265, 80, 100, 25, "Radio 13");
	wradio14 = XfsCreateRadioButton(dpy, w, 265, 110, 100, 25, "Radio 14");
	wradio15 = XfsCreateRadioButton(dpy, w, 265, 140, 100, 25, "Radio 15");

	wradio16 = XfsCreateRadioButton(dpy, w, 395, 20, 100, 25, "Radio 16");
	wradio17 = XfsCreateRadioButton(dpy, w, 395, 50, 100, 25, "Radio 17");
	wradio18 = XfsCreateRadioButton(dpy, w, 395, 80, 100, 25, "Radio 18");
	wradio19 = XfsCreateRadioButton(dpy, w, 395, 110, 100, 25, "Radio 19");
	wradio20 = XfsCreateRadioButton(dpy, w, 395, 140, 100, 25, "Radio 20");
  
	XSelectInput(dpy, w, KeyPressMask | ButtonPressMask | StructureNotifyMask | ExposureMask);

	XMapWindow(dpy, w);

	gc = XCreateGC(dpy, w, 0, NIL);

	font = XLoadQueryFont (dpy, "9x15");

	XSetForeground(dpy, gc, 0x0ff00);
	for (;;) {
		char buff[10];
		XComposeStatus compose;
		KeySym keysym;

		int state;
		XNextEvent (dpy, &e);
		XfsEventToolkitHandler(dpy, &e, &win_ret, (void *) &k);

		switch (e.type) {
		 case KeyPress:
			XLookupString(&e.xkey, buff, 10, &keysym, &compose);
			fprintf(stdout, "%s", buff);
			if(!strcmp(buff, "Q")) {
				XUnloadFont (dpy, font->fid);
				XFreeGC (dpy, gc);
				XCloseDisplay (dpy);
				exit(0);
			}
			break;
		case Expose:
			if (e.xexpose.count == 0)
				XDrawString (dpy, w, gc, (width - XTextWidth (font, greeting, strlen (greeting))) / 2, (height - (font->ascent + font->descent)) / 2, greeting, strlen (greeting));

			break;

		case ButtonPress:
			if(win_ret == wradio) {
				state = XfsGetRadioButtonState(wradio, 0);
				printf("Radio/Toggle 1 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio2) {
				state = XfsGetRadioButtonState(wradio2, 0);
				printf("Radio/Toggle 2 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio3) {
				state = XfsGetRadioButtonState(wradio3, 0);
				printf("Radio/Toggle 3 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio4) {
				state = XfsGetRadioButtonState(wradio4, 0);
				printf("Radio/Toggle 4 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio5) {
				state = XfsGetRadioButtonState(wradio5, 0);
				printf("Radio/Toggle 5 is clicked and it is %s state\n", state?"ON":"OFF");
			}

			if(win_ret == wradio6) {
				state = XfsGetRadioButtonState(wradio6, 0);
				printf("Radio/Toggle 6 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio7) {
				state = XfsGetRadioButtonState(wradio7, 0);
				printf("Radio/Toggle 7 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio8) {
				state = XfsGetRadioButtonState(wradio8, 0);
				printf("Radio/Toggle 8 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio9) {
				state = XfsGetRadioButtonState(wradio9, 0);
				printf("Radio/Toggle 9 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio10) {
				state = XfsGetRadioButtonState(wradio10, 0);
				printf("Radio/Toggle 10 is clicked and it is %s state\n", state?"ON":"OFF");
			}

			if(win_ret == wradio11) {
				state = XfsGetRadioButtonState(wradio11, 0);
				printf("Radio/Toggle 11 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio12) {
				state = XfsGetRadioButtonState(wradio12, 0);
				printf("Radio/Toggle 12 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio13) {
				state = XfsGetRadioButtonState(wradio13, 0);
				printf("Radio/Toggle 13 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio14) {
				state = XfsGetRadioButtonState(wradio14, 0);
				printf("Radio/Toggle 14 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio15) {
				state = XfsGetRadioButtonState(wradio15, 0);
				printf("Radio/Toggle 15 is clicked and it is %s state\n", state?"ON":"OFF");
			}

			if(win_ret == wradio16) {
				state = XfsGetRadioButtonState(wradio16, 0);
        printf("Radio/Toggle 16 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio17) {
				state = XfsGetRadioButtonState(wradio17, 0);
				printf("Radio/Toggle 17 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio18) {
				state = XfsGetRadioButtonState(wradio18, 0);
				printf("Radio/Toggle 18 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio19) {
				state = XfsGetRadioButtonState(wradio19, 0);
				printf("Radio/Toggle 19 is clicked and it is %s state\n", state?"ON":"OFF");
			}
			if(win_ret == wradio20) {
				state = XfsGetRadioButtonState(wradio20, 0);
				printf("Radio/Toggle 20 is clicked and it is %s state\n", state?"ON":"OFF");
			}


			break;
		}
	}
}
