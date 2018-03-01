#include "GLSupport.hpp"

namespace graphics{

	static GLuint Tex;
	static GLuint FrameBuffer;
	static GLuint depthrenderbuffer;

	static int g_width, g_height;

	void (*userRender)(void);

	void reshapeFuction(int w, int h){
		g_width = w;
		g_height = h;
		glutSwapBuffers();
	}

	void displayFunc(){
		userRender();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, g_width, g_height);

		glClearColor(0.f, 0.f, 0.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, g_width, 0, g_height, -100, 100);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glBindTexture(GL_TEXTURE_2D, Tex);
		glBegin(GL_POLYGON);
			glTexCoord2f(0.f, 0.f);
			glVertex3d(0.f, 0.f, 0.f);
			
			glTexCoord2f(1.f, 0.f);
			glVertex3d(g_width, 0.f, 0.f);
			
			glTexCoord2f(1.f, 1.f);
			glVertex3d(g_width, g_height, 0.f);

			glTexCoord2f(0.f, 1.f);
			glVertex3d(0.f, g_height, 0.f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
		glutSwapBuffers();
	}

	void init(){
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
		glEnable(GL_DEPTH_TEST);
		glewInit();


		glGenTextures(1, &Tex);
		glBindTexture(GL_TEXTURE_2D, Tex);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, 512, 512, 0, GL_RGB,
			GL_UNSIGNED_BYTE, 0);

		glBindTexture(GL_TEXTURE_2D, 0);

		glGenFramebuffers(1, &FrameBuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);

		glGenRenderbuffers(1, &depthrenderbuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 512, 512);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, Tex, 0);
		
		GLenum e = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

	void idle(){
		
		glutPostRedisplay();
	}

	void InitAndCreateWindow(int argc, char* argv[], char* windowName, int width, int height, void(*idlefunc)(void)){
		g_width = width;
		g_height = height;
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutInitWindowSize(width, height);
		glutCreateWindow(windowName);

		init();
		userRender = idlefunc;
		glutDisplayFunc(displayFunc);
		glutReshapeFunc(reshapeFuction);
		glutIdleFunc(idle);

		glutMainLoop();
	}
	double xx = 0.f;

	void plot(int x, int y, float r, float g, float b){

		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, Tex, 0);

		GLenum e = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		glViewport(0, 0, 512, 512);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 512, 0, 512, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glBegin(GL_TRIANGLE_FAN);
			glColor3f(r, g, b);
			
			glVertex3d(x,			y,			0.f);
			glVertex3d(x + 1.f,		y,			0.f);
			glVertex3d(x + 1.f,		y + 1.f,	0.f);
			glVertex3d(x,			y + 1.f,	0.f);

		glEnd();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		
	}

	void drawLine(Point2f sp, Point2f ep, Color c) {
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
		glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, Tex, 0);

		GLenum e = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		glViewport(0, 0, 512, 512);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0, 512, 0, 512, -1, 1);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glBegin(GL_LINES);
		glLineWidth(3);
		glColor3f(c.r, c.g, c.b);
		glVertex3d(sp.x, sp.y, 0.f);
		glVertex3d(ep.x, ep.y, 0.f);
		glColor3f(1.0, 1.0, 1.0);

		glEnd();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void clear(){
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
		glClearColor(1.f, 1.f, 1.f, 0.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}