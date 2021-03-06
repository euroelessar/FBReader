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

#ifndef __ZLIMAGE_H__
#define __ZLIMAGE_H__

#include <string>

#include <shared_ptr.h>

#include <ZLMimeType.h>

class ZLNetworkRequest;

class ZLImage {

protected:
	ZLImage();

public:
	virtual ~ZLImage();
	virtual bool isSingle() const = 0;
	virtual shared_ptr<ZLNetworkRequest> synchronizationData() const;
	virtual bool good() const = 0;
};

class ZLSingleImage : public ZLImage {

protected:
	ZLSingleImage(shared_ptr<ZLMimeType> mimeType);
	virtual ~ZLSingleImage();

public:
	bool isSingle() const { return true; }
	shared_ptr<ZLMimeType> mimeType() const;
	bool good() const;
	virtual const shared_ptr<std::string> stringData() const = 0;

private:
	shared_ptr<ZLMimeType> myMimeType;
};

class ZLMultiImage : public ZLImage {

protected:
	ZLMultiImage();
	virtual ~ZLMultiImage();

public:
	bool isSingle() const { return false; }
	bool good() const;
	virtual unsigned int rows() const = 0;
	virtual unsigned int columns() const = 0;
	virtual shared_ptr<const ZLImage> subImage(unsigned int row, unsigned int column) const = 0;
};

inline ZLImage::ZLImage() {}
inline ZLImage::~ZLImage() {}

inline ZLSingleImage::ZLSingleImage(shared_ptr<ZLMimeType> mimeType) : myMimeType(mimeType) {}
inline ZLSingleImage::~ZLSingleImage() {}
inline shared_ptr<ZLMimeType> ZLSingleImage::mimeType() const { return myMimeType; }

inline ZLMultiImage::ZLMultiImage() : ZLImage() {}
inline ZLMultiImage::~ZLMultiImage() {}

#endif /* __ZLIMAGE_H__ */
