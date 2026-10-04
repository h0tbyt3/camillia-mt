### New
- **Chat Server**: catch up on channel messages you missed while the device was off or out of range. A chat server is a node running camillia-chat-server firmware that keeps channel messages and sends back the ones you missed. It covers every channel you share with it (same name and key). Direct messages are not included.
- The **Chat Server** setting on the Config screen (**Catch-up** in Web Config, under Modules) has three modes: **Off**, **Automatic** (checks at startup and every 15 minutes) and **Manual only** (checks only when you ask).
- The device finds a server on its own. It searches up to 3 hops away at startup, then every hour until one answers, and uses the first server that shares at least one of your channels. It keeps that server, even if it stops answering, until you clear it.
- **Check for Messages Now**, on the Config screen and in Web Config under Utilities > Diagnostics, asks the server right away, at most once every 5 minutes.
- To pick a server yourself, choose **Chat Server** in a node's menu on the Nodes screen, or enter its short name or node ID (!aabbccdd) under **Chat Server Node** in Web Config. To forget the server and look for a new one, select **Chat Server Node** on the Config screen or clear that box in Web Config.
- Missed messages appear in the channel at the time they were sent, marked with a refresh icon (CS on the Cardputer). Messages you already have are not repeated, ignored nodes stay hidden, muted channels stay silent, and each batch alerts once rather than once per message.
- The Live feed shows when a chat server is found, when it can't be reached, and when it is reachable again.
- If the device's clock is not set, it takes the time from the chat server, unless **Time and Date** is set to Manual.
- New messages you receive now blink until you have viewed their channel or DM and then moved to another channel or screen, or the display has gone to sleep. This works in every chat style. Not on the T-Deck Pro.

### Changed
- The Meshtastic Store & Forward client is removed and replaced by the chat server. The **Store&Fwd Client** and **Request S&F Replay** rows, the Web Config Store & Forward settings and the **Request Replay Now** button are gone. Store & Forward traffic still shows in the Live feed.
- After updating, a device that had the Store & Forward client on (the old default) starts with Chat Server set to **Automatic** and begins looking for a chat server. Set it to Off if your mesh has none. A pinned Store & Forward router is cleared. New installs start with Chat Server **Off**.
- Exported configs (config.yaml) now include the chat server settings. Older exports with Store & Forward settings still import; those settings are ignored.


### Update (v5.7.1)
### Changed
- Running "Check chat server" before a chat server has been found now starts a search for one right away instead of showing "No chat server yet". You can repeat it every 5 minutes, the same as an ordinary check.
