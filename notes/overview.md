# ThingsBoard Local Water System Monitoring Dashboard

**Project: Interactive SCADA-style dashboard for home water system (2 tanks, 1 pump, 3 wells, sensors) using ThingsBoard CE on Raspberry Pi 5**

## Project Overview

Build a self-hosted IoT dashboard using ThingsBoard Community Edition to visualize and monitor:

- 2 water tanks (levels, perhaps alarms for low/high)
- 1 pump (on/off status, runtime, control if RPC supported)
- 3 water wells (status, perhaps flow/pressure)
- 2 flow sensors
- 5 temperature sensors
- 3 pressure sensors
- 2 pressure switches

Data source: MQTT via locally installed Mosquitto on the Pi (sensors publish JSON telemetry).  
Dashboard: Real-time gauges, cards, time-series charts, SCADA symbols (tanks/pumps/pipes with dynamic fill/color/animation).

Why local on Pi 5: Zero cost, full privacy, no limits, accessible via local network or secure remote (VPN/Tailscale).

## Phase 1: Prerequisites & Hardware Check

1. Raspberry Pi 5 setup
   - 64-bit Raspberry Pi OS (latest via Raspberry Pi Imager)
   - Enable SSH/VNC if needed (`raspi-config`)
   - Update system:
     ```bash
     sudo apt update && sudo apt full-upgrade -y && sudo reboot
     ```
   - At least 8GB RAM model preferred (Docker + ThingsBoard can use 2-4GB under load)
   - Stable power supply and cooling (fan/heatsink recommended)

2. Install Docker & Docker Compose on Pi
   - Follow official: <https://docs.docker.com/engine/install/raspberry-pi-os/>
   - Quick commands:
     ```bash
     curl -fsSL https://get.docker.com -o get-docker.sh
     sudo sh get-docker.sh
     sudo usermod -aG docker $USER
     ```
   - Log out/in or reboot
   - Verify:
     ```bash
     docker compose version  # Should show v2+
     ```

3. Optional: Static IP for Pi (easier access)
   - Edit `/etc/dhcpcd.conf` or use router reservation
   - Example fixed IP: `192.168.1.100`

## Phase 2: Install ThingsBoard CE via Docker (Recommended Simple Setup)

Use single-container `tb-postgres` image with in-memory queue (perfect for your low-scale home setup; avoids Kafka overhead on Pi).

1. Create project directory
   ```bash
   mkdir ~/thingsboard-water && cd ~/thingsboard-water
   ```

2. Create `docker-compose.yml`
   ```bash
   nano docker-compose.yml
   ```

Paste (adapted for ARM64/Pi compatibility; latest as of 2026):

```yaml
version: '3.8'
services:
  thingsboard:
    restart: always
    image: thingsboard/tb-postgres:latest  # Bundles Postgres + in-memory queue
    ports:
      - "8080:8080"                        # Web UI
      - "1884:1883"                        # ThingsBoard MQTT endpoint (use this for Mosquitto bridge)
      - "5683-5688:5683-5688/udp"          # CoAP/LwM2M if needed later
    environment:
      TB_QUEUE_TYPE: in-memory
      LOAD_DEMO: "true"                    # Optional: loads sample data/dashboards (good for testing)
    volumes:
      - tb-data:/data
      - tb-logs:/var/log/thingsboard
volumes:
  tb-data:
  tb-logs:
```

Start ThingsBoard:

```bash
docker compose up -d
docker compose logs -f   # Watch for "ThingsBoard started successfully" (~2-5 min first run)
```

Access the UI:

- Browser: `http://<pi-ip>:8080` (e.g., `http://192.168.1.100:8080`)
- Default logins (change immediately):
  - System Admin: `sysadmin@thingsboard.org / sysadmin`
  - Tenant Admin: `tenant@thingsboard.org / tenant` (use this for your project)

Troubleshooting:

- Check container: `docker ps`
- Logs: `docker compose logs thingsboard`
- High CPU? Limit resources in compose: add `mem_limit: 3g` under `thingsboard` service
- Port conflict? Change host ports (e.g., `"18080:8080"`)

## Phase 3: MQTT & Device Setup

MQTT broker: local Mosquitto on the Pi (port `1883`).

