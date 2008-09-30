/*
 * bit_invader.h - declaration of class bitInvader and bSynth which
 *                         are a wavetable synthesizer
 *
 * Copyright (c) 2006-2008 Andreas Brandmaier <andy/at/brandmaier/dot/de>
 * 
 * This file is part of Linux MultiMedia Studio - http://lmms.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 *
 */


#ifndef _BIT_INVADER_H
#define _BIT_INVADER_H


#include "instrument.h"
#include "instrument_view.h"
#include "types.h"
#include "graph.h"
#include "knob.h"
#include "pixmap_button.h"
#include "led_checkbox.h"

class oscillator;
class bitInvaderView;

class bSynth
{
public:
	bSynth( float * sample, int length, notePlayHandle * _nph,
			bool _interpolation, float factor, 
			const sample_rate_t _sample_rate );
	virtual ~bSynth();
	
	sample_t nextStringSample();


private:
	int sample_index;
	float sample_realindex;
	float* sample_shape;
	notePlayHandle* nph;
	const int sample_length;
	const sample_rate_t sample_rate;

	bool interpolation;
	
} ;

class bitInvader : public instrument
{
	Q_OBJECT
public:
	bitInvader(instrumentTrack * _channel_track );
	virtual ~bitInvader();

	virtual void playNote( notePlayHandle * _n,
						sampleFrame * _working_buffer );
	virtual void deleteNotePluginData( notePlayHandle * _n );


	virtual void saveSettings( QDomDocument & _doc,
							QDomElement & _parent );
	virtual void loadSettings( const QDomElement & _this );

	virtual QString nodeName( void ) const;

	virtual f_cnt_t desiredReleaseFrames( void ) const
	{
		return( 64 );
	}

	virtual pluginView * instantiateView( QWidget * _parent );

protected slots:
	void lengthChanged( void );
	void samplesChanged( int, int );

	void normalize( void );


private:
	knobModel  m_sampleLength;
	graphModel  m_graph;
	
	boolModel m_interpolation;
	boolModel m_normalize;
	
	float normalizeFactor;
	
	oscillator * m_osc;

	friend class bitInvaderView;
} ;



class bitInvaderView : public instrumentView
{
	Q_OBJECT
public:
	bitInvaderView( instrument * _instrument,
					QWidget * _parent );

	virtual ~bitInvaderView() {};

protected slots:
	//void sampleSizeChanged( float _new_sample_length );

	void interpolationToggled( bool value );
	void normalizeToggled( bool value );

	void sinWaveClicked( void );
	void triangleWaveClicked( void );
	void sqrWaveClicked( void );
	void sawWaveClicked( void );
	void noiseWaveClicked( void );
	void usrWaveClicked( void );
	
	void smoothClicked( void  );

private:
	virtual void modelChanged( void );

	knob * m_sampleLengthKnob;
	pixmapButton * sinWaveBtn;
	pixmapButton * triangleWaveBtn;
	pixmapButton * sqrWaveBtn;
	pixmapButton * sawWaveBtn;
	pixmapButton * whiteNoiseWaveBtn;
	pixmapButton * smoothBtn;
	pixmapButton * usrWaveBtn;

	static QPixmap * s_artwork;

	graph * m_graph;
	ledCheckBox * m_interpolationToggle;
	ledCheckBox * m_normalizeToggle;

} ;



#endif
