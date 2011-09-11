/*
 * Copyright (C) 2009-2010 Geometer Plus <contact@geometerplus.com>
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

#ifndef __ZLBLOCKTREENODE_H__
#define __ZLBLOCKTREENODE_H__

#include <map>
#include <vector>

#include <shared_ptr.h>

#include <ZLTypeId.h>
#include <ZLRunnable.h>
#include <ZLPaintContext.h>

// TODO: Rename ZLBlockTreeNode to ZLTreeNode
// Nowadays I see hierarchy in this way:
//
// ZLTreeNode
// |
// +-ZLTreeTitledNode -- simple node, as shown below
// | |
// | +- ZLTreeActionNode -- node with some action on click, i.e. BookNode at local library
// |
// +-ZLTreePageNode -- usually the leaf of the tree, smth like page with ZLDialogContent
//                     and some actions, i.e. BookInfo page at network library

class ZLBlockTreeView;

class ZLBlockTreeNode : public ZLObjectWithRTTI {

public:
	typedef std::vector<ZLBlockTreeNode*> List;

protected:
	struct Rectangle {
		const size_t Left;
		const size_t Top;
		const size_t Right;
		const size_t Bottom;

		Rectangle(size_t left, size_t vOffset, size_t right, size_t bottom);

		bool contains(size_t x, size_t y) const;
		bool operator < (const Rectangle &r) const;
	};

public:
	static const ZLTypeId TYPE_ID;

protected:
	ZLBlockTreeNode(ZLBlockTreeView &view);
	ZLBlockTreeNode(ZLBlockTreeNode *parent, size_t atPosition = -1);

public:
	virtual ~ZLBlockTreeNode();
	void clear();

public:
	ZLBlockTreeNode *parent() const;
	ZLBlockTreeNode *previous() const;
	ZLBlockTreeNode *next() const;
	const List &children() const;

	void open(bool openNotClose);
	bool isOpen() const;

protected:
	size_t level() const;

	ZLBlockTreeView &view();
	
public:
	// TODO: new API, there are listed methods of ZLTreeTitledNode
	// ** begin
	// Usually node looks like
	// +-------+---------------+
	// |       |  TITLE        |
	// | image |             > |
	// |       |  subtitle     |
	// +-------+---------------+
	// Name of book
	virtual std::string title() const { return std::string(); }
	// Short description
	virtual std::string subtitle() const { return std::string(); }
	// Url to image
	virtual std::string imageUrl() const { return std::string(); }
	// Or the image if there is no url
	virtual shared_ptr<ZLImage> image() const { return shared_ptr<ZLImage>(); }
	// Children should be requested from network only if we need them
	virtual void requestChildren() {}
	// Some action if there is no children, I suppose it should be at ZLTreeActionNode
	virtual void activate() {}
	// **end

public:
	// TODO: old API, remove all this methods
	// ** begin
	virtual void paint(ZLPaintContext &context, int vOffset) = 0;
	virtual int height(ZLPaintContext &context) const = 0;

	void onStylusPress(size_t x, size_t y);
	bool isOverHyperlink(size_t x, size_t y);

protected:
	void addHyperlink(size_t left, size_t top, size_t right, size_t bottom, shared_ptr<ZLRunnableWithKey> action);
	void removeAllHyperlinks();
	// **end

private:
	// myView should be renamed to myListener. Also I don't see any reasons
	// to store myView in every node, maximum level is not so big to suffer
	// from getting it from top parent
	ZLBlockTreeView &myView;
	ZLBlockTreeNode *myParent;
	size_t myChildIndex;

	List myChildren;
	// Should this be removed?
	bool myIsOpen;

	typedef std::map<Rectangle,shared_ptr<ZLRunnableWithKey> > LinkMap;
	LinkMap myHyperlinks;

private:
	ZLBlockTreeNode(const ZLBlockTreeNode&);
	const ZLBlockTreeNode &operator = (const ZLBlockTreeNode&);
};

//class ZLTreeActionNode : public ZLTreeNode {
//	static const ZLTypeId TYPE_ID;
//public:
//	// Some action if there is no children
//	virtual void activate() const {}
//};

#endif /* __ZLBLOCKTREENODE_H__ */
