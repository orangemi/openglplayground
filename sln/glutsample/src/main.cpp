#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>
#include <png.h>


GLubyte *textureImage;

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio =  w * 1.0 / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

float angle = 0.0f;

void renderScene(void) {

	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); glVertex3f(-1.0, -1.0, 0.0);
		glTexCoord2f(0.0, 1.0);	glVertex3f(-1.0,  1.0, 0.0);
		glTexCoord2f(1.0, 1.0);	glVertex3f( 1.0,  1.0, 0.0);
		glTexCoord2f(1.0, 0.0);	glVertex3f( 1.0, -1.0, 0.0);
	glEnd();

	glutSwapBuffers();
}



bool loadPngImage(const char* name, int &outWitdh, int &outHeight, bool &outHasAlpha, GLubyte **outData) {
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned int read = 0;
	int color_type, interlace_type;
	FILE *fp;

	if ((fp = fopen(name, "rb")) == NULL) {
		std::cout << "fopen" << std::endl;
		return false;
	}

	png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		std::cout << "png_ptr" << std::endl;
		fclose(fp);
		return false;
	}

	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr) {
		std::cout << "info_ptr" << std::endl;
		fclose(fp);
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}

	if (setjmp(png_jmpbuf(png_ptr))) {
		std::cout << "setjmp" << std::endl;
		fclose(fp);
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return false;
	}

	png_init_io(png_ptr, fp);
	png_set_sig_bytes(png_ptr, read);
	png_read_png(png_ptr, info_ptr, PNG_TRANSFORM_STRIP_16 | PNG_TRANSFORM_PACKING | PNG_TRANSFORM_EXPAND, NULL);
	png_uint_32 width, height;
	int bit_depth;
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL, NULL);
	outWitdh = width;
	outHeight = height;

	unsigned int row_bytes = png_get_rowbytes(png_ptr, info_ptr);
	*outData = (unsigned char*) malloc(row_bytes *outHeight);
	png_bytepp row_pointers = png_get_rows(png_ptr, info_ptr);

	for (int i = 0; i < outHeight; i++) {
		memcpy(*outData + (row_bytes * (outHeight - 1 - i)), row_pointers[i], row_bytes);
	}

	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

	return true;
}

void init() {

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	// The following two lines enable semi transparent
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	char* filename = "logo.png";
	int width, height;
	bool hasAlpha;
	bool success = loadPngImage(filename, width, height, hasAlpha, &textureImage);
	if (!success) {
		std::cout << "Unable to load " << filename << std::endl;
		return;
	}

	hasAlpha = false;
	std::cout << "Image loaded " << width << " " << height << " alpha " << hasAlpha << std::endl;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, hasAlpha ? GL_RGBA8 : GL_RGB8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureImage);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_CLAMP);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_CLAMP);
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);

}

int main(int argc, char **argv) {

	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(320,320);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");

	init();

	// register callbacks
	glutDisplayFunc(renderScene);
//	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0;
}