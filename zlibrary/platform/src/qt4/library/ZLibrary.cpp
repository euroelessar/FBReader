/*
 * Copyright (C) 2004-2007 Nikolay Pultsin <geometer@mawhrin.net>
 * Copyright (C) 2005 Mikhail Sobolev <mss@mawhrin.net>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <QtGui/QApplication>

#include <ZLApplication.h>
#include <ZLibrary.h>

#include "../filesystem/ZLQtFSManager.h"
#include "../time/ZLQtTime.h"
#include "../dialogs/ZLQtDialogManager.h"
#include "../image/ZLQtImageManager.h"
#include "../view/ZLQtPaintContext.h"
#include "../../../../core/src/unix/message/ZLUnixMessage.h"
#include "../../../../core/src/util/ZLKeyUtil.h"
#include "../../../../core/src/unix/xmlconfig/XMLConfig.h"
#include "../../../../core/src/unix/iconv/IConvEncodingConverter.h"

void ZLibrary::init(int &argc, char **&argv) {
	new QApplication(argc, argv);

	parseArguments(argc, argv);

	XMLConfigManager::createInstance();
	ZLQtTimeManager::createInstance();
	ZLQtFSManager::createInstance();
	ZLQtDialogManager::createInstance();
	ZLUnixCommunicationManager::createInstance();
	ZLQtImageManager::createInstance();
	ZLEncodingCollection::instance().registerProvider(new IConvEncodingConverterProvider());

	ZLKeyUtil::setKeyNamesFileName("keynames-qt4.xml");
}

ZLPaintContext *ZLibrary::createContext() {
	return new ZLQtPaintContext();
}

void ZLibrary::run(ZLApplication *application) {
	ZLDialogManager::instance().createApplicationWindow(application);
	application->initWindow();
	qApp->exec();
	delete application;
}