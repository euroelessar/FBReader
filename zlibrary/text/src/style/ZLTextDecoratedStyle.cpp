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

#include "ZLTextStyle.h"
#include "ZLTextStyleCollection.h"
#include "ZLTextDecoratedStyle.h"
#include <ZLTextStyleEntry.h>

static const std::string STYLE = "Style";

ZLTextStyleDecoration::ZLTextStyleDecoration(const std::string &name, int fontSizeDelta, ZLBoolean3 bold, ZLBoolean3 italic, int verticalShift, ZLBoolean3 allowHyphenations) :
	FontFamilyOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":fontFamily", std::string()),
	FontSizeDeltaOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":fontSize", -16, 16, fontSizeDelta),
	BoldOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":bold", bold),
	ItalicOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":italic", italic),
	VerticalShiftOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":vShift", verticalShift),
	AllowHyphenationsOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":allowHyphenations", allowHyphenations),
	myName(name) {
}

ZLTextFullStyleDecoration::ZLTextFullStyleDecoration(const std::string &name, int fontSizeDelta, ZLBoolean3 bold, ZLBoolean3 italic, short spaceBefore, short spaceAfter, short lineStartIndent, short lineEndIndent, short firstLineIndentDelta, int verticalShift, ZLTextAlignmentType alignment, double lineSpace, ZLBoolean3 allowHyphenations) : ZLTextStyleDecoration(name, fontSizeDelta, bold, italic, verticalShift, allowHyphenations),
	SpaceBeforeOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":spaceBefore", -10, 100, spaceBefore),
	SpaceAfterOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":spaceAfter", -10, 100, spaceAfter),
	LineStartIndentOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":leftIndent", -300, 300, lineStartIndent),
	LineEndIndentOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":rightIndent", -300, 300, lineEndIndent),
	FirstLineIndentDeltaOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":firstLineIndentDelta", -300, 300, firstLineIndentDelta),
	AlignmentOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":alignment", alignment),
	LineSpacePercentOption(ZLCategoryKey::LOOK_AND_FEEL, STYLE, name + ":lineSpacePercent", (lineSpace == 0.0) ? -1 : (int)(lineSpace * 100)) {
}

shared_ptr<ZLTextStyle> ZLTextStyleDecoration::createDecoratedStyle(const shared_ptr<ZLTextStyle> base) const {
	return new ZLTextPartialDecoratedStyle(base, *this);
}

shared_ptr<ZLTextStyle> ZLTextFullStyleDecoration::createDecoratedStyle(const shared_ptr<ZLTextStyle> base) const {
	return new ZLTextFullDecoratedStyle(base, *this);
}

const std::string &ZLTextPartialDecoratedStyle::fontFamily() const {
	const std::string &family = myDecoration.FontFamilyOption.value();
	return !family.empty() ? family : base()->fontFamily();
}

int ZLTextPartialDecoratedStyle::fontSize() const {
	return base()->fontSize() + myDecoration.FontSizeDeltaOption.value();
}

bool ZLTextPartialDecoratedStyle::bold() const {
	ZLBoolean3 b = myDecoration.BoldOption.value();
	return b == B3_UNDEFINED ? base()->bold() : (b == B3_TRUE);
}

bool ZLTextPartialDecoratedStyle::italic() const {
	ZLBoolean3 i = myDecoration.ItalicOption.value();
	return i == B3_UNDEFINED ? base()->italic() : (i == B3_TRUE);
}

bool ZLTextPartialDecoratedStyle::allowHyphenations() const {
	ZLBoolean3 a = myDecoration.AllowHyphenationsOption.value();
	return a == B3_UNDEFINED ? base()->allowHyphenations() : (a == B3_TRUE);
}

short ZLTextFullDecoratedStyle::firstLineIndentDelta(const ZLTextStyleEntry::Metrics &metrics) const {
	return alignment() == ALIGN_CENTER ? 0 : base()->firstLineIndentDelta(metrics) + myDecoration.FirstLineIndentDeltaOption.value();
}

const std::string &ZLTextFullDecoratedStyle::fontFamily() const {
	const std::string &family = myDecoration.FontFamilyOption.value();
	return !family.empty() ? family : base()->fontFamily();
}

int ZLTextFullDecoratedStyle::fontSize() const {
	return base()->fontSize() + myDecoration.FontSizeDeltaOption.value();
}

bool ZLTextFullDecoratedStyle::bold() const {
	ZLBoolean3 b = myDecoration.BoldOption.value();
	return b == B3_UNDEFINED ? base()->bold() : (b == B3_TRUE);
}

bool ZLTextFullDecoratedStyle::italic() const {
	ZLBoolean3 i = myDecoration.ItalicOption.value();
	return i == B3_UNDEFINED ? base()->italic() : (i == B3_TRUE);
}

ZLTextAlignmentType ZLTextFullDecoratedStyle::alignment() const {
	ZLTextAlignmentType a = (ZLTextAlignmentType)myDecoration.AlignmentOption.value();
	return a == ALIGN_UNDEFINED ? base()->alignment() : a;
}

