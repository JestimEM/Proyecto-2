CXX = g++
CXXFLAGS = -std=c++17 -Wall

# Directorios
SRC_DIR = src
OBJ_DIR = build

# Archivos objeto
OBJS = $(OBJ_DIR)/main.o $(OBJ_DIR)/Map.o $(OBJ_DIR)/Tank.o $(OBJ_DIR)/Pathfinding.o $(OBJ_DIR)/Bullet.o  # Agrega Bullet.o

# Nombre del ejecutable
EXEC = TankAttack

# Regla predeterminada
all: $(EXEC)

# Cómo construir el ejecutable final
$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system

# Cómo construir cada archivo objeto de los .cpp en el directorio src
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Para correr el programa
run: all
	./$(EXEC)

# Limpiar archivos compilados
clean:
	rm -rf $(OBJ_DIR) $(EXEC)

# Dependencias de los archivos
$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/Map.h $(SRC_DIR)/Tank.h $(SRC_DIR)/Pathfinding.h $(SRC_DIR)/Bullet.h  # Incluye Bullet.h
$(OBJ_DIR)/Map.o: $(SRC_DIR)/Map.cpp $(SRC_DIR)/Map.h
$(OBJ_DIR)/Tank.o: $(SRC_DIR)/Tank.cpp $(SRC_DIR)/Tank.h
$(OBJ_DIR)/Pathfinding.o: $(SRC_DIR)/Pathfinding.cpp $(SRC_DIR)/Pathfinding.h
$(OBJ_DIR)/Bullet.o: $(SRC_DIR)/Bullet.cpp $(SRC_DIR)/Bullet.h  # Agrega Bullet.cpp y Bullet.h
