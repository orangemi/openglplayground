#include "App3.h"

AppDelegate::AppDelegate() {
}

AppDelegate::~AppDelegate() {
}

////////////////////////////////////////////////////////////////////////////

//void AppDelegate::startup() {
//	FT_Library ft;
//	if (FT_Init_FreeType(&ft)) {
//		std::cout << "FT init error" << std::endl;
//		return;
//	}
//
//	//FT_Face face;
//	if (FT_New_Face(ft, "res/font/msyh.ttf", 0, &face)) {
//		std::cout << "FT face error" << std::endl;
//		return;
//	}
//
//	if (FT_Set_Pixel_Sizes(face, 0, 48)) {
//		std::cout << "FT size error" << std::endl;
//		return;
//	}
//	
//	glActiveTexture(GL_TEXTURE0);
//	glGenTextures(1, &fontTexture);
////	glBindTexture(GL_TEXTURE_2D, fontTexture);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
//
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//	GLuint vertexShader;
//	GLuint fragShader;
//	loadVertexSharderSource("res/glsl/app3.vert", vertexShader);
//	loadFragSharderSource("res/glsl/app3.frag", fragShader);
//	compileShader(vertexShader, fragShader, program);
//	glDeleteShader(vertexShader);
//	glDeleteShader(fragShader);
//
//	GLuint uniformTexture = glGetUniformLocation(program, "tex");
//	GLuint uniformColor = glGetUniformLocation(program, "color");
//
//	glBindTexture(GL_TEXTURE_2D, fontTexture);
//	glUniform1i(uniformTexture, 0);
//	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
//
//	glGenBuffers(1, &vertexBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	

	//char * p = "a";
	////for (p = text; *p; p ++) {
	//if (FT_Load_Char(face, *p, FT_LOAD_RENDER)) {
	//	std::cout << "can not find char : " << *p << std::endl;
	//	//	continue;
	//}

	//FT_GlyphSlot g = face->glyph;
	//for (int j = 0; j < g->bitmap.rows; j++) {
	//	for (int i = 0; i < g->bitmap.width; i++) {
	//		unsigned char d = g->bitmap.buffer[j * g->bitmap.pitch + i];
	//		//char f = int(d) > 0 ? 'X' : '.';
	//		std::cout << (d > 250 ? 'X' : '.') << ' ';
	//	}
	//	std::cout << std::endl;

	//}




//}

//void AppDelegate::render(double time) {
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glClearColor(1, 0, 0, 1);
	//glClear(GL_COLOR_BUFFER_BIT);

	//glUseProgram(program);

	////char * text = "this is a test";
	//char * p = "a";
	////for (p = text; *p; p ++) {
	//if (FT_Load_Char(face, *p, FT_LOAD_RENDER)) {
	//	std::cout << "can not find char : " << *p << std::endl;
	////	continue;
	//}

	//FT_GlyphSlot g = face->glyph;

	//glBindTexture(GL_TEXTURE_2D, fontTexture);
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_ALPHA, g->bitmap.width, g->bitmap.rows, 0, GL_ALPHA, GL_UNSIGNED_BYTE, g->bitmap.buffer);

	//GLfloat box[4][4] = {
	//	{ -1,  -1, 0, 0 },
	//	{ -1,   1, 0, 1 },
	//	{  1,  -1, 1, 0 },
	//	{  1,   1, 1, 1 }
	//};

	//glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	//glEnableVertexAttribArray(0);
	//glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
	//glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

	//glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	////}

//}

void initFont(FT_Face &face, GLuint &textureBuffer) {
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		std::cout << "FT init error" << std::endl;
		return;
	}
	
	//FT_Face face;
	if (FT_New_Face(ft, "res/font/msyh.ttf", 0, &face)) {
		std::cout << "FT face error" << std::endl;
		return;
	}
	
	if (FT_Set_Pixel_Sizes(face, 0, 48)) {
		std::cout << "FT size error" << std::endl;
		return;
	}

	FT_Load_Char(face, 'X', FT_LOAD_RENDER);
	FT_GlyphSlot g = face->glyph;

	glGenTextures(1, &textureBuffer); 
	glBindTexture(GL_TEXTURE_2D, textureBuffer);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		g->bitmap.width,
		g->bitmap.rows,
		0,
		GL_ALPHA,
		GL_UNSIGNED_BYTE,
		g->bitmap.buffer
	);

	//gltextcoord

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}

void AppDelegate::startup() {
	GLuint vertexShader;
	GLuint fragShader;
	loadVertexSharderSource("res/glsl/app3.vert", vertexShader);
	loadFragSharderSource("res/glsl/app3.frag", fragShader);
	compileShader(vertexShader, fragShader, program);

	GLfloat g_vertex_buffer_data[4][4] = {
		{ -1.0f,  -1.0f, 0.0f, 0.0f },
		{ -1.0f,   1.0f, 0.0f, 1.0f },
		{  1.0f,  -1.0f, 1.0f, 0.0f },
		{  1.0f,   1.0f, 1.0f, 1.0f }
	};

	GLfloat g_frag_buffer_data[4][2] = {
		{ 0.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 0.0f },
		{ 1.0f, 1.0f }
	};

	glEnableVertexAttribArray(0);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

	glEnableVertexAttribArray(1); 
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_frag_buffer_data), g_frag_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void *)0);

//	glEnableVertexAttribArray(1);
//	glGenBuffers(1, &uvBuffer);
//	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(g_frag_buffer_data), g_frag_buffer_data, GL_STATIC_DRAW);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *)0);

//	int width, height;
//	bool hasAlpha;
//	GLubyte * bytes;
//	loadPngImg("res/img/011.png", width, height, hasAlpha, &bytes);
//	loadImgTexture(width, height, hasAlpha, bytes, textureBuffer);

	initFont(face, textureBuffer);

	glBindTexture(GL_TEXTURE_2D, textureBuffer);
	GLuint uniformTexture = glGetUniformLocation(program, "textureSampler");
	glUniform1i(uniformTexture, 0);

//	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_LESS);
}


void AppDelegate::render(double time) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glUseProgram(program);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

}


void AppDelegate::end() {
}