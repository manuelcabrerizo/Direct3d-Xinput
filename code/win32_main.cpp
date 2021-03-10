///////////////////////////////
/// FRAGMENT_SHADER EXAMPLE ///
///////////////////////////////
#include "d3d9.h"
#include "d3dx9.h"
#include "stdint.h"
#include "mesh.h"
#include "camera.h"
#include "stdio.h" 

#define global_variable static
#define WNDWIDTH 1000
#define WNDHEIGHT 800


// vertex_shader
IDirect3DVertexShader9* diffuseShader = 0;
ID3DXConstantTable* diffuseConstTable = 0;
D3DXHANDLE WorldMatrixHandle = 0;
D3DXHANDLE ViewMatrixHandle  = 0;
D3DXHANDLE ProjMatrixHandle  = 0;
D3DXHANDLE LightDirectionHandle = 0;
Vec4 lightDir = {1.0f, 0.0f, 0.0f, 1.0f};

// fragment_shader
IDirect3DPixelShader9* MultiTexPS = 0;
ID3DXConstantTable* MultiTexCT    = 0;
D3DXHANDLE BaseTexHandle        = 0;
D3DXCONSTANT_DESC BaseTexDesc;

struct MultiTexVertex
{
    float x, y, z;
    float u0, v0;
    float u1, v1;
    float u2, v2;
    static const DWORD FVF = D3DFVF_XYZ | D3DFVF_TEX3;
};

global_variable Mesh mesh;
global_variable BOOL appRunnig;
global_variable Mouse mouseHandler;
global_variable Keyboard keyboardHandler;
global_variable Camera camera;
global_variable Controller controller;

void SetUp(IDirect3DDevice9* device)
{
    // compile VERTEX_SHADER:
    HRESULT hr = 0;
    ID3DXBuffer* shader      = 0;
    ID3DXBuffer* errorBuffer = 0;
    hr = D3DXCompileShaderFromFile(
            "./code/shader.vert",
            0,
            0,
            "Main",
            "vs_1_1",
            D3DXSHADER_DEBUG | D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY,
            &shader,
            &errorBuffer,
            &diffuseConstTable);
    if(errorBuffer)
    {
        OutputDebugString("ERROR: something whet realy BAD...");
        OutputDebugString((char*)errorBuffer->GetBufferPointer());
    }
    if(FAILED(hr))
    {
        OutputDebugString("ERROR: error compiling VERTEX SHADER\n");
    } 
    // create shader
    hr = device->CreateVertexShader(
            (DWORD*)shader->GetBufferPointer(),
            &diffuseShader);
    if(FAILED(hr))
    {
        OutputDebugString("ERROR: error creating VERTEX SHADER\n");
    } 
    shader->Release();
    // get handles
    WorldMatrixHandle = diffuseConstTable->GetConstantByName(0, "WorldMatrix");
    ViewMatrixHandle  = diffuseConstTable->GetConstantByName(0, "ViewMatrix"); 
    ProjMatrixHandle  = diffuseConstTable->GetConstantByName(0, "ProjMatrix");
    LightDirectionHandle = diffuseConstTable->GetConstantByName(0, "lightDirection");
    diffuseConstTable->SetDefaults(device);

   // compile FRAGMENT_SHADER
    ID3DXBuffer* fragShader      = 0;
    ID3DXBuffer* fragErrorBuffer = 0;
    hr = D3DXCompileShaderFromFile(
            "./code/fragmentShader.frag",
            0,
            0,
            "Main",
            "ps_1_1",
            D3DXSHADER_DEBUG | D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY,
            &fragShader,
            &fragErrorBuffer,
            &MultiTexCT);
    if(fragErrorBuffer)
    {
        OutputDebugString("ERROR: something whet realy BAD...");
        OutputDebugString((char*)fragErrorBuffer->GetBufferPointer());
    }
    if(FAILED(hr))
    {
        OutputDebugString("ERROR: error compiling FRAGMENT SHADER\n");
    }

    hr = device->CreatePixelShader(
            (DWORD*)fragShader->GetBufferPointer(),
            &MultiTexPS);
    if(FAILED(hr))
    {
        OutputDebugString("ERROR: error creating FRAGMENT SHADER\n");
    } 
    fragShader->Release();

    //disable light
    device->SetRenderState(D3DRS_LIGHTING, false);

    // get handles
    BaseTexHandle = MultiTexCT->GetConstantByName(0, "BaseTex");
    MultiTexCT->SetDefaults(device);
    // set constant descriptions
    UINT count;
    MultiTexCT->GetConstantDesc(
                    BaseTexHandle,
                    &BaseTexDesc,
                    &count);


    // compute projection matrix
    Matrix proj = GetProjectionMatrix(D3DX_PI * 45 / 180, (float)WNDWIDTH / (float)WNDHEIGHT, 1.0f, 100.0f);
    diffuseConstTable->SetMatrix(device, ProjMatrixHandle, &GetD3DXMatrix(proj));

    Vec3 position = {0.0f, 0.0f, -5.0f};
    Vec3 up = {0.0f, 1.0f, 0.0f};
    InitCamera(&camera, position, up); 
}

