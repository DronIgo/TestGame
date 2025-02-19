#pragma once
#include "Graphics/Objects/VertexArray.h"
#include "Graphics/Objects/Camera.h"

Camera* getCamera();

void initGLStates();
void initGraphics();
void initShaders();

void render();