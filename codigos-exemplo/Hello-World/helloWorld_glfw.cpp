#include <GLFW/glfw3.h>

/*
 * Programa 'Olá mundo' de OpenGL clássico.
 * Desenha um triângulo vermelho sobre um fundo branco.
 */


//É uma boa prática criar uma função para agrupar configurações iniciais do OpenGL para o desenho a ser feito
void inicio(){
    glClearColor(1.0, 1.0, 1.0, 1.0); //indica qual cor será usada para limpar o frame buffer (normalmente usa uma cor de background)
}


//Função que será usada para desenhar o conteúdo no Frame Buffer
void desenha(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1,3,-1,2,-1,1);
    /*
    glColor3f(0.0, 1.0, 1.0);
    
    glBegin(GL_TRIANGLES);       //instrução que indica o tipo de primitiva que será desenhada. Nesse caso, triangulos.
        glVertex2f( 0.0,  0.0);  //instrução que envia as coordenadas dos vértices do triangulo
        glVertex2f(-1.0, -1.0);  
        glVertex2f( 0.0, -1.0);
    glEnd();
    */
    glColor3f(1.0, 1.0, 0.0);    //instrução que altera a cor corrente. glColor3f(R,G,B). R = vermelho, G = verde, B = azul
    glBegin(GL_TRIANGLES);       //instrução que indica o tipo de primitiva que será desenhada. Nesse caso, triangulos.
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f( 0.0,  0.0);  //instrução que envia as coordenadas dos vértices do triangulo
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f( 2.0,  0.0); 
        glColor3f(0.0, 0.0, 1.0);
        glVertex2f( 1.0,  1.0);
    glEnd();
    
    glFlush();  //Todas as instruções anteriores apenas indicaram o que deve ser feito. Essa é a ordem pra GPU redesenhar com as informações enviadas
}

int main(int argc, char** argv){
    // Configuração da criação da janela com GLFW
    glfwInit();

    GLFWwindow* win = glfwCreateWindow(800, 600, "Hello World", NULL, NULL); // Criação da janela 
    glfwMakeContextCurrent(win);

    inicio(); 
 
    while(!glfwWindowShouldClose(win)) {
        glfwPollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT); //sempre antes de desenhar qualquer coisa, deve-se limpar o Frame Buffer
    
        desenha();

        glfwSwapBuffers(win);
    }

    glfwTerminate();
    return 0;
}
