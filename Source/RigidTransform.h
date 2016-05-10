#ifndef RIGID_TRANS_
#define RIGID_TRANS_


#include "Vectors.h"
#include "Matrices.h"
#include "openvr.h"

class RigidTransform
{
public:
	RigidTransform() {};
	~RigidTransform() {};
	void UpdateTransform(vr::HmdMatrix34_t pose);

	Vector3 pos;
	Vector4 rot; //quaternion
	float yaw, pitch, roll;

};

inline void RigidTransform::UpdateTransform(vr::HmdMatrix34_t pose)
{
	Matrix4 m;
	
	m[0] = pose.m[0][0];
	m[1] = pose.m[0][1];
	m[2] = -pose.m[0][2];
	m[3] = pose.m[0][3];

	m[4] = pose.m[1][0];
	m[5] = pose.m[1][1];
	m[6] = -pose.m[1][2];
	m[7] = pose.m[1][3];

	m[8] = -pose.m[2][0];
	m[9] = -pose.m[2][1];
	m[10] = pose.m[2][2];
	m[11] = -pose.m[2][3];

	this->pos = m.GetPosition();
	this->rot = m.GetRotation();


	//
	yaw = atan2f(2.0f*(this->rot.y * this->rot.z + this->rot.w * this->rot.x), this->rot.w * this->rot.w - this->rot.x * this->rot.x - this->rot.y * this->rot.y + this->rot.z*this->rot.z);
	pitch = asinf(-2.0f*(this->rot.x*this->rot.z - this->rot.w*this->rot.y));
	roll = atan2f(2.0f*(this->rot.x * this->rot.x + this->rot.w * this->rot.z), this->rot.w * this->rot.w + this->rot.x * this->rot.x - this->rot.y * this->rot.y - this->rot.z * this->rot.z);
}

#endif // !RIGID_TRANS_