bool ZLTextFullDecoratedStyle::allowHyphenations() const {
	ZLBoolean3 a = myDecoration.AllowHyphenationsOption.value();
	return a == B3_UNDEFINED ? base()->allowHyphenations() : (a == B3_TRUE);
}

const std::string &ZLTextPartialDecoratedStyle::colorStyle() const {
	const std::string &style = myDecoration.colorStyle();
	return style.empty() ? base()->colorStyle() : style;
}

const std::string &ZLTextFullDecoratedStyle::colorStyle() const {
	const std::string &style = myDecoration.colorStyle();
	return style.empty() ? base()->colorStyle() : style;
}

short ZLTextForcedStyle::lineStartIndent(const ZLTextStyleEntry::Metrics &metrics, bool rtl) const {
	ZLTextStyleEntry::Feature lengthType = rtl ?
		ZLTextStyleEntry::LENGTH_RIGHT_INDENT :
		ZLTextStyleEntry::LENGTH_LEFT_INDENT;
	return
		myEntry.isFeatureSupported(lengthType) ?
			myEntry.length(lengthType, metrics) :
			base()->lineStartIndent(metrics, rtl);
}

short ZLTextForcedStyle::lineEndIndent(const ZLTextStyleEntry::Metrics &metrics, bool rtl) const {
	ZLTextStyleEntry::Feature lengthType = rtl ?
		ZLTextStyleEntry::LENGTH_LEFT_INDENT :
		ZLTextStyleEntry::LENGTH_RIGHT_INDENT;
	return
		myEntry.isFeatureSupported(lengthType) ?
			myEntry.length(lengthType, metrics) :
			base()->lineEndIndent(metrics, rtl);
}

short ZLTextForcedStyle::spaceBefore(const ZLTextStyleEntry::Metrics &metrics) const {
	return
		myEntry.isFeatureSupported(ZLTextStyleEntry::LENGTH_SPACE_BEFORE) ?
			myEntry.length(ZLTextStyleEntry::LENGTH_SPACE_BEFORE, metrics) :
			base()->spaceBefore(metrics);
}

short ZLTextForcedStyle::spaceAfter(const ZLTextStyleEntry::Metrics &metrics) const {
	return
		myEntry.isFeatureSupported(ZLTextStyleEntry::LENGTH_SPACE_AFTER) ?
			myEntry.length(ZLTextStyleEntry::LENGTH_SPACE_AFTER, metrics) :
			base()->spaceAfter(metrics);
}

short ZLTextForcedStyle::firstLineIndentDelta(const ZLTextStyleEntry::Metrics &metrics) const {
	return
		myEntry.isFeatureSupported(ZLTextStyleEntry::LENGTH_FIRST_LINE_INDENT_DELTA) ?
			myEntry.length(ZLTextStyleEntry::LENGTH_FIRST_LINE_INDENT_DELTA, metrics) :
			base()->firstLineIndentDelta(metrics);
}

ZLTextAlignmentType ZLTextForcedStyle::alignment() const {
	return myEntry.isFeatureSupported(ZLTextStyleEntry::ALIGNMENT_TYPE) ? myEntry.alignmentType() : base()->alignment();
}

bool ZLTextForcedStyle::bold() const {
	ZLBoolean3 support = myEntry.fontModifier(ZLTextStyleEntry::FONT_MODIFIER_BOLD);
	return (support == B3_UNDEFINED) ? base()->bold() : (support == B3_TRUE);
}

bool ZLTextForcedStyle::italic() const {
	ZLBoolean3 support = myEntry.fontModifier(ZLTextStyleEntry::FONT_MODIFIER_ITALIC);
	return (support == B3_UNDEFINED) ? base()->italic() : (support == B3_TRUE);
}

int ZLTextForcedStyle::fontSize() const {
	if (myEntry.isFeatureSupported(ZLTextStyleEntry::LENGTH_FONT_SIZE)) {
		shared_ptr<ZLTextStyle> base = this->base();
		while (base->isDecorated()) {
			base = ((ZLTextDecoratedStyle&)*base).base();
		}
		ZLTextStyleEntry::Metrics metrics(base->fontSize(), 0, 0, 0);
		return myEntry.length(ZLTextStyleEntry::LENGTH_FONT_SIZE, metrics);
	} else {
		return base()->fontSize();
	}
}

const std::string &ZLTextForcedStyle::fontFamily() const {
	return (!ZLTextStyleCollection::Instance().OverrideSpecifiedFontsOption.value() &&
					myEntry.isFeatureSupported(ZLTextStyleEntry::FONT_FAMILY)) ?
						myEntry.fontFamily() : base()->fontFamily();
}

const std::string &ZLTextStyleDecoration::colorStyle() const {
	return myColorStyle;
}

void ZLTextStyleDecoration::setColorStyle(const std::string &colorStyle) {
	myColorStyle = colorStyle;
}
