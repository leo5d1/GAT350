#include "Matrix2x2.h"

namespace c14
{
	// 1 0
	// 0 1
	const Matrix2x2 Matrix2x2::identity
	{ 
		{1, 0},
		{0, 1}
	};
	// 0 0
	// 0 0
	const Matrix2x2 Matrix2x2::zero
	{ 
		{0, 0},
		{0, 0}
	};


	
}