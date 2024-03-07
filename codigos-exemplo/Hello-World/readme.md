# Configuração do ambiente

## Python

Pelo Windows ele pode passar a mensagem ```Microsoft Visual C++ 14.0 or greater is required.```. Então você deve instalar o Microsoft C++ Build Tools

Caso não tenha as dependências do Python para desenvolvimento
```bash
sudo dnf (ou apt-get) install python3-devel
```

Compilador do gcc para C e C++, necessário para buildar o PyOpenGL
```Bash
sudo dnf (ou apt-get) install gcc gcc-c++
```

Bibliotecas do Python para comandos OpenGL
```Bash
pip install PyOpenGL PyOpenGL_accelerate
```

Biblioteca GLFW para criação da janela e manipulação de inputs de teclado e mouse
```Bash
sudo dnf (ou apt-get) install glfw-devel
pip install glfw
```

Então para testar basta executar o HelloWorld e você deve ver um triângulo na tela.
```Bash
python helloWorld_glfw.py
```

## C++

Para C++ vamos utilizar CMake, cmake vai facilitar o processo de build, mais detalhes no arquivo CMakeLists.txt.

Para baixar o CMake. (Pelo Windows basta baixar o instalador do site oficial)
```Bash
sudo apt-get install cmake
```

Para então buildar o projeto, tem que estar no diretório que se encontra o CMakeLists.txt.
```Bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Sobre os comandos acima
Você está criando uma pasta de build, passando para ela e executando ```cmake ..``` para gerar os arquivos de build do cmake nesta pasta, ```cmake --build .``` vai então gerar seu executável nesta pasta.
 
E então pode executar o arquivo final. Se estiver no Windows o executável estará em build/Debug
```Bash
./Hello
```

