/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#include "tensorflow/lite/profiling/memory_info.h"

#ifdef __linux__
#include <malloc.h>
#include <sys/resource.h>
#include <sys/time.h>
#endif

namespace tflite {
namespace profiling {
namespace memory {

const int MemoryUsage::kValueNotSet = 0;

MemoryUsage GetMemoryUsage() {
  MemoryUsage result;
#ifdef __linux__
  rusage res;
  if (getrusage(RUSAGE_SELF, &res) == 0) {
    result.max_rss_kb = res.ru_maxrss;
  }
  const auto mem = mallinfo();
  result.total_allocated_bytes = mem.uordblks;
#endif
  return result;
}

}  // namespace memory
}  // namespace profiling
}  // namespace tflite
