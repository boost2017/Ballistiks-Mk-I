#pragma once
#include "AlertZone.h"
#include "TriangleStrip.h"

class GoalZone : public AlertZone
{
public:
	class Drawable : ::Drawable
	{
	public:
		Drawable( const GoalZone& parent )
			:
			parent( parent )
		{}
		virtual void Rasterize( D3DGraphics& gfx ) const override
		{
			for( const TriangleStrip& s : parent.strips )
			{
				s.GetDrawable( parent.color ).Rasterize( gfx );
			}
		}
	private:
		const GoalZone& parent;
	};
public:
	GoalZone( const PolyClosed& poly )
		:
		AlertZone( poly ),
		strips( TriangleStrip::ExtractSolidStripCollection( poly ) )
	{}
	Drawable GetDrawable() const
	{
		return Drawable( *this );
	}
private:
	const std::vector< const TriangleStrip > strips;
	const Color color = Color( 80,0,0 );
};