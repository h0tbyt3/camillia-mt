### New
- Wardriving mode, off by default: turn it on from Settings → Wardriving (next to the GPS toggle), from web config → Node Management, or with `nodes: wardriveLog: true` in the YAML config. It only appears on boards with storage. The Settings row shows when it can't log, such as no GPS fix, log full or no storage.
- With Wardriving on, every radio sighting is logged with your own GPS position to `/camillia/wardrive.csv`. Each node gets at most one line every 30 seconds, or sooner once you've moved 50 m.
- The wardrive log stops when it reaches an eighth of the storage, up to 64 MB, and shows "log full". In web config, the Node Management page shows session counters and has Download Wardrive Log and Clear Wardrive Log buttons.
- With Wardriving on, the node export (`/nodes.csv`) and the SD node archive record where your device was when it best heard each node. New `mapLat`/`mapLon` columns use the node's own position when it has one and that heard position otherwise, ready for map uploads.
- With Wardriving on, the Discovery screen shows a status line with GPS state (satellite count, no fix or GPS off) and how many nodes and lines the log has taken. On the T-Deck Pro it shows only fix state and node count, so the e-paper doesn't refresh as often.

### Changed
- Blinking new-message marks in a channel or DM now clear after you've had that conversation open for 15 seconds, not only when you leave it. A new message restarts the 15 seconds.
- T-Deck Pro: when weather is shown, the at-a-glance header centres the node name and time in the left half and the weather in the right half.
- Node exports that include archived nodes now pad older archive rows with empty fields, so every row has as many columns as the header.
