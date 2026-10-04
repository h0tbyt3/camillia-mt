# Wardriving

Features aimed at mapping Meshtastic nodes from a moving device
(T-Deck Plus first, but nothing here is board-specific).

Everything below except multi-GNSS hangs off one switch, **Wardriving**, off by
default: device **Settings → Wardriving** (beside the GPS toggle, on boards with
storage), web config → **Node Management**, or YAML `nodes: wardriveLog: true`.
It records where *this device* was, which is your own location history, so
nothing is recorded or exported unless it is on.

## 1. Heard position on every node

Most nodes never broadcast a POSITION packet, so their `latI`/`lonI` stay
empty. Each node now also records **where this device was** when it heard it,
taken from our own GPS fix:

- a **direct** sighting (hop count known and zero, so the RSSI is the node's own
  transmitter) beats a relayed one;
- between two of the same kind, the **stronger RSSI** wins.

Strongest-direct is the best single-point estimate of where a node actually is.
Only stamped while wardriving is on and the GPS has a fix, never from MQTT. Not
saved to NVS (cleared on reboot) -- but if the node archive is also on, a node
evicted while wardriving is written to the SD archive with its heard position.

New columns at the end of `/nodes.csv` (and of the SD eviction archive). The
heard columns are empty, and `mapSource` is only ever `node`, while wardriving
is off:

| column | meaning |
|---|---|
| `heardLatI`, `heardLonI` | our position at the winning sighting, degrees × 1e7 |
| `heardRssi` | RSSI of that sighting, dBm |
| `heardDirect` | 1 if it was a direct (0-hop) packet |
| `mapLat`, `mapLon` | **what to upload**: the node's own position if it has one, else the heard position, decimal degrees |
| `mapSource` | `node`, `heard-direct`, `heard-relayed`, or empty |

Columns were appended, so readers that go by header name keep working and the
archive restore parser (positional) is unaffected. Archive rows written before
these columns existed are padded with empty fields in the export, so every row
has as many columns as the header.

## 2. Wardrive log on the SD card

`/camillia/wardrive.csv` gets one line per radio sighting:

```
epoch,utc,nodeId,shortName,longName,rssi,snr,hops,portnum,chanIdx,lat,lon,altM,sats,hdop,speedKmh,nodeLat,nodeLon
```

- `lat`/`lon` are **our** position; `nodeLat`/`nodeLon` the node's own, if known.
- `hops` is empty when the packet did not say.
- At most one line per node every 30 s, or sooner after moving 50 m.
- Only radio packets, only with a GPS fix. Sightings without a fix are counted
  (at the same per-node rate a line would have been written), not logged.
- The per-node throttle tracks 512 nodes on boards with PSRAM, 64 without.
- The file is capped at an eighth of the storage, 64 MB at most (about 400 KB
  on the 3.3 MB internal-flash partition). At the cap logging stops -- shown as
  "log full" in Discovery, Settings and web config -- until you clear it.
- Written from the main loop in batches (SD shares the SPI bus with the radio);
  a crash or flat battery loses seconds, not the drive.

Web config → **Node Management**: on/off checkbox (applies without a reboot),
session counters, **Download Wardrive Log**, **Clear Wardrive Log**. Off by
default (`MY_WARDRIVE_LOG_EN`).

## 3. Discovery shows GPS and log state

While wardriving is on, the Discovery screen has a line under the summary:
`GPS 7 sat | Log 23/310` (nodes/lines), `No GPS fix | …`, `GPS off | …`, or
`… | Log full`. On the T-Deck Pro's e-paper it reads `GPS fix | Log: 23 node(s)`
instead, so the panel is not refreshed for every satellite or line. No more
finding out at upload time that the whole drive had no fix. The Settings row
says the same: `Wardriving: On (no GPS fix)`, `(log full)`, `(no storage)`.

## 4. Multi-GNSS (off by default)

Behind `-DMY_GPS_MULTI_GNSS=1`: sends `$PCAS04,7` (GPS + BeiDou + GLONASS on
CASIC/AT6558 parts such as the L76K) and `$PMTK353,1,1,1,0,1` for MediaTek
parts, once per boot when the NMEA stream is first confirmed.

Off by default because it made things worse in a field test on a T-Deck Plus:
2 satellites in use with it on versus 5 with stock firmware at the same spot.
Changing the constellation set restarts the L76K's search.

## Notes

- `RhinoConfig` gained `wardriveLogEnabled` at offset 1224 (the previous
  `sizeof(RhinoConfig)`), after `_reservedPad16`, per the append-only rule.
- Pure helpers live in `src/wardrive_util.h` with a host test:
  `g++ -std=c++17 -I src tools/test_wardrive_util.cpp && ./a.out`
