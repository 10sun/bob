#ifndef LINE2D_INC
#define LINE2D_INC

#include "ip/Point2D.h"

namespace Torch {

	/** This class is designed to handle a 2D line

	    A Line2D is infinite.

	    @author Sebastien Marcel (marcel@idiap.ch)
	    @author Dan Sunday (http://www.softsurfer.com/)
	    @version 2.0
	    \date
	    @since 1.0
	*/
	class Line2D : public geomObject
	{
	public:
		/// first point supporting the line
		Point2D P0;

		/// second point supporting the line
		Point2D P1;

		//-----

		/** @name constructors */
		//@{
		///
		Line2D() {};

		///
		Line2D(const Point2D& P0_, const Point2D& P1_) { P0 = P0_; P1 = P1_; }
		//@}

		/// destructor
		virtual ~Line2D() {};

		//-----

		///
		virtual void reset(const Point2D& P0_, const Point2D& P1_) { P0 = P0_; P1 = P1_; }

		///
		virtual void reset(int x0_, int y0_, int x1_, int y1_) { P0.reset(x0_, y0_); P1.reset(x1_, y1_); }

		//-----

		/// draw the line on an image
		virtual void draw(Image *image_, Color color_);

	#ifdef HAVE_X11
		/** draw the object on a X11 display

		    #line_style_# can be LineSolid, LineOnOffDash or LineDoubleDash
		    #fill_style_# can be FillSolid, FillTiled, FillStippled or FillOpaqueStippled
		*/
		virtual void xdraw(Display *pDisplay_, Pixmap pixmap_, GC gc_, unsigned long color_, int line_width_ = 1, int line_style_ = LineSolid, bool fill_ = false, int fill_style_ = FillSolid);
	#endif

	};

}

#endif
