# Raspberry Pi ThingsBoard Uninstall Guide

This guide provides safe uninstallation procedures for ThingsBoard CE from your Raspberry Pi system.

⚠️ **WARNING: These procedures will permanently delete your ThingsBoard data, dashboards, and configurations!**

## 📋 Quick Uninstall (Complete Removal)

```bash
# Navigate to your project directory
cd /home/pi/ThingsboardMWP

# Stop and remove everything (including volumes)
cd config && docker compose down -v

# Remove Docker images (optional, saves disk space)
docker image rm thingsboard/tb-node:4.3.0.1 postgres:16

# Remove project directory (optional)
cd /home/pi && rm -rf ThingsboardMWP

# Clean up unused Docker resources
docker system prune -f
```

## 📋 Manual Uninstall Steps

### Step 1: Stop ThingsBoard Services

```bash
# Navigate to config directory
cd /home/pi/ThingsboardMWP/config

# Stop containers
docker compose down
```

### Step 2: Remove Data Volumes (⚠️ DELETES ALL DATA)

```bash
# This removes PostgreSQL database and ThingsBoard data
docker compose down -v

# Verify volumes are removed
docker volume ls
```

### Step 3: Remove Docker Images (Optional)

```bash
# Remove ThingsBoard and PostgreSQL images
docker image rm thingsboard/tb-node:4.3.0.1
docker image rm postgres:16

# Clean up unused images
docker image prune -f
```

### Step 4: Remove Project Files

```bash
# Remove the entire project directory
cd /home/pi
rm -rf ThingsboardMWP

# Verify removal
ls -la | grep Thingsboard
```

## 🧹 System Cleanup (Optional)

### Remove Docker Resources

```bash
# Remove all unused containers, networks, and images
docker system prune -a -f

# Remove all unused volumes
docker volume prune -f

# Check disk space recovered
df -h
```

### Remove Docker Completely (Advanced)

⚠️ **This removes Docker entirely - ThingsBoard and all other containers will stop working!**

```bash
# Stop all containers
docker stop $(docker ps -aq)

# Remove Docker
sudo apt purge -y docker-ce docker-ce-cli containerd.io

# Remove Docker data directory
sudo rm -rf /var/lib/docker

# Remove Docker group membership
sudo deluser pi docker

# Clean up
sudo apt autoremove -y
```

## 🔍 Verification Steps

After uninstallation, verify everything is removed:

```bash
# Check no ThingsBoard containers running
docker ps -a | grep thingsboard

# Check no ThingsBoard images
docker images | grep thingsboard

# Check no ThingsBoard volumes
docker volume ls | grep tb-

# Check no ThingsBoard processes
ps aux | grep thingsboard

# Check port 8080 is free
netstat -tlnp | grep :8080
```

## 🛡️ Safety Precautions

### Backup Before Uninstalling

If you want to keep your data:

```bash
# Export dashboards (if accessible)
# Note: Requires ThingsBoard to be running
curl -X GET "http://localhost:8080/api/tenant/dashboards?pageSize=100&page=0" \
  -H "X-Authorization: Bearer YOUR_JWT_TOKEN" \
  > dashboards_backup.json

# Export devices
curl -X GET "http://localhost:8080/api/tenant/devices?pageSize=100&page=0" \
  -H "X-Authorization: Bearer YOUR_JWT_TOKEN" \
  > devices_backup.json
```

### Selective Removal Options

**Keep data but remove containers:**
```bash
cd /home/pi/ThingsboardMWP/config
docker compose down  # Keeps volumes
```

**Remove containers but keep images:**
```bash
cd /home/pi/ThingsboardMWP/config
docker compose down -v  # Removes volumes but keeps images
```

## 🔄 Reinstallation

To reinstall after complete removal:

```bash
# Clone or recreate project
mkdir -p /home/pi/ThingsboardMWP
cd /home/pi/ThingsboardMWP

# Copy config files back
# ... (recreate docker-compose.yml and config)

# Follow install.md instructions
```

## 🐛 Troubleshooting Uninstallation

### Stuck Containers

If containers won't stop:
```bash
# Force stop
docker kill $(docker ps -aq)

# Force remove
docker rm -f $(docker ps -aq)
```

### Permission Issues

If you get permission errors:
```bash
# Run with sudo
sudo docker compose down -v

# Or add user to docker group
sudo usermod -aG docker pi
# Then logout/login
```

### Disk Space Not Recovered

If disk space isn't freed:
```bash
# Check what Docker is using
docker system df

# Force cleanup
docker system prune -a --volumes -f
```

## 📊 Uninstall Summary

| Component | Removal Command | Data Loss Risk |
|-----------|----------------|----------------|
| Containers | `docker compose down` | None |
| Containers + Data | `docker compose down -v` | **High** |
| Docker Images | `docker image rm <image>` | None |
| Project Files | `rm -rf /path/to/project` | **High** |
| Docker System | `sudo apt purge docker-ce` | **Critical** |

## ✅ Success Indicators

After successful uninstallation:
- ✅ No Docker containers named "thingsboard" or "config-*"
- ✅ No ThingsBoard images in `docker images`
- ✅ No ThingsBoard volumes in `docker volume ls`
- ✅ Port 8080 is free (no longer in use)
- ✅ Project directory removed (optional)
- ✅ Disk space recovered (check with `df -h`)

---

**Uninstall Date:** [Date]  
**Status:** ✅ Complete / ⏳ In Progress / ❌ Issues Encountered

**Notes:**  
[Add any specific notes about your uninstallation process]