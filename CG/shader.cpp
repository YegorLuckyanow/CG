#include<string>
#include<fstream>
#include<sstream>
#include<iostream>
#include<glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    unsigned int ID;
    Shader(const char *vertexPath, const char *fragmentPath);
    Shader(const char *vertexPath, const char *geometricPath, const char *fragmentPath);
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;
    void setVec4(const std::string &name, glm::vec4 value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
};

Shader::Shader(const char *vPath, const char *gPath, const char *fPath)
{
    std::string vc, fc, gc;
    std::ifstream vf(vPath), ff(fPath), gf(gPath);
    if (vf.fail())
    {
        std::cout << "Opening vertex shader error!" << std::endl;
        return;
    }
    if (ff.fail())
    {
        std::cout << "Opening fragment shader error!" << std::endl;
        return;
    }
    if (gf.fail())
    {
        std::cout << "Opening geometric shader error!" << std::endl;
        return;
    }
    while (!vf.eof())
    {
        std::string tmp;
        std::getline(vf, tmp);
        vc += tmp += "\n";
    }
    vf.close();
    while (!ff.eof())
    {
        std::string tmp;
        std::getline(ff, tmp);
        fc += tmp += "\n";
    }
    ff.close();
    while (!gf.eof())
    {
        std::string tmp;
        std::getline(gf, tmp);
        gc += tmp += "\n";
    }
    gf.close();
    const char *vcc = vc.c_str(), *fcc = fc.c_str(), *gcc = gc.c_str();
    unsigned vid, fid, gid;
    int succ;
    char infoLog[512];
    vid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vid, 1, &vcc, NULL);
    glCompileShader(vid);
    glGetShaderiv(vid, GL_COMPILE_STATUS, &succ);
    if (!succ)
    {
        glGetShaderInfoLog(vid, 512, NULL, infoLog);
        std::cout << "Vertex shader compilation error: " << infoLog << std::endl;
    }
    fid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fid, 1, &fcc, NULL);
    glCompileShader(fid);
    glGetShaderiv(fid, GL_COMPILE_STATUS, &succ);
    if (!succ)
    {
        glGetShaderInfoLog(fid, 512, NULL, infoLog);
        std::cout << "Fragment shader compilation error: " << infoLog << std::endl;
    }
    gid = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(gid, 1, &gcc, NULL);
    glCompileShader(gid);
    glGetShaderiv(gid, GL_COMPILE_STATUS, &succ);
    if (!succ)
    {
        glGetShaderInfoLog(gid, 512, NULL, infoLog);
        std::cout << "Geometric shader compilation error: " << infoLog << std::endl;
    }
    ID = glCreateProgram();
    glAttachShader(ID, vid);
    glAttachShader(ID, gid);
    glAttachShader(ID, fid);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &succ);
    if (!succ)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "Shader program linking error: " << infoLog << std::endl;
    }
    glDeleteShader(vid);
    glDeleteShader(fid);
}

Shader::Shader(const char *vPath, const char *fPath)
{
    std::string vc, fc, gc;
    std::ifstream vf(vPath), ff(fPath);
    if (vf.fail())
    {
        std::cout << "Opening vertex shader error!" << std::endl;
        return;
    }
    if (ff.fail())
    {
        std::cout << "Opening fragment shader error!" << std::endl;
        return;
    }
    while (!vf.eof())
    {
        std::string tmp;
        std::getline(vf, tmp);
        vc += tmp += "\n";
    }
    vf.close();
    while (!ff.eof())
    {
        std::string tmp;
        std::getline(ff, tmp);
        fc += tmp += "\n";
    }
    ff.close();
    const char *vcc = vc.c_str(), *fcc = fc.c_str();
    unsigned vid, fid;
    int succ;
    char infoLog[512];
    vid = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vid, 1, &vcc, NULL);
    glCompileShader(vid);
    glGetShaderiv(vid, GL_COMPILE_STATUS, &succ);
    if (!succ)
    {
        glGetShaderInfoLog(vid, 512, NULL, infoLog);
        std::cout << "Vertex shader compilation error: " << infoLog << std::endl;
    }
    fid = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fid, 1, &fcc, NULL);
    glCompileShader(fid);
    glGetShaderiv(fid, GL_COMPILE_STATUS, &succ);
    if (!succ)
    {
        glGetShaderInfoLog(fid, 512, NULL, infoLog);
        std::cout << "Fragment shader compilation error: " << infoLog << std::endl;
    }
    ID = glCreateProgram();
    glAttachShader(ID, vid);
    glAttachShader(ID, fid);
    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &succ);
    if (!succ)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout << "Shader program linking error: " << infoLog << std::endl;
    }
    glDeleteShader(vid);
    glDeleteShader(fid);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}
void Shader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}
void Shader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string &name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec4(const std::string &name, glm::vec4 value) const
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z, value.w);
}

void Shader::setVec3(const std::string &name, glm::vec3 value) const
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), value.x, value.y, value.z);
}