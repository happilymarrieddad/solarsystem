struct Light
{
    Light( GLenum lightID
         , GLfloat ambient[]
         , GLfloat diffuse[]
         , GLfloat specular[]
         , GLfloat position[]
         , GLfloat spotDirection[]
         , GLfloat  spotExponent
         , GLfloat  spotCutoff
         , GLfloat  constantAttenuation
         , GLfloat  linearAttenuation
         , GLfloat  quadraticAttenuation)
        : m_LightID ( lightID )
        , m_Ambient( ambient )
        , m_Diffuse( diffuse )
        , m_Specular( specular )
        , m_Position( position )
        , m_SpotDirection( spotDirection )
        , m_SpotExponent( spotExponent )
        , m_SpotCutoff( spotCutoff )
        , m_ConstantAttenuation( constantAttenuation )
        , m_LinearAttenuation( linearAttenuation )
        , m_QuadraticAttenuation( quadraticAttenuation )
    {}
 
    void Activate()
    {
        glEnable( m_LightID );
        glLightfv( m_LightID, GL_AMBIENT, &(m_Ambient) );
        glLightfv( m_LightID, GL_DIFFUSE, &(m_Diffuse) );
        glLightfv( m_LightID, GL_SPECULAR, &(m_Specular) );
        glLightfv( m_LightID, GL_POSITION, &(m_Position) );
        glLightfv( m_LightID, GL_SPOT_DIRECTION, &(m_SpotDirection) );
        glLightf( m_LightID, GL_SPOT_EXPONENT, m_SpotExponent );
        glLightf( m_LightID, GL_SPOT_CUTOFF, m_SpotCutoff );
        glLightf( m_LightID, GL_CONSTANT_ATTENUATION, m_ConstantAttenuation );
        glLightf( m_LightID, GL_LINEAR_ATTENUATION, m_LinearAttenuation );
        glLightf( m_LightID, GL_QUADRATIC_ATTENUATION, m_QuadraticAttenuation );
    } 
 
    void Deactivate()
    {
        glDisable( m_LightID );
    }
 
    GLenum m_LightID;
    GLfloat m_Ambient[4];
    GLfloat m_Diffuse[4];
    GLfloat m_Specular[4];
 
    GLfloat m_Position[4];
    GLfloat m_SpotDirection[3];
    GLfloat  m_SpotExponent;
    GLfloat  m_SpotCutoff;
    GLfloat  m_ConstantAttenuation;
    GLfloat  m_LinearAttenuation;
    GLfloat  m_QuadraticAttenuation;
};