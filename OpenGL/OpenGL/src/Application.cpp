#include<iostream>
#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<string>
#include<fstream>
#include<sstream>

struct ShaderProgramSource {
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);//�ж��ļ��Ƿ��ܴ�
    enum class Shadertype
    {
		NONE = -1,VERTEX = 0,FRAGMENT = 1
    };  

    std::string line;
    std::stringstream ss[2];

    Shadertype type = Shadertype::NONE;
    while (getline(stream, line))
    {
        if (line.find("#shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
            {
                type = Shadertype::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos)
            {
                type = Shadertype::FRAGMENT;
            }
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }
    return { ss[0].str(),ss[1].str() };
}


static unsigned int  CompileShader(unsigned int type, const std::string& source) {
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();

    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_COMPILE_STATUS, &length);
        char* msg = (char*)_malloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, msg);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << msg << std::endl;
        glDeleteShader(id); // ɾ����ɫ��
        return 0;
    }
    return id;

}

static int CreateShader(const std::string& vertexShader,const std::string & fragmentShader) {
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program); /* ���ӳ��� */
    glValidateProgram(program); /* ��֤ */
    /* ɾ����ɫ�� */
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;


}

    int main(void)
    {
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            return -1;
        
        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return -1;
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);


        GLenum err = glewInit();
        if (GLEW_OK != err) {
            std::cout << "Error:" << glewGetErrorString(err) << std::endl;

         }
        std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;
        std::cout << "Status: Using GL " << glGetString(GL_VERSION) << std::endl;

        float positions[6] = {
            -0.5f, -0.5f,
            0.0f, 0.5f,
            0.5f, -0.5f
        };

        unsigned int buffer;
        glGenBuffers(1, &buffer);/* ���ɻ����� */
        glBindBuffer(GL_ARRAY_BUFFER, buffer);/* �󶨻����� */
        glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);/* ���û��������� */
        
        glEnableVertexAttribArray(0);//���� -0.5f, -0.5f,λ��
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
        //                   0����ʼ����id ��2���������������� 2 * sizeof(float)������ƫ�Ƶ���һ�������Bytes��GL_FALSE�����һ��


        ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
        unsigned int shader = CreateShader(source.VertexSource, source.FragmentSource);
        glUseProgram(shader); /* ʹ����ɫ������ */



        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);
            
            glDrawArrays(GL_TRIANGLES, 0, 3);
            /* Swap front and back buffers */
            glfwSwapBuffers(window);

            /* Poll for and process events */
            glfwPollEvents();
        }
        glDeleteProgram(shader);
        glfwTerminate();
        return 0;
    }