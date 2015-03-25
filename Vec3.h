template <class T> class Vec3
{
public:
	Vec3() { x = y = z = 0; }
	Vec3(T xVal, T yVal, T zVal) { x=xVal;y=yVal;z=zVal; }

	void setXYZ(const T &xVal, const T &yVal, const T &zVal)
	{
		x = xVal;
		y = yVal;
		z = zVal;
	}
	void setX(const T &xVal) { x = xVal; }
	void setY(const T &yVal) { y = yVal; }
	void setZ(const T &zVal) { z = zVal; }

	T getX() const { return x; }
	T getY() const { return y; }
	T getZ() const { return z; }

	void reset() { x=0;y=0;z=0; }
	void zero()
    {
        x = y = z = 0;
    }
	void normalize()
	{
		T magnitude = sqrt((x * x) + (y * y) + (z * z));
		if (magnitude != 0)
		{
			x /= magnitude;
			y /= magnitude;
			z /= magnitude;
		}
	}

	void display()
	{
	    cout << "X: " << x << "\t Y: " << y << "\t Z: " << z << endl;
	}
	void addX(T v) { x += v; }
	void addY(T v) { y += v; }
	void addZ(T v) { z += v; }



	static T dotProduct(const Vec3 &v1, const Vec3 &v2)
	{
	    return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	}

	T dotProduct(const Vec3 &v) const
	{
	    return (x * v.x) + (y * v.y) + (z * v.z);
	}

	static Vec3 cross(const Vec3 &v1, const Vec3 &v2)
	{
		return Vec3((v1.y * v2.z) - (v1.z * v2.y), 
			(v1.z * v2.x) - (v1.x * v2.z), 
	        (v1.x * v2.y) - (v1.y * v2.x));
	}

	static T getDistance(const Vec3 &v1, const Vec3 &v2)
	{
		T dx = v2.x - v1.x;
		T dy = v2.y - v1.y;
		T dz = v2.z - v1.z;

		return sqrt(dx * dx + dy * dy + dz * dz);
	}

	Vec3 operator +(const Vec3 &v) const
	{
	    return Vec3<T>(x + v.x, y + v.y, z + v.z);
	}

	void operator +=(const Vec3 &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	Vec3 operator -(const Vec3 &v) const
	{
	    return Vec3<T>(x - v.x, y - v.y, z - v.z);
	}

	void operator -=(const Vec3 &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}

	Vec3 operator *(const Vec3 &v) const
	{
	    return Vec3<T>(x * v.x, y * v.y, z * v.z);
	}

	Vec3 operator *(const T &v) const
	{
	    return Vec3<T>(x * v, y * v, z * v);
	}

	void operator *=(const T &v)
	{
		x *= v;
		y *= v;
		z *= v;
	}

	Vec3 operator /(const T &v) const
	{
	    return Vec3<T>(x / v, y / v, z / v);
	}

	void operator /=(const T &v)
	{
		x /= v;
		y /= v;
		z /= v;
	}

private:
	T x;
	T y;
	T z;
};