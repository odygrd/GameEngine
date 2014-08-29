#ifndef COMMON_H
#define COMMON_H
#include <GLM\glm.hpp>

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define INVALID_VALUE 0xFFFFFFFF

typedef glm::vec2 vec2;
typedef glm::vec3 vec3;
typedef glm::vec4 vec4;
typedef glm::mat3 mat3;
typedef glm::mat4 mat4;

//Definitions
static const bool IGNORE_FRAME_CAP = true;
static const bool WINDOW_RESIZABLE = false;
static const bool FULLSCREEN = false;

static const float WIDTH = 1280;
static const float HEIGHT = 720;
static const double FRAME_CAP = 1000;
static const int SAMPLES = 4;

static const float FOV = 50.0f;
static const float ZNEAR = 0.01f;
static const float ZFAR = 100.0f;

static const int NUM_KEYS = 350;
static const int NUM_MOUSEBUTTONS = 8;

class Time {
public:
	static double GetDelta(){ return m_delta; }
	static void SetDelta(double value) { m_delta = value; }
private:
	static double m_delta;
};

class Color
{
public:
	Color():m_color(vec3(0.0f,0.0f,0.0f)){}
	Color(float r, float g, float b):m_color(vec3(r,g,b)){}
	inline const vec3& GetColor() const { return m_color; }
	inline void SetColor(float r, float g, float b){ m_color = vec3(r, g, b); }
private:
	vec3 m_color;
};
#endif