void Update(IDirect3DDevice9* device, float deltaTime)
{
    // compute view matrix
    Matrix view = GetCameraViewMatrix(&camera);
    diffuseConstTable->SetMatrix(device, ViewMatrixHandle, &GetD3DXMatrix(view));

    ProcessKeyboardInput(&camera, &keyboardHandler, deltaTime);
    ProcessMouseMovement(&camera, mouseHandler.mouseRPos.x, mouseHandler.mouseRPos.y, deltaTime);
    ProcessControllerMovement(&camera, &controller, deltaTime);
    mouseHandler.mouseRPos.x = 0;
    mouseHandler.mouseRPos.y = 0;

    float angle = 2.0f * deltaTime;
    lightDir = Vec4RotateY(lightDir, angle);
    diffuseConstTable->SetVector(device, LightDirectionHandle, &GetD3DXVector(lightDir));
}

void Render(IDirect3DDevice9* device, float deltaTime)
{
    device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xff000055, 1.0f, 0);
    device->BeginScene();

    Matrix scale     = GetIdentity();
    Matrix rotation  = GetIdentity();
    Matrix translate = GetIdentity();
    Matrix world     = GetIdentity();

    // rotate the mesh in the y cooord
    static float angle = 0.0f;
    //rotation = MatrixRotationY(angle);
    translate = MatrixTranslation(0.0f, 0.0f, 10.0f);
    scale = MatrixScale(4.0f, 4.0f, 4.0f);
    angle += 1 * deltaTime;

    device->SetVertexShader(diffuseShader);
    device->SetPixelShader(MultiTexPS);
    world = MatrixMultiply(rotation, scale);
    world = MatrixMultiply(world, translate); 
    diffuseConstTable->SetMatrix(device, WorldMatrixHandle, &GetD3DXMatrix(world)); 
    device->SetFVF(MeshVertex::FVF);
    device->SetTexture(BaseTexDesc.RegisterIndex, mesh.tex);
    device->SetStreamSource(0, mesh.D3DvertexBuffer, 0, sizeof(MeshVertex));    
    device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, mesh.numIndex);

    device->EndScene();
    device->Present(0, 0, 0, 0);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    LRESULT result;
    switch(Msg)
    {
        case WM_CLOSE:
        {
            appRunnig = FALSE;
        }break;
        case WM_DESTROY:
        {
            appRunnig = FALSE;
        }break;
        case WM_KEYUP:
        {
            uint32_t scancode = wParam;
            SetKeyUp(&keyboardHandler, scancode);
        }break;
        case WM_KEYDOWN:
        {
            uint32_t scancode = wParam;
            SetKeyDown(&keyboardHandler, scancode);
        }break;
        case WM_MOUSEMOVE:
        {
            POINT cursorPos;
            GetCursorPos(&cursorPos);
            mouseHandler.mouseRPos.x += cursorPos.x - mouseHandler.mouseDPos.x;
            mouseHandler.mouseRPos.y += cursorPos.y - mouseHandler.mouseDPos.y;            
            SetCursorPos(mouseHandler.mouseDPos.x, mouseHandler.mouseDPos.y);
        }break;
        case WM_MOVE:
        {
            RECT windowRect;
            GetClientRect(hwnd, &windowRect);
            int x      = (int)(short)LOWORD(lParam);
            int y      = (int)(short)HIWORD(lParam);
            int width  = windowRect.right - windowRect.left;
            int height = windowRect.bottom - windowRect.top;
            mouseHandler.mouseDPos.x = x + width  / 2;
            mouseHandler.mouseDPos.y = y + height / 2;
        }break;
        default:
        {
            result = DefWindowProc(hwnd, Msg, wParam, lParam); 
        }break;
    }
    return(result);
}

