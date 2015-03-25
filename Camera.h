class Camera
{
public:
    Camera(float width, float height);
    ~Camera();
 
    void handleMouseMove(int x, int y);
    const double toRadians(const double &angleInDegrees) const;
    void move(double deltaTime);
 
    float getPitchSensitivity()            { return _pitch;  }
    void  setPitchSensitivity(float value) { _pitch = value; }
    float getYawSensitivity()              { return _yaw;    }
    void  setYawSensitivity(float value)   { _yaw = value; }
 
    Vec3<double> getPosition() const { return position;        }
    double getXPos()           const { return position.getX(); }
    double getYPos()           const { return position.getY(); }
    double getZPos()           const { return position.getZ(); }
 
    Vec3<double> getRotation() const { return rotation;        }
    double getXRot()           const { return rotation.getX(); }
    double getYRot()           const { return rotation.getY(); }
    double getZRot()           const { return rotation.getZ(); }
    
    static const double TO_RADIANS;
    bool forward;
    bool backward;
    bool left;
    bool right;
protected:
    Vec3<double> position;
    Vec3<double> rotation;
    Vec3<double> speed;
    double _speed;
    double _pitch;
    double _yaw;
    int _width;
    int _height;
 
    void initCamera();
};