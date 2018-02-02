﻿#ifndef __GM_LINEARMATH_H__
#define __GM_LINEARMATH_H__
#include <defines.h>
#include <math.h>
#include <gmdxincludes.h>

#define GLM_FORCE_INLINE
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/matrix_inverse.inl"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/compatibility.hpp"
#include "glm/gtx/fast_square_root.hpp"
#include "glm/gtx/norm.hpp"

constexpr gm::GMfloat PI = 3.141592653f;

bool s_useDxMath = false;

#define IS_OPENGL (!s_useDxMath)
#define IS_DX (s_useDxMath)

BEGIN_NS

#ifndef FLT_EPSILON
#	define FLT_EPSILON 1.192092896e-07F
#endif

#define GM_SIMD_EPSILON FLT_EPSILON

// 数学函数
inline GMfloat gmFabs(GMfloat x) { return fabsf(x); }
inline GMfloat gmCos(GMfloat x) { return cosf(x); }
inline GMfloat gmSin(GMfloat x) { return sinf(x); }
inline GMfloat gmTan(GMfloat x) { return tanf(x); }
inline GMfloat gmSqrt(GMfloat x) { return sqrtf(x); }
inline GMfloat gmAcos(GMfloat x)
{
	if (x < GMfloat(-1))
		x = GMfloat(-1);
	if (x > GMfloat(1))
		x = GMfloat(1);
	return acosf(x);
}
inline GMfloat gmAsin(GMfloat x)
{
	if (x < GMfloat(-1))
		x = GMfloat(-1);
	if (x > GMfloat(1))
		x = GMfloat(1);
	return asinf(x);
}
inline GMfloat gmAtan(GMfloat x) { return atanf(x); }
inline GMfloat gmAtan2(GMfloat x, GMfloat y) { return atan2f(x, y); }
inline GMfloat gmExp(GMfloat x) { return expf(x); }
inline GMfloat gmLog(GMfloat x) { return logf(x); }
inline GMfloat gmPow(GMfloat x, GMfloat y) { return powf(x, y); }
inline GMfloat gmFmod(GMfloat x, GMfloat y) { return fmodf(x, y); }
inline GMfloat gmFloor(GMfloat x) { return floor(x); }
inline GMfloat gmMin(GMfloat x, GMfloat y) { return x < y ? x : y; }
inline GMfloat gmMax(GMfloat x, GMfloat y) { return x > y ? x : y; }

END_NS

#if GM_USE_DX11
#define GMMATH_BEGIN_STRUCT(className, glStruct, dxStruct)	\
	struct className					\
	{									\
		glStruct gl_;					\
		dxStruct dx_;					\
	public:								\
		className() = default;			\
		className(const className& rhs);
#else
#define GMMATH_BEGIN_STRUCT(className, glStruct, dxStruct)	\
	struct className					\
	{									\
		glStruct gl_;					\
										\
	public:								\
		className() = default;			\
		className(const GMVec2& rhs);
#endif
#define GMMATH_END_STRUCT };

namespace gmmath
{
	enum DataFormat
	{
		GL,
		DX,
	};

	// This is a singleton
	struct GMMathEnv
	{
	public:
		GMMathEnv();
		DataFormat format_;
	};

	extern GMMathEnv* s_math_env_instance;

	GMMATH_BEGIN_STRUCT(GMVec2, glm::vec2, D3DXVECTOR2)
	GMMATH_END_STRUCT

	GMMATH_BEGIN_STRUCT(GMVec3, glm::vec3, D3DXVECTOR3)
	GMMATH_END_STRUCT

	GMMATH_BEGIN_STRUCT(GMVec4, glm::vec4, DirectX::XMVECTOR)
	GMMATH_END_STRUCT

	GMMATH_BEGIN_STRUCT(GMMat4, glm::mat4, DirectX::XMMATRIX)
	GMMATH_END_STRUCT

	GMMATH_BEGIN_STRUCT(GMQuat, glm::quat, DirectX::XMVECTOR)
	GMMATH_END_STRUCT

	//////////////////////////////////////////////////////////////////////////
	GMVec2 __getZeroVec2();
	GMVec3 __getZeroVec3();
	GMVec4 __getZeroVec4();
	GMMat4 __getIdentityMat4();
	GMMat4 __mul(const GMMat4& M1, const GMMat4& M2);
	GMVec4 __mul(const GMVec4& V, const GMMat4& M);

	template <typename T>
	T zero();

	template <>
	GMVec2 zero()
	{
		return __getZeroVec2();
	}

	template <>
	GMVec3 zero()
	{
		return __getZeroVec3();
	}

	template <>
	GMVec4 zero()
	{
		return __getZeroVec4();
	}

	template <typename T>
	T identity();

	template <>
	GMMat4 identity()
	{
		return __getIdentityMat4();
	}

	//! 计算两个矩阵相乘的结果。
	/*!
	  表示先进行M1矩阵变换，然后进行M2矩阵变换。
	  \param M1 先进行变换的矩阵。
	  \param M2 后进行变换的矩阵。
	  \return 变换后的矩阵。
	*/
	GMMat4 operator*(const GMMat4& M1, const GMMat4& M2)
	{
		return __mul(M1, M2);
	}

	GMVec4 operator*(const GMVec4& V, const GMMat4& M)
	{
		return __mul(V, M);
	}

	GMMat4 QuatToMatrix(const GMQuat& quat)
	{
		GMMat4 mat;
#if GM_USE_DX11
		if (1)
			mat.gl_ = glm::mat4_cast(quat.gl_);
		else
			mat.dx_ = DirectX::XMMatrixRotationQuaternion(quat.dx_);
#else
		mat.gl_ = glm::mat4_cast(quat.gl_);
#endif
		return mat;
	}
}

#include "linearmath.inl"

#endif
