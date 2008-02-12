/***************************************************************************
 *   Copyright (C) 2007 by Sindre Aam�s                                    *
 *   aamas@stud.ntnu.no                                                    *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License version 2 as     *
 *   published by the Free Software Foundation.                            *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License version 2 for more details.                *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   version 2 along with this program; if not, write to the               *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

class QWidget;

#include <QString>

class AudioEngine {
public:
	struct BufferState {
		enum { NOT_SUPPORTED = 0xFFFFFFFFu };
		unsigned fromUnderrun;
		unsigned fromOverflow;
	};
	
	const QString nameString;
	
	AudioEngine(const QString &name) : nameString(name) {}
	virtual ~AudioEngine() {}
	virtual int init(int rate, unsigned msLatency) = 0;
	virtual void uninit() {}
	virtual int write(void *buffer, unsigned samples) = 0;
	virtual const BufferState bufferState() const { static const BufferState s = { BufferState::NOT_SUPPORTED, BufferState::NOT_SUPPORTED }; return s; }
	virtual void pause() {}
	virtual QWidget* settingsWidget() { return NULL; }
	virtual void acceptSettings() {}
	virtual void rejectSettings() {}
};

#endif
