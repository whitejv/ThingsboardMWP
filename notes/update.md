# ThingsBoard Docker Update Guide

This guide provides safe update procedures for your ThingsBoard CE Docker installation on Raspberry Pi.

## 📋 Quick Update (Recommended)

```bash
# Navigate to config directory
cd /home/pi/ThingsboardMWP/config

# Backup current setup (optional but recommended)
docker compose exec postgres pg_dump -U postgres thingsboard > thingsboard_backup_$(date +%Y%m%d_%H%M%S).sql

# Stop services
docker compose down

# Update images
docker compose pull

# Start updated services
docker compose up -d

# Verify update
docker compose logs --tail=20 thingsboard
```

## 🔍 Check for Updates

### Check Current Version

```bash
# Check running ThingsBoard version
cd /home/pi/ThingsboardMWP/config
docker compose exec thingsboard cat /usr/share/thingsboard/bin/thingsboard.jar | head -20 | grep -i version

# Or check via API
curl -s http://localhost:8080/api/components/VERSION | jq .version
```

### Check Available Updates

```bash
# Check latest ThingsBoard image
docker pull thingsboard/tb-node:latest --dry-run 2>/dev/null || echo "Check Docker Hub manually"

# Visit Docker Hub
echo "Check: https://hub.docker.com/r/thingsboard/tb-node/tags"

# Check ThingsBoard releases
echo "Check: https://github.com/thingsboard/thingsboard/releases"
```

## 📋 Manual Update Steps

### Step 1: Pre-Update Backup (Recommended)

```bash
# Navigate to config directory
cd /home/pi/ThingsboardMWP/config

# Create backup directory
mkdir -p backups/$(date +%Y%m%d)

# Backup database
docker compose exec postgres pg_dump -U postgres thingsboard > backups/$(date +%Y%m%d)/thingsboard_backup_$(date +%Y%m%d_%H%M%S).sql

# Export dashboards (requires running system)
curl -X GET "http://localhost:8080/api/tenant/dashboards?pageSize=100&page=0" \
  -H "X-Authorization: Bearer YOUR_JWT_TOKEN" \
  > backups/$(date +%Y%m%d)/dashboards_backup_$(date +%Y%m%d_%H%M%S).json

# Export devices
curl -X GET "http://localhost:8080/api/tenant/devices?pageSize=100&page=0" \
  -H "X-Authorization: Bearer YOUR_JWT_TOKEN" \
  > backups/$(date +%Y%m%d)/devices_backup_$(date +%Y%m%d_%H%M%S).json
```

### Step 2: Stop Services

```bash
cd /home/pi/ThingsboardMWP/config
docker compose down
```

### Step 3: Update Docker Images

```bash
# Update specific version
docker pull thingsboard/tb-node:4.3.0.1  # Replace with latest version

# Or update to latest
docker pull thingsboard/tb-node:latest

# Update PostgreSQL (if needed)
docker pull postgres:16
```

### Step 4: Update Configuration (if needed)

Check if new version requires configuration changes:

```bash
# Check ThingsBoard release notes
echo "Visit: https://github.com/thingsboard/thingsboard/releases"

# Common configuration updates:
# - Environment variables
# - Memory settings
# - Database schema changes (usually automatic)
```

### Step 5: Start Updated Services

```bash
cd /home/pi/ThingsboardMWP/config
docker compose up -d
```

### Step 6: Monitor Startup and Verify

```bash
# Monitor logs
docker compose logs -f thingsboard

# Check services are healthy
docker compose ps

# Verify web interface
curl -s http://localhost:8080 | grep -i "thingsboard"

# Check API is responding
curl -s http://localhost:8080/api/components/VERSION
```

## 🔄 Rollback Procedure (If Update Fails)

### Emergency Rollback

```bash
# Stop failing services
cd /home/pi/ThingsboardMWP/config
docker compose down

# Revert to previous image version
# Edit docker-compose.yml to specify previous version
nano docker-compose.yml
# Change: thingsboard/tb-node:4.3.0.1 -> thingsboard/tb-node:4.2.0.1

# Start with previous version
docker compose up -d

# Restore database if needed
docker compose exec -T postgres psql -U postgres thingsboard < backups/YYYYMMDD/thingsboard_backup.sql
```

## 🆙 Major Version Updates

For major version updates (e.g., 4.2 → 4.3), additional steps may be required:

### Pre-Update Checklist
- ✅ Review release notes for breaking changes
- ✅ Test update in development environment first
- ✅ Backup all data (database, dashboards, devices)
- ✅ Plan downtime window
- ✅ Have rollback plan ready

### Post-Update Verification
- ✅ Database schema migrations completed
- ✅ All devices still reporting
- ✅ Dashboards loading correctly
- ✅ Rule chains functioning
- ✅ API endpoints working

## 🔧 Maintenance Updates

### Regular Maintenance

```bash
# Monthly: Update Docker images
cd /home/pi/ThingsboardMWP/config
docker compose pull
docker compose up -d

# Weekly: Clean up old images
docker image prune -f

# Check disk usage
df -h
docker system df
```

### Security Updates

```bash
# Check for security advisories
echo "Visit: https://github.com/thingsboard/thingsboard/security/advisories"

# Update immediately if security issue affects your version
cd /home/pi/ThingsboardMWP/config
docker compose pull
docker compose up -d
```

## 🐛 Troubleshooting Updates

### Update Fails to Start

```bash
# Check logs for errors
cd /home/pi/ThingsboardMWP/config
docker compose logs thingsboard

# Common issues:
# - Database schema incompatibility
# - Configuration syntax errors
# - Memory allocation issues
# - Port conflicts
```

### Performance Issues After Update

```bash
# Check resource usage
docker stats

# Check Java memory settings
docker compose exec thingsboard ps aux | grep java

# Adjust memory if needed
# Edit docker-compose.yml
# JAVA_OPTS: "-Xms256m -Xmx1024m"  # Adjust based on Pi model
```

### Database Migration Issues

```bash
# Check database logs
docker compose logs postgres

# Manual migration (rare)
docker compose exec thingsboard java -cp /usr/share/thingsboard/bin/thingsboard.jar org.thingsboard.server.service.install.SqlDatabaseUpgradeService

# Restore from backup if migration fails
docker compose exec -T postgres psql -U postgres thingsboard < backup.sql
```

## 📊 Update History Tracking

Keep track of your updates:

```bash
# Create update log
echo "$(date): Updated ThingsBoard to v4.3.0.1 - Status: SUCCESS/FAILED" >> /home/pi/ThingsboardMWP/update_history.log

# View update history
cat /home/pi/ThingsboardMWP/update_history.log
```

## ✅ Success Indicators

After successful update:
- ✅ ThingsBoard web interface loads
- ✅ API endpoints respond correctly
- ✅ Database connections working
- ✅ No error logs in containers
- ✅ All configured devices appear
- ✅ Dashboards display correctly

---

## 📅 Update Schedule

**Recommended Update Frequency:**
- **Security Updates:** Immediately when available
- **Bug Fixes:** Within 1-2 weeks
- **Feature Updates:** Monthly or when needed
- **Major Versions:** Quarterly or as needed

**Last Updated:** [Date]  
**Current Version:** ThingsBoard CE 4.3.0.1  
**Status:** ✅ Up to date

**Update Notes:**  
[Document any issues or special considerations for this update]