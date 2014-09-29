#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <iostream>

#include <GL\glew.h>
#include <GL\GLU.h>
#include <GL\GL.h>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
bool GlewTests(); // Palauttaa true jos glew testit onnistuu.
//bool InitGL(GLvoid); // Alustetaan OpenGL.
//bool DrawGLScene(GLvoid); // Alustetaan ikkuna piirt�mist� varten.
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
	WNDCLASSEX				winClass; // Sis�lt�� ikkunan asetukset.
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

	if (!RegisterClassEx(&winClass)) // Rekister�id��n ikkuna ja tarkistetaan onnistuuko se.
		std::cout << "RegisterClassEx failed!" << std::endl;
	else
		std::cout << "RegisterClassEx succeeded!" << std::endl;

	winHandle = CreateWindowEx( // Luodaan ikkuna ja sille handle jonka kautta sit� voidaan k�ytt��.
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

	pixFormat = ChoosePixelFormat(hDC, &winPixel); // Etsit��n l�hin pixeliformaatti jota voidaan k�ytt��.
	if (!SetPixelFormat(hDC, pixFormat, &winPixel))
		std::cout << "SetPixelFormat failed!" << std::endl;
	else
		std::cout << "SetPixelFormat succeeded!" << std::endl;

	hGLRC = wglCreateContext(hDC); // Luodaan handle OpenGL render�inti� varten.
	wglMakeCurrent(hDC, hGLRC); // K�ytet��n t�t� ikkunaa komentokutsuissa.

	ShowWindow(winHandle, SW_SHOWNORMAL); // N�ytet��n rekister�ity ikkuna.
	UpdateWindow(winHandle);
	GlewTests(); // Testaa OpenGL 2.1 toimivuutta.

	

	//glClearColor(1.0f, 0.2f, 1.0f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);
	// K�yet��n GLSL #version 120 tai aiempaa.
	// http://www.opengl.org/wiki/Shader_Compilation

	GLuint glObject = glCreateProgram();
	GLuint glVertexShader = glCreateShader(GL_VERTEX_SHADER); // Luodaan vertex shader.
	GLuint glFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	GLint linkCheck = NULL;
	
	const char *shaderCode;

	glShaderSource(glVertexShader, 1, &shaderCode, NULL);

	glAttachShader(glObject, glVertexShader); // Lis�t��n shaderi tyhj��n objektiin.
	glLinkProgram(glObject); // Linkkaaminen luo executablen shadereihin jotka siihen on lis�tty.

	// Testatataan linkkaaminen ja shaderin compilointi.
	glGetProgramiv(glObject, GL_LINK_STATUS, &linkCheck);
	std::cout << "Linker bool: " << linkCheck << std::endl;
	glGetShaderiv(glVertexShader, GL_COMPILE_STATUS, &linkCheck);
	std::cout << "Vertex shaderin compilointi: " << linkCheck << std::endl;
	glGetShaderiv(glFragmentShader, GL_COMPILE_STATUS, &linkCheck);
	std::cout << "Fragment shaderin compilointi: " << linkCheck << std::endl;

	glUseProgram(glObject); // Lis�t��n t�m�nhetkiseen render�intiin.



	while (isRunning) // Ohjelman main-looppi.
	{
		while (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE)) // Main loop jossa ikkuna ottaa vastaan viestej�.
		{
			//TranslateMessage(&messages); // K��nt�� n�pp�in painalluksia tunnetuksi koodiksi.
			if (messages.message == WM_QUIT)
			{
				isRunning = false;
				wglDeleteContext(hGLRC); // Tuhotaan render�inti sis�lt�.
				break;
			}
			DispatchMessage(&messages);
			SwapBuffers(hDC); // Swapataan buffereita piirtoa varten.
		}
	}

	return (int) messages.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) // Prosessoi viestej� ikkunalle.
{ 
	//PAINTSTRUCT paint; // Can be used to paint the client area of a window owned by that application.
	//HDC displayHandle; // Mihin piirret��n.
	//TCHAR greeting[] = _T("Terve");

	switch (message) {
	//case WM_PAINT:
	//	displayHandle = BeginPaint(hWnd, &paint);
	//	TextOut(displayHandle, 5, 5, greeting, _tcslen(greeting));
	//	EndPaint(hWnd, &paint);
	//	break;
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

	if (GLEW_VERSION_2_1) // Tarkastetaan onko 2.1 k�yt�ss�.
		std::cout << "OpenGL 2.1 supported." << std::endl;
	else
	{
		std::cout << "OpenGL 2.1 not supported." << std::endl;
		return false;
	}
	return true;
}

 /*bool InitGL(GLvoid)
{
	glShadeModel(GL_SMOOTH); // Enables smooth shading.
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Musta tausta.
	glClearDepth(1.0f); // Syvyys bufferin setup.
	//glEnable(GL_DEPTH_TEST); // Syvyys testej�.
	//glDepthFunc(GL_LEQUAL);
	return true;
}

bool DrawGLScene(GLvoid)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clearaa ruudun ja syvyys bufferin.
	glLoadIdentity(); // Resettaa modelview matrixin.
	return true;
}

bool CreateGLWindow()
{
	GLuint		PixelFormat;
} */