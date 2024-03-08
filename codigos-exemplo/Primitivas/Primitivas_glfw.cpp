#include <GLFW/glfw3.h>
#include <math.h>
/*
 * Programa 'Primitivas' de OpenGL clássico.
 * Desenha diversas primitivas geométricas presentes em OpenGL
 * Comentários e código utilizando GLUT de Rafael Ivo
 */

//É uma boa prática criar uma função para agrupar configurações iniciais do OpenGL para o desenho a ser feito
void inicio(){
    glClearColor(1.0, 1.0, 1.0, 1.0); //indica qual cor será usada para limpar o frame buffer (será a cor de fundo)
    glPointSize(5); //altera o tamanho de pontos (por padrão, o tamanho é de 1 pixel)
    glLineWidth(3); //altera a largura de segmentos de reta (por padrão, a largura é de 1 pixel)
}

//função que desenha várias primitivas diferentes para exemplificar seu uso
void primitivas(){
    glBegin(GL_POINTS); //pontos
        glVertex2f( 1, 1);
        glVertex2f( 4, 1);
        glVertex2f( 4, 4);
        glVertex2f( 1, 4);
    glEnd();
    
    glBegin(GL_LINES); //a cada dois pontos, conecte-os em segmentos de reta
        glVertex2f( 5, 1);
        glVertex2f( 8, 1);
        glVertex2f( 8, 4);
        glVertex2f( 5, 4);
    glEnd();
    
    glBegin(GL_LINE_STRIP); //conecte uma sequencia de pontos em segmentos de reta
        glVertex2f( 9, 1);
        glVertex2f(12, 1);
        glVertex2f(12, 4);
        glVertex2f( 9, 4);
    glEnd();
    
    glBegin(GL_LINE_LOOP); //conecte uma sequencia de pontos em segmentos de reta e o ultimo ponto com o primeiro
        glVertex2f(13, 1);
        glVertex2f(16, 1);
        glVertex2f(16, 4);
        glVertex2f(13, 4);
    glEnd();
    
    glBegin(GL_QUADS); //a cada quatro pontos, conecte-os em quadriláteros
        glVertex2f( 1, 5);
        glVertex2f( 4, 5);
        glVertex2f( 4, 8);
        glVertex2f( 1, 8);
    glEnd();
    
    glBegin(GL_TRIANGLES); //a cada tres pontos, conecte-os em triangulos
        glVertex2f( 5, 5);
        glVertex2f( 8, 5);
        glVertex2f( 5, 8);
        glVertex2f( 5, 8);
        glVertex2f( 8, 5);
        glVertex2f( 8, 8);
    glEnd();
    
    glBegin(GL_TRIANGLE_STRIP); //cada novo ponto é conectado aos dois ultimos formando triangulos
        glVertex2f( 9, 5);
        glVertex2f( 9, 8);
        glVertex2f(10, 5);
        glVertex2f(10, 8);
        glVertex2f(11, 5);
        glVertex2f(11, 8);
        glVertex2f(12, 5);
        glVertex2f(12, 8);
    glEnd();
    
    glBegin(GL_QUAD_STRIP); //cada dois novos pontos são conectados aos dois ultimos formando quadriláteros
        glVertex2f(13, 5);
        glVertex2f(13, 8);
        glVertex2f(14, 5);
        glVertex2f(14, 8);
        glVertex2f(15, 5);
        glVertex2f(15, 8);
        glVertex2f(16, 5);
        glVertex2f(16, 8);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN); //o primeiro ponto é conectado a todos os demais formando triangulos
        glVertex2f(2.5,10.5);
        glVertex2f(  1,  9);
        glVertex2f(  4,  9);
        glVertex2f(  4, 12);
        glVertex2f(  1, 12);
        glVertex2f(  1,  9);
    glEnd();
    
    glBegin(GL_POLYGON); //poligono de vários lados (deve ser evitado)
        glVertex2f( 5,10);
        glVertex2f( 6, 9);
        glVertex2f( 7, 9);
        glVertex2f( 8,10);
        glVertex2f( 8,11);
        glVertex2f( 7,12);
        glVertex2f( 6,12);
        glVertex2f( 5,11);
    glEnd();
    
    glBegin(GL_QUADS); //quadriláteros e poligonos com a ordem dos vértices incorreta pode levar a esse tipo de erro
        glVertex2f( 9, 9);
        glVertex2f(12, 9);
        glVertex2f( 9,12);
        glVertex2f(12,12);
    glEnd();
    
    glBegin(GL_TRIANGLE_FAN); //GL_POLYGON pode ser substituido por GL_TRIANGLE_FAN
        glVertex2f(13,10);
        glVertex2f(14, 9);
        glVertex2f(15, 9);
        glVertex2f(16,10);
        glVertex2f(16,11);
        glVertex2f(15,12);
        glVertex2f(14,12);
        glVertex2f(13,11);
    glEnd();
}

//Função que será usada para desenhar o conteudo no frame buffer
void desenha(){
    //por padrão, o OpenGL exibe apenas as coisas desenhadas dentro do intervalo -1 e 1 nas coordenadas x e y
    //os comandos abaixo alteram esse comportamento padrão de visualização (será explicado em mais detalhes futuramente)
    glMatrixMode(GL_PROJECTION); 
    glLoadIdentity();
    glOrtho(0,20,0,20,-1,1);    //glOrtho(xmin,xmax,ymin,ymax,zmin,zmax) = alterando a área de visualização (tudo entre 0 e 20 nas coordenadas x e y será visualizado)
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();
    
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); //alterando para modo de preenchimento (por padrão já vem ativado)
    glColor3f(1.0, 0.0, 0.0);                    //cor de preenchimento vermelha  
    primitivas();                                //chamando a função que desenha aquele conjunto de primitivas

    glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); //alterando para modo de linhas (usado para mostrar as arestas dos poligonos)
    glColor3f(0.0, 0.0, 0.0);                    //cor das linhas pretas
    primitivas();                                //chamando a função das primitivas novamente (boa prática pra evitar reescrever cÃ³digo)

    glFlush(); //Todas as instruções anteriores apenas indicaram o que deve ser feito. Essa é a ordem pra GPU redesenhar com as informações enviadas
}

int main(int argc, char** argv){

    glfwInit();

    GLFWwindow* win = glfwCreateWindow(500, 500, "Primitivas", NULL, NULL);
    glfwMakeContextCurrent(win);

    inicio();

    while (!glfwWindowShouldClose(win))
    {
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT); //sempre antes de desenhar qualquer coisa, deve-se limpar o frame-buffer

        desenha();

        glfwSwapBuffers(win);
    }

    return 0;
}