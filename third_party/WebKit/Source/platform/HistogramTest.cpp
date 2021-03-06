// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "platform/Histogram.h"

#include "base/metrics/histogram_samples.h"
#include "base/test/simple_test_tick_clock.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace blink {

class TestCustomCountHistogram : public CustomCountHistogram {
 public:
  TestCustomCountHistogram(const char* name,
                           base::HistogramBase::Sample min,
                           base::HistogramBase::Sample max,
                           int32_t bucket_count)
      : CustomCountHistogram(name, min, max, bucket_count) {}

  base::HistogramBase* Histogram() { return histogram_; }
};

TEST(ScopedUsHistogramTimerTest, Basic) {
  TestCustomCountHistogram scoped_us_counter("test", 0, 10000000, 50);
  {
    base::SimpleTestTickClock clock;
    ScopedUsHistogramTimer timer(scoped_us_counter, &clock);
    clock.Advance(TimeDelta::FromMilliseconds(500));
  }
  // 500ms == 500000us
  EXPECT_EQ(500000, scoped_us_counter.Histogram()->SnapshotSamples()->sum());
}

}  // namespace blink
