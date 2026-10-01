### New
- New IRC chat style: one row per message with the time in blue, then the sender's name and the message. Wrapped lines stay lined up under the message text. It works in channel chat and DMs on every board with a Chat Style setting, and you can pick it in the web config page.
- T-Display P4: attaching the keyboard expansion in portrait now offers to switch to landscape. A 10-second countdown runs before the reboot. Reboot now (or Enter) skips the wait, and Cancel (or Esc) keeps portrait. Removing the keyboard leaves the orientation unchanged.
- T-Display P4: in landscape with the keyboard expansion, Right moves from the channel list into the chat and Left moves back. In the chat, Up and Down step through messages. In the list, they switch channels.

### Changed
- The acknowledgement marker is now a small `[A]` instead of `[ACK]` in every chat style. In Bubbles, your acknowledged messages are tagged `ME` with `[A]` beside it instead of `ME (ACK)`.
- Tools → Announce now asks before it sends NODEINFO and telemetry to the mesh. Choosing No sends nothing and doesn't start the cooldown.
- T-Display P4: the Small font size is smaller, so more lines fit on the screen.
