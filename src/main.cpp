#include <Windows.h>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include "app/application.hpp"
#include "app/timer.hpp"
#include "app/window.hpp"
#include "gl_funcs.hpp"
#include "errors.hpp"
#include "app/shader.hpp"
#include "app/program.hpp"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR cmdLine, int)
{
    try {

    AllocConsole();
    freopen("CONOUT$", "wb", stdout);
    freopen("CONOUT$", "wb", stderr);
    freopen("CONIN$", "rb", stdin);

    Application app(hInstance);
    app.Init();

    Program program;
    program.LoadShader(GL_VERTEX_SHADER, "test.vert");
    program.LoadShader(GL_FRAGMENT_SHADER, "test.frag");
    const std::vector<Shader> &shaders = program.Shaders();
    for (std::vector<Shader>::const_iterator i = shaders.begin(); i != shaders.end(); i++) {
        std::cout << i->SourceFile() << ": " << i->TypeName() << std::endl;
        std::cout << "Source:" << std::endl << i->Source() << std::endl;
        std::cout << "Compilation status: " << i->CompileStatusString() << std::endl;
        std::cout << "Compilation log:" << std::endl << i->CompileLog() << std::endl;
    }
    program.Link();
    std::cout << "Link status: " << program.LinkStatusString() << std::endl;
    std::cout << "Link log:" << std::endl << program.LinkLog() << std::endl;
    program.Use();

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLfloat data[] = {
        -1.0f, -1.0f,  0.0f,
        1.0f, -1.0f,  0.0f,
        0.0f,  1.0f,  0.0f,
    };
    GLuint verBuf;
    glGenBuffers(1, &verBuf);
    glBindBuffer(GL_ARRAY_BUFFER, verBuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    
    
    bool done = false;
    while (!done) {
        MSG msg;
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                done = true;
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, verBuf);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);

        glDrawArrays(GL_TRIANGLE_FAN, 0, 3);
        glDisableVertexAttribArray(0);

        glFinish();

        SwapBuffers(app.DeviceContext());
    }




    
    
    glDeleteBuffers(1, &verBuf);
    glDeleteVertexArrays(1, &vao);

    

    app.Destroy();


    } catch (WindowsError werr) {
        std::cerr << "Windows error: " << werr.WindowsErrCode() << std::endl;
        std::cerr << "Message: " << werr.WindowsErrMessage() << std::endl;
    } catch (OpenGLError err) {
        std::cerr << "OpenGL error: " << err.OglErrName() << " (" << err.OglErrCode() << ")" << std::endl;
    } catch (Error err) {
        std::cerr << "Error: " << err.ErrCode() << std::endl;
    }

    getchar();
}

