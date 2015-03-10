class Moon
{
public:
	Moon();
	~Moon();
private:
    GLUquadricObj *sphere;
    GLuint texture;
};

Moon::Moon()
{
	sphere = gluNewQuadric();
}

Moon::~Moon()
{
}