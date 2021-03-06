// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_FAKE_EXTENSION_PROVIDER_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_FAKE_EXTENSION_PROVIDER_H_

#include <memory>

#include "chrome/browser/chromeos/file_system_provider/extension_provider.h"
#include "chrome/browser/chromeos/file_system_provider/provided_file_system_interface.h"
#include "chrome/browser/chromeos/file_system_provider/provider_interface.h"

class Profile;

namespace chromeos {
namespace file_system_provider {

class ProvidedFileSystemInfo;

class FakeExtensionProvider : public ExtensionProvider {
 public:
  FakeExtensionProvider();
  ~FakeExtensionProvider() override {}

  // ExtensionProvider override.
  std::unique_ptr<ProvidedFileSystemInterface> CreateProvidedFileSystem(
      Profile* profile,
      const ProvidedFileSystemInfo& file_system_info) override;
};

}  // namespace file_system_provider
}  // namespace chromeos

#endif  // CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_FAKE_EXTENSION_PROVIDER_H_