int InitializeD3D9(IDirect3DDevice9** device, HWND hWnd)
{
    HRESULT hr               = 0;
    IDirect3D9* d3d          = 0;
    int vp                   = 0;
    if((d3d = Direct3DCreate9(D3D_SDK_VERSION)) == NULL)
    {
        OutputDebugString("FAILED creating D3D\n");
        return(1);
    }
    D3DCAPS9 caps;
    d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
    if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
    {
        vp = D3DCREATE_HARDWARE_VERTEXPROCESSING; 
    }
    else
    {
        vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
    }
    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferWidth            = WNDWIDTH;
	d3dpp.BackBufferHeight           = WNDHEIGHT;
	d3dpp.BackBufferFormat           = D3DFMT_A8R8G8B8;
	d3dpp.BackBufferCount            = 1;
	d3dpp.MultiSampleType            = D3DMULTISAMPLE_NONE;
	d3dpp.MultiSampleQuality         = 0;
	d3dpp.SwapEffect                 = D3DSWAPEFFECT_DISCARD; 
	d3dpp.hDeviceWindow              = hWnd;
	d3dpp.Windowed                   = true;
	d3dpp.EnableAutoDepthStencil     = true; 
	d3dpp.AutoDepthStencilFormat     = D3DFMT_D24S8;
	d3dpp.Flags                      = 0;
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_ONE;    
    hr = d3d->CreateDevice(D3DADAPTER_DEFAULT,
                           D3DDEVTYPE_HAL,
                           hWnd,
                           vp,
                           &d3dpp,
                           device);
    if(FAILED(hr))
    {
        OutputDebugString("FAILED creating d3d_device\n");
    } 
    d3d->Release();
    if(device != NULL)
    {
        OutputDebugString("SUCCEED creating d3d_device\n");
        return(0);
    }
    return(1);
}

int WinMain(HINSTANCE hInstance,
            HINSTANCE hPrevInstance,
            LPSTR     lpCmdLine,
            int       nCmdShow)
{
    IDirect3DDevice9* device = 0;

    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance; 
    wc.lpszClassName = "FrameClass";

    if(!RegisterClassA(&wc))
    {
        OutputDebugString("FAILED register class\n");
        return(1);    
    }

    RECT wr;
	wr.left = 0;
	wr.right = WNDWIDTH;
	wr.top = 0;
	wr.bottom = WNDHEIGHT;
	AdjustWindowRect(&wr, WS_OVERLAPPED, FALSE);

    HWND hWnd = CreateWindowA("FrameClass", "Role3DGame",
                  WS_OVERLAPPEDWINDOW,
                  0, 0,
                  wr.right - wr.left, wr.bottom - wr.top,
                  NULL, NULL,
                  hInstance,
                  NULL);

    LARGE_INTEGER perfCountFrequency;
    QueryPerformanceFrequency(&perfCountFrequency);
    uint64_t frequency = (uint64_t)perfCountFrequency.QuadPart;

    if(hWnd)
    {
        appRunnig = TRUE;
        ShowWindow(hWnd, SW_SHOW); 
        ShowCursor(false); 
        mouseHandler.mouseDPos.x = WNDWIDTH  / 2;
        mouseHandler.mouseDPos.y = WNDHEIGHT / 2;
        SetCursorPos(mouseHandler.mouseDPos.x, mouseHandler.mouseDPos.y);

        if(InitializeD3D9(&device, hWnd) == 0)
        {
            OutputDebugString("D3D9 INITIALIZED\n");
            if(device == NULL)
            {
                OutputDebugString("device is NULL ptr\n");
            }
            else
            {
                SetUp(device);
                LoadOBJFile(device, &mesh, "./data/crab.obj", "./data/crab.png");
                LARGE_INTEGER lastCounter;
                QueryPerformanceCounter(&lastCounter);
                while(appRunnig == TRUE)
                {
                    MSG  msg;
                    BOOL bRet; 
                    static float lastTime = (float)timeGetTime();
                    if(PeekMessageA(&msg, hWnd, 0, 0, PM_REMOVE))
                    {            
                        TranslateMessage(&msg); 
                        DispatchMessage(&msg); 
                    }
                    else
                    {
                        LARGE_INTEGER endCounter;
                        QueryPerformanceCounter(&endCounter);
                        uint64_t counterElapsed =  endCounter.QuadPart - lastCounter.QuadPart; 
                        float deltaTime = (counterElapsed / (float)frequency);

                        Update(device, deltaTime);
                        Render(device, deltaTime);

                        lastCounter = endCounter;          
                    }
                }
            }
        }

    }
    else
    {
        return(1);
    }
    MultiTexPS->Release();
    MultiTexCT->Release();
    diffuseShader->Release();
    diffuseConstTable->Release();
    return 0;
}
