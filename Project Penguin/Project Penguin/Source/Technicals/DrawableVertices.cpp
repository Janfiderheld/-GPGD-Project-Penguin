#include <Technicals/DrawableVertices.h>

/// <summary>
/// Calculates the vertices based on the saved values
/// </summary>
void DrawableVertices::calculateVertices() {
	for(int i = 0; i < VerticeAmount; i++) {
		if(i == 0 || i == 5) {
			_vertices[i] = _maxX;
		}
		if(i == 1 || i == 16) {
			_vertices[i] = _maxY;
		}
		if(i == 10 || i == 15) {
			_vertices[i] = _minX;
		}
		if(i == 6 || i == 11) {
			_vertices[i] = _minY;
		}
		if((i + 3) % 5 == 0) {
			_vertices[i] = _z;
		}
		if(i == 3 || i == 4 || i == 8 || i == 19) {
			_vertices[i] = 1.0f;
		}
	}
}

/// <summary>
/// Sets the min and max values for the x- and y-axis. Also sets all values initially to zero
/// </summary>
/// <param name="minX">min value on x-axis</param>
/// <param name="minY">min value on y-axis</param>
/// <param name="maxX">max value on x-axis</param>
/// <param name="maxY">max value on y-axis</param>
/// <returns></returns>
DrawableVertices::DrawableVertices(float minX, float minY, float maxX, float maxY) {
	_minX = minX;
	_minY = minY;
	_maxX = maxX;
	_maxY = maxY;

	for(int i = 0; i < VerticeAmount; i++) {
		_vertices[i] = 0.0f;
	}
}

/// <summary>
/// Returns the filled vertices for drawing 
/// </summary>
float* DrawableVertices::getVertices() {
	calculateVertices();
	return _vertices;
}