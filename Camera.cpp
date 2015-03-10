class Camera
{
public:
	Camera();
	~Camera();
/*
    void rotateY(GLfloat num);
    void setTarget(Vector target);
    void update();*/

private:
    glm::vec3 target;
    /*
    Vector c_target;
    Vector c_position;
    Vector c_up;
    Vector c_right;*/
};

Camera::Camera()
{
    
}

Camera::~Camera()
{
}

/*
void Camera::rotateY(GLfloat num)
{
	// Store current values so they don't change while doing the calculations
    Vector target = c_target;
    Vector right = c_right;

    // Convert to radians
    num /= 57.2957795f;

    c_target.m_xyzw[0] = (cos(1.5708f + num) * target.m_xyzw[0]) + (cos(num) * right.m_xyzw[0]);
    c_target.m_xyzw[1] = (cos(1.5708f + num) * target.m_xyzw[1]) + (cos(num) * right.m_xyzw[1]);
    c_target.m_xyzw[2] = (cos(1.5708f + num) * target.m_xyzw[2]) + (cos(num) * right.m_xyzw[2]);


    c_right.m_xyzw[0] = (cos(num) * target.m_xyzw[0]) + (cos(1.5708f) * right.m_xyzw[0]);
    c_right.m_xyzw[1] = (cos(num) * target.m_xyzw[1]) + (cos(1.5708f) * right.m_xyzw[1]);
    c_right.m_xyzw[2] = (cos(num) * target.m_xyzw[2]) + (cos(1.5708f) * right.m_xyzw[2]);

    c_target.normalize();
    m_right.normalize();
}

void Camera::setTarget(Vector target)
{
	Vector projectedTarget;
     
    target = target - c_position;
    projectedTarget = target;
         
    if(fabs(target.m_xyzw[0]) < 0.00001f && fabs(target.m_xyzw[2]) < 0.00001f) {  // YZ plane
     
        projectedTarget.m_xyzw[0] = 0.0f;
        projectedTarget.normalize();
         
        c_right = Vector(1.0f, 0.0f, 0.0f);
        c_up = cross(projectedTarget, c_right);
             
        c_target = target;
        c_right = -cross(c_target, c_up);
    }
         
    else {                                      // XZ plane
             
        projectedTarget.m_xyzw[1] = 0.0f;
        projectedTarget.normalize();
         
        c_up = Vector(0.0f, 1.0f, 0.0f);
        c_right = -cross(projectedTarget, c_up);
     
        c_target = target;
        c_up = cross(c_target, c_right);
    }
     
    c_target.normalize();
    c_right.normalize();
    c_up.normalize();
}

void Camera::update()
{
	gluLookAt(
        c_position.m_xyzw[0];
        c_position.m_xyzw[1];
        c_position.m_xyzw[2];
        c_target.m_xyzw[0];
        c_target.m_xyzw[1];
        c_target.m_xyzw[2];
        c_up.m_xyzw[0];
        c_up.m_xyzw[1];
        c_up.m_xyzw[2];
	);
}
*/