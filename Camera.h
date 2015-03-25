class Camera
{
public:
    Camera(float windowWidth, float windowHeight);
    ~Camera();
 
    void handleMouseMove(int mouseX, int mouseY);
    const double toRads(const double &angleInDegrees) const;
    void move(double deltaTime);
 
    float getPitchSensitivity()            { return pitchSensitivity;  }
    void  setPitchSensitivity(float value) { pitchSensitivity = value; }
    float getYawSensitivity()              { return yawSensitivity;    }
    void  setYawSensitivity(float value)   { yawSensitivity   = value; }
 
    Vec3<double> getPosition() const { return position;        }
    double getXPos()           const { return position.getX(); }
    double getYPos()           const { return position.getY(); }
    double getZPos()           const { return position.getZ(); }
 
    Vec3<double> getRotation() const { return rotation;        }
    double getXRot()           const { return rotation.getX(); }
    double getYRot()           const { return rotation.getY(); }
    double getZRot()           const { return rotation.getZ(); }
    
    static const double TO_RADS; 
    bool forward;
    bool backward;
    bool left;
    bool right;
protected:
    Vec3<double> position;
    Vec3<double> rotation;
    Vec3<double> speed;
    double movementSpeedFactor;
    double pitchSensitivity;
    double yawSensitivity;
    int windowWidth;
    int windowHeight;
    int windowMidX;
    int windowMidY;
 
    void initCamera();
};