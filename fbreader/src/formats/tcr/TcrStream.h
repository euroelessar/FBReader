/*
 * Copyright (C) 2004-2013 Geometer Plus <contact@geometerplus.com>
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

#ifndef __TCRSTREAM_H__
#define __TCRSTREAM_H__

#include <ZLInputStream.h>

class ZLFile;

class TcrStream : public ZLInputStream {

public:
	TcrStream(const ZLFile &file);
	virtual ~TcrStream();
	bool open();
	virtual void close();

	std::size_t read(char *buffer, std::size_t maxSize);
	void seek(int offset, bool absoluteOffset);
	std::size_t offset() const;
	std::size_t sizeOfOpened();

protected:
	std::string myDictionary[256];
	std::string myBuffer;
	shared_ptr<ZLInputStream> myBase;
	std::size_t myOffset;
};

#endif /* __TCRSTREAM_H__ */
