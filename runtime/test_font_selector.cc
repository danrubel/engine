// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flutter/runtime/test_font_selector.h"
#include "flutter/lib/ui/ui_dart_state.h"
#include "flutter/runtime/test_font_data.h"
#include "flutter/sky/engine/platform/fonts/SimpleFontData.h"
#include "third_party/skia/include/core/SkTypeface.h"

namespace blink {

void TestFontSelector::Install() {
  auto font_selector = adoptRef(new TestFontSelector());
  UIDartState::Current()->set_font_selector(font_selector);
}

TestFontSelector::TestFontSelector() = default;

TestFontSelector::~TestFontSelector() = default;

PassRefPtr<FontData> TestFontSelector::getFontData(
    const FontDescription&,
    const AtomicString& familyName) {
  if (test_font_data_ != nullptr) {
    return test_font_data_;
  }

  auto typeface = SkTypeface::MakeFromStream(GetTestFontData().release());

  FontPlatformData platform_data(typeface, "Ahem", 14.0, false, false,
                                 FontOrientation::Horizontal, false);

  test_font_data_ =
      SimpleFontData::create(platform_data, CustomFontData::create());

  return test_font_data_;
}

void TestFontSelector::willUseFontData(const FontDescription&,
                                       const AtomicString& familyName,
                                       UChar32) {}

unsigned TestFontSelector::version() const {
  return 0;
}

void TestFontSelector::fontCacheInvalidated() {}

}  // namespace blink
