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

#ifndef __ZLKEYBINDINGS_H__
#define __ZLKEYBINDINGS_H__

#include <map>
#include <string>

class ZLKeyBindings {

public:
	ZLKeyBindings(const std::string &name);
	~ZLKeyBindings();

	void bindKey(const std::string &key, const std::string &code);
	const std::map<std::string,std::string> &bindings() const;
	const std::string &actionId(const std::string &key) const;

private:
	void loadDefaultBindings();
	void loadCustomBindings();

public:
	void saveCustomBindings();

private:
	const std::string myName;
	std::map<std::string,std::string> myBindingsMap;
	bool myIsChanged;
};

#endif /* __KEYBINDINGS_H__ */
