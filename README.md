# ThingsBoard Milano Water Project (MWP)

A comprehensive SCADA-style IoT dashboard for monitoring home water systems using ThingsBoard Community Edition on Raspberry Pi.

## 📋 Project Overview

**ThingsBoard MWP** is a self-hosted IoT monitoring solution that provides real-time visualization and control of residential water infrastructure. Built specifically for Raspberry Pi ARM64 architecture, it monitors water tanks, pumps, flow sensors, pressure systems, and temperature sensors through MQTT connectivity.

### 🎯 Key Features

- **Real-time SCADA Dashboard** - Tank levels, pump status, flow rates, pressure monitoring
- **MQTT Integration** - Seamless connection with existing water sensors via Mosquitto broker
- **Alarm System** - Configurable thresholds with notifications for critical conditions
- **Docker Deployment** - Easy installation and updates on Raspberry Pi
- **Privacy-Focused** - Local, self-hosted solution with no cloud dependencies

### 🏗️ System Architecture

- **2 Water Tanks** - Level monitoring with percentage capacity
- **3 Well Pumps + 1 Irrigation Pump** - Status tracking and runtime monitoring
- **5 Flow Sensors** - Gallons per minute and daily totals
- **3 Pressure Sensors** - House, well, and irrigation line monitoring
- **5 Temperature Sensors** - System, house, well, irrigation, and air temperature
- **2 Pressure Switches** - Tank and septic system monitoring

## 📚 Critical Resources

| Resource | Description | Location |
|----------|-------------|----------|
| **Installation Guide** | Complete Docker setup and configuration | [`notes/install.md`](notes/install.md) |
| **Update Guide** | Safe update procedures and version management | [`notes/update.md`](notes/update.md) |
| **Uninstall Guide** | Complete removal and cleanup instructions | [`notes/uninstall.md`](notes/uninstall.md) |
| **Data Structures** | MQTT payload formats and sensor data mapping | [`notes/data-items.md`](notes/data-items.md) |
| **Telemetry Schema** | Canonical data format for ThingsBoard | [`notes/telemetry-canonical.md`](notes/telemetry-canonical.md) |
| **Dashboard Design** | SCADA layout and widget specifications | [`notes/dashboard-pages.md`](notes/dashboard-pages.md) |
| **Alarm System** | Threshold configuration and rule chains | [`notes/alarm-foundation.md`](notes/alarm-foundation.md) |
| **System Architecture** | Complete project overview and setup phases | [`notes/overview.md`](notes/overview.md) |

## 🚀 Quick Start

### Prerequisites
- Raspberry Pi 5 (8GB RAM recommended)
- Docker and Docker Compose installed
- Basic Linux command line knowledge

### Installation
```bash
# Clone or navigate to project directory
cd /home/pi/ThingsboardMWP

# Follow detailed installation steps
cat notes/install.md
```

**Default Login Credentials:**
- **System Admin:** `sysadmin@thingsboard.org` / `sysadmin`
- **Tenant Admin:** `tenant@thingsboard.org` / `tenant`
- **⚠️ Change passwords immediately after first login!**

## ✅ Installation Verification

After installation, verify everything is working:

```bash
# Check containers are running
cd /home/pi/ThingsboardMWP/config && docker compose ps

# Verify web interface
curl -s http://localhost:8080 | grep -i "thingsboard"

# Check API connectivity
curl -s http://localhost:8080/api/components/VERSION | jq .version 2>/dev/null || echo "API not responding"
```

Expected output:
- ✅ PostgreSQL and ThingsBoard containers running
- ✅ Web interface accessible at `http://localhost:8080`
- ✅ API returning version information

## 🔄 Updates & Maintenance

### Check for Updates
```bash
# Check current version
cd /home/pi/ThingsboardMWP/config
docker compose exec thingsboard cat /usr/share/thingsboard/bin/thingsboard.jar | head -20 | grep -i version

# Check latest available
docker pull thingsboard/tb-node:latest --dry-run 2>/dev/null || echo "Check Docker Hub manually"
```

### Quick Update Process
```bash
cd /home/pi/ThingsboardMWP/config

# Backup (recommended)
docker compose exec postgres pg_dump -U postgres thingsboard > backup_$(date +%Y%m%d).sql

# Update and restart
docker compose pull && docker compose up -d

# Verify
docker compose logs --tail=10 thingsboard
```

See [`notes/update.md`](notes/update.md) for complete update procedures and rollback instructions.

## 🏗️ Development Phases

- **✅ Phase 1:** Raspberry Pi setup and Docker installation
- **✅ Phase 2:** ThingsBoard CE deployment and configuration
- **🔄 Phase 3:** MQTT bridge setup and device creation *(Next)*
- **⏳ Phase 4:** SCADA dashboard development
- **⏳ Phase 5:** Alarm system implementation
- **⏳ Phase 6:** Production optimization and monitoring

## 🔧 System Requirements

- **Hardware:** Raspberry Pi 5 (8GB RAM minimum)
- **OS:** Raspberry Pi OS (64-bit) or Ubuntu 20.04+
- **Storage:** 16GB SD card minimum, SSD recommended
- **Network:** Stable internet for initial setup, local network for operation
- **Docker:** Version 20.10+ with Compose v2.0+

## 📞 Support & Troubleshooting

### Common Issues
- **Port conflicts:** Ensure ports 8080, 1884, 7070, 8883 are available
- **Memory issues:** Monitor with `docker stats` and adjust `JAVA_OPTS`
- **Database errors:** Check logs with `docker compose logs postgres`

### Getting Help
1. Check the detailed guides in the `notes/` directory
2. Review Docker container logs: `docker compose logs -f`
3. Verify system resources: `htop` and `df -h`
4. Check ThingsBoard logs: `docker compose logs thingsboard`

## 📄 License & Attribution

This project uses ThingsBoard Community Edition, which is licensed under Apache 2.0.

**Built for the Milano Water Project** - Self-hosted water infrastructure monitoring for privacy and reliability.

---

**Last Updated:** February 23, 2026  
**ThingsBoard Version:** CE 4.3.0.1  
**Status:** 🟢 Operational
