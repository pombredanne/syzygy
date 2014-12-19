// Copyright 2014 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "syzygy/kasko/waitable_timer_impl.h"

#include <windows.h>

#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "gtest/gtest.h"

namespace kasko {

TEST(WaitableTimerImplTest, BasicTest) {
  base::Time start = base::Time::Now();
  scoped_ptr<WaitableTimer> instance =
      WaitableTimerImpl::Create(base::TimeDelta::FromMilliseconds(100));
  ASSERT_TRUE(instance);
  instance->Start();
  // Wait up to 5000 ms.
  ASSERT_EQ(WAIT_OBJECT_0, ::WaitForSingleObject(instance->GetHANDLE(), 5000));
  EXPECT_LT(50, (base::Time::Now() - start).InMilliseconds());
  EXPECT_GT(500, (base::Time::Now() - start).InMilliseconds());
}

}  // namespace kasko
