#include <GLFW/glfw3.h>
#include <iostream>

// Estrutura representando um vetor 2D
struct vec2
{
	float x;
	float y;
	bool selected = false;
};

vec2 pontoBranco	= { 6.f, 5.f };
vec2 pontoAzul		= { 3.f, 3.f };

// Uma Matrix de projeção ortográfica configurada manualmente
// Referência: https://www.scratchapixel.com/lessons/3d-basic-rendering/perspective-and-orthographic-projection-matrix/orthographic-projection-matrix.html
struct mat4
{
	float left, right, bottom, top, zNear, zFar;

	const GLfloat proj[4][4] = {
		2.f/(right-left), 0, 0, 0,
		
		0, 2.f/(top-bottom), 0, 0,
		
		0, 0, 1.f/(zNear-zFar), 0,

		(left + right)/(left - right), (top + bottom)/(bottom - top), zNear/(zNear - zFar), 1
	};
};

mat4 ortho = { -10.f, 10.f, -10.f, 10.f, -1.f, 1.f };

// Variáveis para controle do Mouse
vec2 mousePos;
bool isPressed = false;
GLFWcursor* cursor;

void desenha();

void mouseButton_callback(GLFWwindow* win, int button, int action, int mods);
void cursorPos_callback(GLFWwindow* win, double xpos, double ypos);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	GLFWwindow* win = glfwCreateWindow(700, 700, "Vetores", NULL, NULL);
	glfwMakeContextCurrent(win);

	// Inicialização
	glClearColor(27.f/255, 27.f/255, 27.f/255, 1.0);
	glPointSize(5);
	glLineWidth(2);

	// funções de callback do GLFW (utilizadas para reconhecer movimentação e click do mouse)
	glfwSetMouseButtonCallback(win, mouseButton_callback);
	glfwSetCursorPosCallback(win, cursorPos_callback);

	while (!glfwWindowShouldClose(win))
	{
		glfwPollEvents();

		glClear(GL_COLOR_BUFFER_BIT);

		desenha();

		glfwSwapBuffers(win);
	}

}

void desenha()
{
	/* Estamos criando uma matriz de projeção, manipulando o espaço de renderização
	* padrão do OpenGL, que é de -1 até 1, a matriz nos permitirá trabalhar com um 
	* sistema de coordenadas configurado por nós.
	*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// O comando abaixo envia nossa matrix para o OpenGL
	// É o mesmo processo que glOrtho está fazendo, só que manualmente
	glLoadMatrixf((ortho.proj[0]));
	//glOrtho(-10, 10, -10, 10, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Sistema de coordenadas
	glBegin(GL_LINES);
		// Eixo X
		glColor3f(0.6f, 0.0f, 0.0f);
		glVertex3f(-10.f, 0.0f, 0.0f);
		glVertex3f(10.f, 0.0f, 0.0f);
		
		// Eixo Y
		glColor3f(0.0f, 0.6f, 0.0f);
		glVertex3f(0.f, 10.0f, 0.0f);
		glVertex3f(0.f, -10.0f, 0.0f);
	glEnd();

	// Os dois pontos
	glBegin(GL_POINTS);
		// Ponto branco
		glColor3f(255.f / 255, 245.f / 255, 245.f / 255);
		glVertex3f(pontoBranco.x, pontoBranco.y, 0.0f);

		// Ponto Azul
		glColor3f(18.f / 255, 156.f / 255, 228.f / 255);
		glVertex3f(pontoAzul.x, pontoAzul.y, 0.0f);
	glEnd();

	// O vetor que representa a trajetória do ponto Azul até o Branco
	// vetorAB = B - A
	vec2 vetorAB = {
		pontoBranco.x - pontoAzul.x, // Coordenada x
		pontoBranco.y - pontoAzul.y // Coordenada y
	};

	glBegin(GL_LINES);
	glColor3f(144.f / 255, 212.f / 255, 255.f / 255);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(vetorAB.x, vetorAB.y, 0.f);
	glEnd();
}


/* !!! As funções abaixo são para poder utilizar o Mouse para arrastar os pontos no programa !!! */

// Código para reconhecer o click do mouse no ponto e arrastar ele para onde quiser.
void mouseButton_callback(GLFWwindow* win, int button, int action, int mods)
{
	float offset = 0.1f;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && !isPressed)
	{
		isPressed = true;

		// ponto Branco
		if (mousePos.x >= pontoBranco.x - offset && mousePos.x <= pontoBranco.x + offset)
		{
			if (mousePos.y >= pontoBranco.y - offset && mousePos.y <= pontoBranco.y + offset)
			{
				pontoBranco.selected = true;
				cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
				glfwSetCursor(win, cursor);
			}
		}
		// ponto Azul
		else if (mousePos.x >= pontoAzul.x - offset && mousePos.x <= pontoAzul.x + offset)
		{
			if (mousePos.y >= pontoAzul.y - offset && mousePos.y <= pontoAzul.y + offset)
			{
				pontoAzul.selected = true;
				cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
				glfwSetCursor(win, cursor);
			}
		}
	}
	
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		isPressed = false;
		pontoBranco.selected = false;
		pontoAzul.selected = false;
		cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		glfwSetCursor(win, cursor);
	}

}

void cursorPos_callback(GLFWwindow* win, double xpos, double ypos)
{
	// Este método contém calculos para transformação manual de espaços de coordenadas
	// Referência: https://antongerdelan.net/opengl/raycasting.html

	int width, height;
	glfwGetWindowSize(win, &width, &height);

	// Coordenadas em Screen Space
	mousePos = { (float)xpos, (float)ypos };

	// Transformadas para Clip Space (No OpenGL é de -1 até 1)
	mousePos.x = (2.0f * mousePos.x) / width - 1.f;
	mousePos.y = 1.0f - (2.0f * mousePos.y) / height;

	// Como nossa projeção é Ortográfica, basta escalarmos nosso vetor do Clip space para espaço global	
	mousePos.x *= 10;
	mousePos.y *= 10;

	if (pontoBranco.selected)
	{
		pontoBranco.x = mousePos.x;
		pontoBranco.y = mousePos.y;
	}
	else if (pontoAzul.selected)
	{
		pontoAzul.x = mousePos.x;
		pontoAzul.y = mousePos.y;
	}
}








