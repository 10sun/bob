/**
 * @file cxx/ip/ip/Matrix2D.h
 * @date Tue Jan 18 17:07:26 2011 +0100
 * @author André Anjos <andre.anjos@idiap.ch>
 *
 * Copyright (C) 2011 Idiap Reasearch Institute, Martigny, Switzerland
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MATRIX2D_INC
#define MATRIX2D_INC

#include "core/general.h"
#include "core/Tensor.h"

namespace bob {

	/** This class is designed to handle a 2D matrix for geometric operations

	    @author Sebastien Marcel (marcel@idiap.ch)
	    @author Dan Sunday (http://www.softsurfer.com/)
	    @version 2.1
	    \date
	    @since 1.0
	*/
	class Matrix2D : public DoubleTensor
	{
	public:

		/** @name constructors */
		//@{
		/// creates an zero 2D matrix
		Matrix2D();

		/** creates a 2D matrix from coefficients.

		    the 2D matrix will be:
		    \verbatim
			[ a b
			  c d ]
		    \endverbatim
		*/
		Matrix2D(double a, double b, double c, double d);

		/// creates a 2D matrix from another one
		Matrix2D(const Matrix2D &);
		//@}

		///
		~Matrix2D();

		//-----

		/// copy a matrix
		Matrix2D operator=(const Matrix2D&);

		//-----

		/// unary minus operation
		Matrix2D operator-();

		//-----

		/** @name Matrix2D arithmetic operations */
		//@{
		/// addition
		Matrix2D operator+(const Matrix2D&);

		/// substraction
		Matrix2D operator-(const Matrix2D&);

		/// scalar multiplication
		Matrix2D& operator*=(double);

		/// scalar division
		Matrix2D& operator/=(double);

		/// increment
		Matrix2D& operator+=(const Matrix2D&);

		/// decrement
		Matrix2D& operator-=(const Matrix2D&);
		//@}
	};

	//-----

	/** @name scalar multiplication

	    @author Sebastien Marcel (marcel@idiap.ch)
	    @author Dan Sunday (http://www.softsurfer.com/)
	    @version 2.1
	    \date
	    @since 1.0
	*/
	//@{
	/// Matrix2D operator*(int, Matrix2D)
	Matrix2D operator*(int, const Matrix2D&);

	/// Matrix2D operator*(double, Matrix2D)
	Matrix2D operator*(double, const Matrix2D&);

	/// Matrix2D operator*(Matrix2D, int)
	Matrix2D operator*(const Matrix2D&, int);

	/// Matrix2D operator*(Matrix2D, double)
	Matrix2D operator*(const Matrix2D&, double);
	//@}

	//-----

	/** @name scalar division

	    @author Sebastien Marcel (marcel@idiap.ch)
	    @author Dan Sunday (http://www.softsurfer.com/)
	    @version 2.1
	    \date
	    @since 1.0
	*/
	//@{
	/// Matrix2D operator/(Matrix2D, int)
	Matrix2D operator/(const Matrix2D&, int);

	/// Matrix2D operator/(Matrix2D, double)
	Matrix2D operator/(const Matrix2D&, double);
	//@}

}

#endif
