// Copyright 2018 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_TEST_SCOPED_OS_INFO_OVERRIDE_WIN_H_
#define BASE_TEST_SCOPED_OS_INFO_OVERRIDE_WIN_H_

#include <memory>

#include "base/macros.h"

namespace base {
namespace win {
class OSInfo;
}  // namespace win
}  // namespace base

namespace base {
namespace test {

// Helper class to override info returned by base::win::OSInfo::GetIntance()
// for the lifetime of this object. Upon destruction, the original info at time
// of object creation is restored.
class ScopedOSInfoOverride {
 public:
  // Types of windows machines that can be used for overriding.  Add new
  // machine types as needed.
  enum class Type {
    kWin10Pro,
    kWin10Home,
  };

  explicit ScopedOSInfoOverride(Type type);
  ~ScopedOSInfoOverride();

 private:
  using UniqueOsInfo =
      std::unique_ptr<base::win::OSInfo, void (*)(base::win::OSInfo*)>;

  static UniqueOsInfo CreateInfoOfType(Type type);

  // The OSInfo taken by this instance at construction and restored at
  // destruction.
  base::win::OSInfo* original_info_;

  // The OSInfo owned by this scoped object and which overrides
  // base::win::OSInfo::GetIntance() for the lifespan of the object.
  UniqueOsInfo overriding_info_;

  // Because the dtor of OSInfo is private, a custom deleter is needed to use
  // unique_ptr.
  static void deleter(base::win::OSInfo* info);

  DISALLOW_COPY_AND_ASSIGN(ScopedOSInfoOverride);
};

}  // namespace test
}  // namespace base

#endif  // BASE_TEST_SCOPED_OS_INFO_OVERRIDE_WIN_H_
