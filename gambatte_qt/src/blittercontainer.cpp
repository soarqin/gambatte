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
#include "blittercontainer.h"

#include "blitterwidget.h"
#include "fullrestoggler.h"
#include "videodialog.h"
#include <QResizeEvent>

BlitterContainer::BlitterContainer(const FullResToggler &resToggler_in, const VideoDialog *videoDialog, QWidget *parent) :
	QWidget(parent),
	resToggler(resToggler_in),
	videoDialog(videoDialog),
	blitter(NULL)
{
	QPalette pal = palette();
	pal.setColor(QPalette::Window, QColor(0, 0, 0));
	setPalette(pal);
// 	setBackgroundRole(QPalette::Window);
	setAutoFillBackground(true);
}

BlitterContainer::~BlitterContainer()
{}

void BlitterContainer::doLayout(const int w, const int h) {
	if (!blitter)
		return;
	
	if (videoDialog->scalingType() == UNRESTRICTED)
		blitter->setCorrectedGeometry(w, h, w, h);
	else if (videoDialog->scalingType() == KEEP_RATIO) {
		const QSize &ar = videoDialog->aspectRatio();
		
		if (w * (ar).height() > h * ar.width()) {
			const int new_w = (h * ar.width() + (ar.height() >> 1)) / ar.height();
			blitter->setCorrectedGeometry(w, h, new_w, h);
		} else {
			const int new_h = (w * ar.height() + (ar.width() >> 1)) / ar.width();
			blitter->setCorrectedGeometry(w, h, w, new_h);
		}
	} else {
		const int scale = std::min(w / minimumWidth(), h / minimumHeight());
		const int new_w = minimumWidth() * scale;
		const int new_h = minimumHeight() * scale;
		blitter->setCorrectedGeometry(w, h, new_w, new_h);
	}
	
	if (!resToggler.resVector().empty()) {
		const ResInfo &res = resToggler.resVector()[resToggler.currentResIndex()];
		blitter->setExclusive(res.w == static_cast<unsigned>(w) && res.h == static_cast<unsigned>(h));
	}
}

void BlitterContainer::setBlitter(BlitterWidget *const blitter_in) {
	if (blitter)
		blitter->setParent(0);
	
	blitter = blitter_in;
	
	if (blitter) {
		blitter->setParent(this);
		updateLayout();
	}
}

void BlitterContainer::resizeEvent(QResizeEvent *const event) {
	doLayout(event->size().width(), event->size().height());
}

void BlitterContainer::hideEvent(QHideEvent *const event) {
	if (blitter)
		blitter->setExclusive(false);
	
	QWidget::hideEvent(event);
}
