class Solarsystem
{
public:
	Solarsystem();
	Solarsystem(string n);
	~Solarsystem();

	void initializeSolSystem();
	void initializeSolSystem(Star star);
	void addStar(Star star);
	int getNumberOfStars() { return (int) stars.size(); }
	void display();

private:
    string name;
    vector<Star> stars;
    bool initialized;
};

Solarsystem::Solarsystem()
{
	name = "";
	initialized = false;
}

Solarsystem::Solarsystem(string n)
{
	name = n;
	initialized = false;
}

Solarsystem::~Solarsystem()
{
}

void Solarsystem::initializeSolSystem()
{
	if (!initialized) 
	{
		initialized = true;
	}
	else
	{
		cout << "Unable to initialize system. "
		     << "System has already been initialized.";
		return;
	}
}

void Solarsystem::initializeSolSystem(Star star)
{
	if (!initialized) 
	{
		initialized = true;
		stars.push_back(star);
	}
	else
	{
		cout << "Unable to initialize system. "
		     << "System has already been initialized.";
		return;
	}
}

void Solarsystem::addStar(Star star)
{
	stars.push_back(star);
}

void Solarsystem::display()
{
	for(int i=0; i < stars.size(); i++)
	{
        stars[i].display();
    }
}