ThingsBoard ingestion path: bridge/forward selected Mosquitto topics to ThingsBoard MQTT endpoint on port `1884`.

### Create Device

1. Login as `tenant@thingsboard.org`
2. `Devices` -> `+` -> Name: `WaterSystemMain` (or separate devices per well/pump)
3. Copy Access Token (e.g., `ABC123DEF456...`)

### Sensor MQTT Config

- Broker: `<pi-ip>` port `1883` (your local Mosquitto)
- Auth: your Mosquitto username/password or cert config
- Topic: your local telemetry topic (for example `water/system/telemetry`)
- Payload example (JSON):

```json
{
  "tank1_level": 72.5,
  "tank2_level": 45.0,
  "pump_status": true,
  "flow_sensor1": 8.2,
  "temp_sensor1": 23.4,
  "pressure_sensor1": 2.1,
  "well1_status": "active"
}
```

### Bridge Mosquitto to ThingsBoard

Configure Mosquitto bridge/routing so telemetry is forwarded to ThingsBoard at:

- Host: `127.0.0.1` (or `<pi-ip>`)
- Port: `1884`
- Topic in ThingsBoard: `v1/devices/me/telemetry`
- Username: ThingsBoard device Access Token
- Password: (blank)

Test publish with a tool like MQTT Explorer or `mosquitto_pub` to your Mosquitto topic, then verify telemetry appears in ThingsBoard device latest values.

Optional: Create Assets (e.g., `Tank1`, `Pump`) and relations for better organization.

## Phase 4: Build the Dashboard

### Create New Dashboard

- `Dashboards` -> `+` -> Name: `Water System Monitor`
- Layout: Fullscreen or SCADA (for symbol-based)

### Add Widgets (drag from right panel)

- Tanks: Use `Value Card` or `Gauge` for levels; bind to `tank1_level` attribute
- Advanced: Use `Image` widget + custom SVG tank with dynamic fill (via CSS/alias)
- Pump: Digital LED or Button widget (for status); color change (green/red)
- If pump control is needed: Enable RPC (server-side method `setPump` -> on/off)
- Sensors: Multiple `Cards` or `Time Series` line charts; group temps/pressures/flows
- SCADA symbols: Use built-in library (tanks, pumps, pipes) from widgets -> SCADA
- Bind states (e.g., pump on -> animate running)
- Dynamic colors (e.g., pressure > 3 -> red)
- Alarms: Alarm widget for thresholds (low tank, high pressure)
- Layout tip: Use `Entity Alias` (e.g., `All Sensors`) for dynamic binding

### Make Interactive

- Add states/navigation (click pump -> detailed view)
- Test real-time updates

### Export/Backup Dashboard

- `Dashboards` -> Export JSON for version control

## Phase 5: Remote Access (Secure)

- Local network: `http://<pi-ip>:8080`
- Remote options (pick one):
  - Tailscale/ZeroTier (easiest, free, secure VPN) - install on Pi + client devices
  - WireGuard/OpenVPN on router/Pi
  - Nginx reverse proxy + Let's Encrypt (HTTPS) + port forward `443` (more advanced)

Avoid direct port forward `8080` without HTTPS/firewall.

## Phase 6: Optimization & Maintenance

- Monitor Pi resources: `htop`, `docker stats`
- Auto-start: Docker compose already has `restart: always`
- Backup: Regularly copy `~/thingsboard-water` volumes or export DB
- Update:
  ```bash
  docker compose pull && docker compose up -d
  ```
- Resources:
  - <https://thingsboard.io/docs/user-guide/scada/> (SCADA widgets)
  - <https://thingsboard.io/docs/user-guide/dashboards/> (dashboards)

## Milestones Checklist

- [ ] Pi OS updated + Docker installed
- [ ] ThingsBoard running + UI accessible
- [ ] MQTT test publish -> see telemetry in Devices
- [ ] Basic dashboard with 2-3 widgets
- [ ] Full system layout + real-time from sensors
- [ ] Alarms configured
- [ ] Remote access tested

Start with Phase 1-2 on the Pi, test MQTT, then build dashboard.

Good luck - ping if you need tweaks or example widget configs.
