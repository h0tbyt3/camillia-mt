### New
- Web Config has a new **Files** tab for the device's storage. You can browse folders, download files, upload one or more files with a progress bar, copy files, create folders, and delete files or whole folders. It uses the SD card, or internal flash on boards without a card slot (Heltec V4, Mesh Deck, CrowPanel 3.5).
- A **Web Files** setting on the device's Config screen turns the Files tab on or off. It is off by default and is not part of the YAML backup, so restoring a backup never turns it on. Changing it needs no reboot, and turning it off locks the files right away, even on a page that is already open.
- The Files tab only works while the device is on your WiFi network, never in access-point mode. On the Cardputer it appears as a Files section at the bottom of Web Config Lite.
- Uploads and copies are saved in full before they replace anything. If the connection drops or storage fills up, the old file stays as it was. Replacing an existing file always asks first.

### Changed
- In Web Config, the **WiFi** tab is gone. Saved WiFi networks are now under **Saved Networks** in the WiFi section of the Config tab, just below the SSID and password of the network in use.
