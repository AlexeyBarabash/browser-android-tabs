// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

(async function() {
  TestRunner.addResult(`Unit test for release note\n`);


  Help.releaseNoteText = [
    {version: 3},
    {version: 4},
    {version: 5},
  ];

  function testMaybeShowInDrawer(lastSeenVersion) {
    TestRunner.addResult(`Last seen version: ${lastSeenVersion}`);
    TestRunner.addSniffer(UI.viewManager, 'showView', onShowView);
    var showedReleaseNote = false;

    Help._showReleaseNoteIfNeeded(lastSeenVersion, Help.latestReleaseNote().version);

    function onShowView() {
      showedReleaseNote = true;
    }
    if (showedReleaseNote)
      TestRunner.addResult(`Showed release note in drawer - version: ${Help.latestReleaseNote().version}`);
    else
      TestRunner.addResult('Did not show release note drawer');
  }

  TestRunner.runTestSuite([
    function getLatestReleaseNote(next) {
      var lastSeenVersion = 4;
      testMaybeShowInDrawer(lastSeenVersion);
      next();
    },
    function getReleaseNoteTwoVersionsAhead(next) {
      var lastSeenVersion = 3;
      testMaybeShowInDrawer(lastSeenVersion);
      next();
    },
    function alreadySeenReleaseNote(next) {
      var lastSeenVersion = 5;
      testMaybeShowInDrawer(lastSeenVersion);
      next();
    },
    function doNotShowReleaseNoteOnFreshProfile(next) {
      var lastSeenVersion = 0;
      testMaybeShowInDrawer(lastSeenVersion);
      TestRunner.addResult(`Release note version in setting: ${Help.releaseNoteVersionSetting().get()}`);
      next();
    },
  ]);
})();
