class Star
{
public:
	Star();
	~Star();

	void initialize();
	void addPlanet(Planet planet) { planets.push_back(planet); }
	void addBMP(const char* filename);
	void display();

    // Getters
    GLUquadricObj* getStar() { return sphere; }
    GLuint getTexture() { return texture; }
    GLfloat getSize() { return size; }
    GLint getSlices() { return slices; }
    GLint getStacks() { return stacks; }
    GLfloat getXLocation() { return xLoc; }
    GLfloat getYLocation() { return yLoc; }
    GLfloat getZLocation() { return zLoc; }
    GLfloat getXRotation() { return xRot; }
    GLfloat getYRotation() { return yRot; }
    GLfloat getZRotation() { return zRot; }
    GLfloat getDistance() { return distance; }

    // Setters
    void setSphere(GLUquadricObj *star) { sphere = star; }
    void setTexture(GLuint t) { texture = t; }
    void setSize(GLfloat s) { size = s; }
    void setSlices(GLint s) { slices = s; }
    void setStacks(GLint s) { stacks = s; }
    void setXLocation(GLfloat x) { xLoc = x; }
    void setYLocation(GLfloat y) { yLoc = y; }
    void setZLocation(GLfloat z) { zLoc = z; }
    void setXRotation(GLfloat x) { xRot = x; }
    void setYRotation(GLfloat y) { yRot = y; }
    void setZRotation(GLfloat z) { zRot = z; }
    void setDistance(GLfloat d) { distance = d; }

private:
    GLUquadricObj *sphere;
    vector<Planet> planets;
    GLuint texture;
    GLfloat size;
    GLint slices;
    GLint stacks;
    GLfloat xLoc;
    GLfloat yLoc;
    GLfloat zLoc;
    GLfloat xRot;
    GLfloat yRot;
    GLfloat zRot;
    GLfloat distance;
};

Star::Star()
{
	sphere = gluNewQuadric();
	texture = 0;
	size = 1.0f;
	slices = 50;
	stacks = 50;
    xLoc = 0.0f;
    yLoc = 0.0f;
    zLoc = 0.0f;
    xRot = 0.0f;
    yRot = 1.0f;
    zRot = 0.0f;
    distance = 0.0f;
}

Star::~Star()
{
}

void Star::initialize()
{

}

void Star::addBMP(const char* filename)
{
	Image* img = Image::loadBMP(filename);
	texture = Image::loadTextureFromImage(img);
	delete img;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    sphere = gluNewQuadric();
	gluQuadricDrawStyle(sphere, GLU_FILL);
	gluQuadricTexture(sphere, GL_TRUE);
	gluQuadricNormals(sphere, GLU_SMOOTH);
}

void Star::display()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texture);
	gluSphere(sphere, size, slices, stacks);
	glPopMatrix();
}