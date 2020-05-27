# node-virtualcam

NOTE: This package is a work-in-progress. No support is provided, use at own risk.

## Installation

This package is Windows-only for now and not yet published on npm.

From admin command prompt:
```sh
npm install --global --production windows-build-tools --vs2015
```
If this gets stuck, see https://github.com/felixrieseberg/windows-build-tools/issues/172#issuecomment-484091133.
Also, see [StackOverflow](https://stackoverflow.com/questions/21658832/npm-install-error-msb3428-could-not-load-the-visual-c-component-vcbuild-ex#comment91997415_39235952) on why `--vs2015` is needed.

Install/build package:
```sh
npm install
```

Run sample:
```sh
node samples\sample.js
```

The package uses [obs-virtual-cam](https://github.com/Fenrirthviti/obs-virtual-cam/releases) which has to be installed separately. Note that the obs-virtual-cam installer assumes an OBS Studio installation and will fail otherwise. You can also download and extract the obs-virtual-cam zip package directly without installing OBS Studio. After unzipping, simply run `regsvr32 "obs-virtualcam\bin\32bit\obs-virtualsource.dll"` from an elevated command prompt to install the virtual camera device. Use `regsvr32 /u "obs-virtualcam\bin\32bit\obs-virtualsource.dll"` to uninstall it again.


