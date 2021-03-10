#ifndef CAMERA_H
#define CAMERA_H

#include "utility.h"
#include "input.h"


const float YAW         = 90.0f;
const float PITCH       =  0.0f;
const float SPEED       =  15.0f;
const float SENSITIVITY =  15.0f;

struct Camera
{
    Vec3 position;
    Vec3 front;
    Vec3 worldFront;
    Vec3 up; 
    Vec3 right;
    Vec3 worldUp;
    float yaw;
    float pitch;
    float movementSpeed;
    float mouseSensitivity;
};

void InitCamera(Camera* camera, Vec3 position, Vec3 up, float yaw = YAW, float pitch = PITCH);
Matrix GetCameraViewMatrix(Camera* camera);
void ProcessKeyboardInput(Camera* camera, Keyboard* keyboard, float deltaTime);
void ProcessMouseMovement(Camera* camera, float xoffset, float yoffset, float deltaTime);
void ProcessControllerMovement(Camera* camera, Controller* controller, float deltaTime);
void UpdateCameraVectors(Camera* camera);

#endif
