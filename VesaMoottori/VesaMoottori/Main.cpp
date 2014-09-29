#include <windows.h>
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <iostream>
#include <fstream>

#include <GL\glew.h>
#include <GL\GLU.h>
#include <GL\GL.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool GlewTests(); // Palauttaa true jos glew testit onnistuu.
char *ShaderReader(std::string fileName); // Luodaan shaderille merkkijono.

//GLint FileLength(); // Tarkastetaan .txt tiedoston pituus.
//bool InitGL(GLvoid); // Alustetaan OpenGL.
//bool DrawGLScene(GLvoid); // Alustetaan ikkuna piirtämistä varten.
//bool CreateGLWindow();
//GLvoid CloseGLWindow(GLvoid); // Vapauttaa asioita kun ohjelma suljetaan.

int main()
{
	const TCHAR				winName[] = TEXT("Window");
	const TCHAR				winClassName[] = TEXT("Window");
	MSG						messages;
	HGLRC					hRC = NULL; // Permanent rendering context.
	HDC						hDC = NULL; // Private GDI device context.
	HGLRC					hGLRC = NULL; // OpenGL rendering context.
	HWND					winHandle = NULL; // Holds window handle.
	HINSTANCE				hInstance = GetModuleHandle(nullptr); // Instance of the application
	WNDCLASSEX				winClass; // Sisältää ikkunan asetukset.
	PIXELFORMATDESCRIPTOR	winPixel; // Describes the pixel format of a drawing surface.
	bool					isRunning = true;
	int						pixFormat = NULL;

	// Alustetaan windows-ikkkuna.
	winClass.lpfnWndProc	= WndProc;
	winClass.cbSize			= sizeof(WNDCLASSEX);
	winClass.style			= CS_OWNDC;
	winClass.hInstance		= hInstance;
	winClass.hbrBackground	= CreateSolidBrush(RGB(255, 102, 255));
	winClass.lpszClassName	= winClassName;
	winClass.cbClsExtra		= NULL;
	winClass.cbWndExtra		= NULL;
	winClass.hIcon			= NULL;
	winClass.hCursor		= NULL;
	winClass.lpszMenuName	= NULL;
	winClass.hIconSm		= NULL;

	if (!RegisterClassEx(&winClass)) // Rekisteröidään ikkuna ja tarkistetaan onnistuuko se.
		std::cout << "RegisterClassEx failed!" << std::endl;
	else
		std::cout << "RegisterClassEx succeeded!" << std::endl;

	winHandle = CreateWindowEx( // Luodaan ikkuna ja sille handle jonka kautta sitä voidaan käyttää.
		NULL,
		winName,
		winClassName,
		WS_OVERLAPPEDWINDOW,
		200, 200,
		500, 500,
		NULL, NULL,
		hInstance,
		NULL);

	if (!winHandle) // Tarkastetaan handlen luominen.
		std::cout << "WindowHandle failed!" << std::endl;
	else
		std::cout << "WindowHandle succeeded!" << std::endl;

	hDC = GetDC(winHandle); // Asetetaan arvo aiemmin alustetulle device contextille.

	// Alustetaan OpenGL varten.
	winPixel.nSize			= sizeof(PIXELFORMATDESCRIPTOR);
	winPixel.nVersion		= 1;
	winPixel.dwFlags		= PFD_DOUBLEBUFFER | PFD_DRAW_TO_WINDOW | LPD_SUPPORT_OPENGL;
	winPixel.iPixelType		= PFD_TYPE_RGBA;
	winPixel.cColorBits		= 24;
	winPixel.cDepthBits		= 24;

	pixFormat = ChoosePixelFormat(hDC, &winPixel); // Etsitään lähin pixeliformaatti jota voidaan käyttää.
	if (!SetPixelFormat(hDC, pixFormat, &winPixel))
		std::cout << "SetPixelFormat failed!" << std::endl;
	else
		std::cout << "SetPixelFormat succeeded!" << std::endl;

	hGLRC = wglCreateContext(hDC); // Luodaan handle OpenGL renderöintiä varten.
	wglMakeCurrent(hDC, hGLRC); // Käytetään tätä ikkunaa komentokutsuissa.

	ShowWindow(winHandle, SW_SHOWNORMAL); // Näytetään rekisteröity ikkuna.
	UpdateWindow(winHandle);
	GlewTests(); // Testaa OpenGL 2.1 toimivuutta.


	// Piirrettään simppeli kolmio.
	GLuint vertexID;
	glGenVertexArrays(1, &vertexID);
	glBindVertexArray(vertexID);

	static const GLfloat triangleData[] = { // Kolmion kulmat.
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};

	GLuint vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleData), triangleData, GL_STATIC_DRAW);

	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	// Käyetään GLSL #version 120 tai aiempaa.
	// http://www.opengl.org/wiki/Shader_Compilation

	GLuint glObject			= glCreateProgram(); // Luodaan tyhjä objekti shaderia varten.
	GLuint glVertexShader	= glCreateShader(GL_VERTEX_SHADER); // Luodaan vertex shader.
	GLuint glFragmentShader	= glCreateShader(GL_FRAGMENT_SHADER); // Luodaan fragment shader.
	GLint linkCheck			= NULL; // Bool testaamista varten.
	char *vertexCode		= ShaderReader("vertexShader.txt"); // Shaderin koodi tekstitiedostosta.
	char *fragmentCode		= ShaderReader("fragmentShader.txt");

	// Lisätään shaderin koodi itse shaderiin.
	glShaderSource(glVertexShader, 1, &vertexCode, NULL); 
	glShaderSource(glFragmentShader, 1, &fragmentCode, NULL);
	// Compiloidaan shadereiden koodit.
	glCompileShader(glVertexShader); 
	glCompileShader(glFragmentShader);
	// Testataan onnistuiko compilointi.
	glGetShaderiv(glVertexShader, GL_COMPILE_STATUS, &linkCheck); 
	std::cout << "Vertex shaderin compilointi: " << linkCheck << std::endl;
	glGetShaderiv(glFragmentShader, GL_COMPILE_STATUS, &linkCheck);
	std::cout << "Fragment shaderin compilointi: " << linkCheck << std::endl;

	// Lisätään shaderit tyhjään objektiin.
	glAttachShader(glObject, glVertexShader);
	glAttachShader(glObject, glFragmentShader);
	glLinkProgram(glObject); // Linkkaaminen luo executablen shadereihin, jotka siihen on lisätty.
	glGetProgramiv(glObject, GL_LINK_STATUS, &linkCheck); // Testatataan shadereiden linkkaaminen objektiin.
	std::cout << "Linker bool: " << linkCheck << std::endl;
	glUseProgram(glObject); // Lisätään objekti tämänhetkiseen renderöintiin.


	while (isRunning) // Ohjelman main-looppi.
	{
		while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)) // Main loop jossa ikkuna ottaa vastaan viestejä.
		{
			//TranslateMessage(&messages); // Kääntää näppäin painalluksia tunnetuksi koodiksi.
			if (messages.message == WM_QUIT)
			{
				isRunning = false;
				wglDeleteContext(hGLRC); // Tuhotaan renderöinti sisältö.
				break;
			}
			DispatchMessage(&messages);

			// Kolmion piirtoa varten.
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			glDrawArrays(GL_TRIANGLES, 0, 3);
			glDisableVertexAttribArray(0);

			SwapBuffers(hDC); // Swapataan buffereita piirtoa varten.
		}
	}

	return (int) messages.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // Prosessoi viestejä ikkunalle.
{ 
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam); 
		break;
	}
	return 0;
} 

 bool GlewTests()
{
	GLenum error = glewInit(); // Alustetaan Glew.
	if (error == GLEW_OK)
		std::cout << "GLEW succeeded!" << std::endl;
	else
	{
		std::cout << "GLEW failed, error message: " << glewGetErrorString(error) << std::endl;
		return false;
	}

	if (GLEW_VERSION_2_1) // Tarkastetaan onko 2.1 käytössä.
		std::cout << "OpenGL 2.1 supported." << std::endl;
	else
	{
		std::cout << "OpenGL 2.1 not supported." << std::endl;
		return false;
	}
	return true;
}

 char *ShaderReader(std::string fileName)
 {
	 // Avataan luettava tiedosto ja tarkistetaan onnistuminen.
	 std::ifstream readFile(fileName, std::ios::in);
	 if(readFile.is_open())
		std::cout << "Opening file: " << fileName << std::endl;
	 else
	 { 
		 std::cout << "Could not open file: " << fileName << std::endl;
		 return NULL;
	 }

	 // Luettavan tiedoston pituus.
	 readFile.seekg(0, readFile.end); // Pistetään char position filun loppuun.
	 int fileLength = readFile.tellg(); // Pistetään pituus ylös.
	 readFile.seekg(0, readFile.beg); // Positio takasin alkuun.
	 if(fileLength == 0)
	 {
		 std::cout << "ERROR: Luettavan tiedoston pituus 0." << std::endl;
		 return NULL;
	 }
	 else
		 std::cout << "Luettavan tiedoston pituus: " << fileLength << std::endl;

	 std::string fileContents((std::istreambuf_iterator<char>(readFile)),
							  std::istreambuf_iterator<char>()); // Kopioidaan tiedoston sisältö stringiin.
	 char *tempChar = new char[fileContents.length() + 1];
	 std::strcpy(tempChar, fileContents.c_str()); // Kopioidaan tiedoston sisällöt dynaamisesti luotuun char-merkkijonoon.

	 std::cout << "Closing file: " << fileName << std::endl;
	 readFile.close();
	 return tempChar;
 }