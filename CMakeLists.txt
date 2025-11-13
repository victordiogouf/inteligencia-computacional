cmake_minimum_required(VERSION 3.14)

# nome do projeto
project(agendamentoTarefas)

# Definindo o padrão de compilação
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configura o arquivo de cabeçalho das constantes que serão usadas no projeto
configure_file(${PROJECT_SOURCE_DIR}/config.h.in config.h)

# Mapeia os arquivos de cabeçalho para o cmake encontrar no momento de compilação
include_directories(${PROJECT_NAME} include)
# include_directories(${PROJECT_NAME} include/templates)
include_directories(${PROJECT_BINARY_DIR})

#adiciona o subdiretório src
add_subdirectory(src)

# Cria um executável
add_executable(${PROJECT_NAME} 
  main.cpp
)

# Adiciona os arquivos de código fonte biblioteca
target_link_libraries(${PROJECT_NAME} libraryAgendamentoTarefas)