# Definição da versão mínima requerida
cmake_minimum_required (VERSION 3.16) 

project(Vetor) # O nome do seu projeto

# Vai agrupar todos os caminhos dos seus arquivos .cpp em uma variável chamada SOURCES
file(GLOB SOURCES "*.cpp") 

# O nome do seu projeto e os caminhos de todos os executáveis a serem buildados, no caso 
# todos na variável SOURCES
add_executable(Vetor ${SOURCES}) 

# FetchContent é uma propriedade do CMake que permite baixar da internet as dependências 
# que você precisa, no Linux é bem fácil de instalar, porém para quem usa Windows é mais
# complicado de fazer o CMake reconhecer a biblioteca, então FetchContent facilita isso
# baixando em uma pasta _deps na sua pasta build. Não é o ideal mas agiliza seu processo
# de build e permite focar no código mesmo.
include(FetchContent)

FetchContent_Declare(
    glfw  
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3-stable
)
FetchContent_GetProperties(glfw)
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
FetchContent_MakeAvailable(glfw)

# find_package é um comando que vai buscar a instalação das requeridas bibliotecas nas suas 
# variáveis de ambiente, ou na pasta de libs no Linux
find_package(OpenGL REQUIRED) 

target_include_directories(Vetor 
    PUBLIC
        ${glfw_SOURCE_DIR}/include
)

# Linkagem das bibliotecas no seu executável
target_link_libraries(Vetor glfw ${OPENGL_LIBRARIES})