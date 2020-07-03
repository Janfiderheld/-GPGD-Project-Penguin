#ifndef LIGHT_INTERACE
#define LIGHT_INTERACE

#include <GLM/glm.hpp>

class ILighting {
private:
	int _radius;
	float _brightness;
	glm::vec3 _color;

public:
	/// <summary>
	/// Returns the radius of the light source
	/// </summary>	/// <returns></returns>
	int getRadius() {
		return _radius;
	}

	/// <summary>
	/// Sets the radius of the light source.
	/// Radius is saved as a percentage value
	/// </summary>
	void setRadius(int newRadius) {
		_radius = newRadius;
	}

	/// <summary>
	/// Returns the brightness of this light source
	/// </summary>
	float getBrightness() {
		return _brightness;
	}

	/// <summary>
	/// Sets the brightness of this light source.
	/// If the given value is not in [0, 1], a default value of 0.5 is used
	/// </summary>
	void setBrightness(float newBright) {
		if (newBright < 0.0f || newBright > 1.0f) {
			_brightness = 0.5f;
		} else {
			_brightness = newBright;
		}
	}

	/// <summary>
	/// Returns the color of the light source
	/// </summary>
	glm::vec3 getColor() {
		return _color;
	}

	/// <summary>
	/// Sets the color of the light source
	/// </summary>
	void setColor(glm::vec3 newColor) {
		_color = newColor;
	}

	/// <summary>
	/// Returns color and brightness in one vector
	/// </summary>
	glm::vec4 getColorAndBrightness() {
		return glm::vec4(_color, _brightness);
	}

	/// <summary>
	/// Sets the color and the brightness
	/// </summary>
	void setColorAndBrightness(glm::vec4 newColor4) {
		setBrightness(newColor4.a);
		setColor(glm::vec3(newColor4.r, newColor4.g, newColor4.b));
	}
};

#endif // LIGHT_INTERACE