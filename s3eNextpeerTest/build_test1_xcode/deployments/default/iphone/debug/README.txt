This folder contains an application deployed using the Marmalade SDK.

    Application : test1
        Version : 0.0.1
    SDK Version : 5.2.2 [303458]
  Date Deployed : Sun Feb 26 12:07:56 2012
      Target OS : iphone (iOS (iPhone, iPad, iPod))
  Configuration : Debug

OS Specific instructions
------------------------

In this folder you will find a ".app.zip" file which is an iPhone application
package, and a ".ipa" file which is the same thing but packaged for use
by iTunes directly.

As part of the deployment process this application may have been signed
already.  If you want to resign the application you and use the "sign_app.py"
script, a copy of which can also be found in this folder.  For more
inforamtion on the signing process see the contents of the sign_app.py script.
All signing must be performed on an Apple Mac with the iPhone SDK installed.

The following steps can be used to install the ".ipa" on a device:

    1.  On windows or mac, double click the .ipa file to open with iTunes.
    2.  Go to the Applications tab on iTunes and ensure there is a tick against
        the app.
    3.  Sync your device in iTunes.
    4.  In you want to replace an alreasy installed version you will have
        to explicitly remove the old version of the app from the device
        before installing it again.

The following steps can be used to install the ".app.zip" on a device:

    1.  Copy the ".app.zip" onto a Mac with the iPhone SDK installed.
    2.  Double click the ".app.zip" file to extact the ".app".
    3.  Use the Xcode organiser windows to install the ".app".
