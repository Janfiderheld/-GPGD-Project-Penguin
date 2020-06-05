#ifndef DRAWVERT_HEADER
#define DRAWVERT_HEADER

class DrawableVertices {
private:
	int VerticeAmount = 20;

	float _minX = 0.0f;
	float _minY = 0.0f;
	float _maxX = 0.0f;
	float _maxY = 0.0f;
	
	float* _vertices = new float[VerticeAmount];
	void calculateVertices();

protected:
	float _z = -10.0f;
	
public:
	DrawableVertices(float minX, float minY, float maxX, float maxY);
	
	float* getVertices();
};

#endif // DRAWVERT_HEADER