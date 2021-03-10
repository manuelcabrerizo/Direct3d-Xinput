#include "camera.h"
#include "stdio.h"
void InitCamera(Camera* camera, Vec3 position, Vec3 up, float yaw, float pitch)
{
    camera->position         = position;
    camera->front            = {0.0f, 0.0f, -1.0f};
    camera->worldFront       = {0.0f, 0.0f, -1.0f}; 
    camera->worldUp          = up;
    camera->yaw              = yaw;
    camera->pitch            = pitch;
    camera->movementSpeed    = SPEED;
    camera->mouseSensitivity = SENSITIVITY;
    UpdateCameraVectors(camera);
}

Matrix GetCameraViewMatrix(Camera* camera)
{
    return GetViewMatrix(camera->position, Vec3Add(camera->position, camera->front), camera->up);
}

void ProcessKeyboardInput(Camera* camera, Keyboard* keyboard, float deltaTime)
{
    float velocity = camera->movementSpeed * deltaTime;
    if(KeyDown(keyboard, 'W'))
    {
        camera->position = Vec3Add(camera->position, Vec3MultScalar(camera->worldFront, velocity)); 
    }
    if(KeyDown(keyboard, 'S'))
    {
        camera->position = Vec3Sub(camera->position, Vec3MultScalar(camera->worldFront, velocity));
    }
    if(KeyDown(keyboard, 'D'))
    {
        camera->position = Vec3Sub(camera->position, Vec3MultScalar(camera->right, velocity));
    }
    if(KeyDown(keyboard, 'A'))
    {
        camera->position = Vec3Add(camera->position, Vec3MultScalar(camera->right, velocity));
    }
    if(KeyDown(keyboard, 'R'))
    {
        camera->position = Vec3Add(camera->position, Vec3MultScalar(camera->worldUp, velocity));
    }
    if(KeyDown(keyboard, 'F'))
    {
        camera->position = Vec3Sub(camera->position, Vec3MultScalar(camera->worldUp, velocity));
    }

}

void ProcessMouseMovement(Camera* camera, float xoffset, float yoffset, float deltaTime)
{
    xoffset *= camera->mouseSensitivity;
    yoffset *= camera->mouseSensitivity;

    camera->yaw   -= xoffset * deltaTime;
    camera->pitch -= yoffset * deltaTime;

    if(camera->pitch > 89.0f)
       camera->pitch = 89.0f;
    if(camera->pitch < -89.0f)
       camera->pitch = -89.0f; 

    UpdateCameraVectors(camera);
}

void ProcessControllerMovement(Camera* camera, Controller* controller, float deltaTime)
{
    if(CheckForConectedControllers())
    {
        ProcessXinput(controller);

        float xLOffset = (controller->thumbLX / 4096) * 2;
        float yLOffset = (controller->thumbLY / 4096) * 2;
        float velocity = camera->movementSpeed * deltaTime;

        camera->position = Vec3Add(camera->position, Vec3MultScalar(camera->worldFront, yLOffset * deltaTime)); 
        camera->position = Vec3Sub(camera->position, Vec3MultScalar(camera->right, xLOffset * deltaTime));
        if(controller->up)
        {
            camera->position = Vec3Add(camera->position, Vec3MultScalar(camera->worldUp, velocity));
        }
        if(controller->down)
        {
            camera->position = Vec3Sub(camera->position, Vec3MultScalar(camera->worldUp, velocity));
        }

        float xROffset = controller->thumbRX / 4096;
        float yROffset = controller->thumbRY / 4096;

        xROffset *= camera->mouseSensitivity;
        yROffset *= camera->mouseSensitivity;

        camera->yaw   -= xROffset * deltaTime;
        camera->pitch += yROffset * deltaTime;

        if(camera->pitch > 89.0f)
           camera->pitch = 89.0f;
        if(camera->pitch < -89.0f)
           camera->pitch = -89.0f; 
        UpdateCameraVectors(camera);
    }
}

void UpdateCameraVectors(Camera* camera)
{

    Vec3 worldfront;
    worldfront.x = cosf(ToRadians(camera->yaw)) * cosf(ToRadians(camera->pitch));
    worldfront.z = sinf(ToRadians(camera->yaw)) * cosf(ToRadians(camera->pitch));
    camera->worldFront = NormalizaVec3(worldfront);

    Vec3 front;
    front.x = cosf(ToRadians(camera->yaw)) * cosf(ToRadians(camera->pitch));
    front.y = sinf(ToRadians(camera->pitch));
    front.z = sinf(ToRadians(camera->yaw)) * cosf(ToRadians(camera->pitch));
    camera->front = NormalizaVec3(front);
    camera->right = NormalizaVec3(Vec3Cross(camera->front, camera->worldUp));
    camera->up    = NormalizaVec3(Vec3Cross(camera->right, camera->front));
}
