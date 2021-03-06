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

#include "NetworkTreeNodes.h"

const ZLTypeId SearchCatalogTree::TYPE_ID(NetworkCatalogTree::TYPE_ID);

const ZLTypeId &SearchCatalogTree::typeId() const {
	return TYPE_ID;
}

SearchCatalogTree::SearchCatalogTree(RootTree *parent, shared_ptr<NetworkItem> item, std::size_t position) :
	NetworkCatalogTree(parent, item, position) {
	//TODO maybe remove this class
}

void SearchCatalogTree::requestChildren(shared_ptr<ZLNetworkRequest::Listener> listener) {
	notifySearchStarted();
	NetworkCatalogTree::requestChildren(listener);
}

void SearchCatalogTree::onChildrenReceived(NetworkItem::List &childrens, const std::string &error) {
	notifySearchStopped();
	NetworkCatalogTree::onChildrenReceived(childrens, error);
}
