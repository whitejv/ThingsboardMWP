# Raspberry Pi Install Guide (ThingsBoard Local)

This guide installs a local ThingsBoard instance on Raspberry Pi and keeps it available after reboot.

## 1) Update Raspberry Pi to Latest

Run these commands on your Pi:

```bash
sudo apt update
sudo apt full-upgrade -y
sudo apt autoremove -y
sudo reboot
```

After reboot, reconnect and continue.

## 2) Install Docker (First Time Only)

Install Docker Engine + Docker Compose plugin:

```bash
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
sudo usermod -aG docker $USER
```

Then log out and back in (or reboot) so your user gets Docker group access.

Verify install:

```bash
docker --version
docker compose version
```

## 3) Install ThingsBoard Local Copy (Docker)

Create a local project folder:

```bash
mkdir -p ~/thingsboard-water
cd ~/thingsboard-water
```

Create `docker-compose.yml`:

```yaml
version: "3.8"
services:
  postgres:
    image: postgres:16
    restart: always
    environment:
      POSTGRES_DB: thingsboard
      POSTGRES_PASSWORD: postgres   # Change this in production!
    volumes:
      - postgres-data:/var/lib/postgresql/data
    # ports:
    #   - "5432:5432"   # Optional: only if you want external access

  thingsboard:
    image: thingsboard/tb-node:4.3.0.1
    container_name: thingsboard
    restart: always
    depends_on:
      - postgres
    ports:
      - "8080:8080"               # ThingsBoard Web UI
      - "1884:1883"               # TB MQTT endpoint (leave 1883 for Mosquitto)
      - "5683-5688:5683-5688/udp" # Optional CoAP/LwM2M ports
    environment:
      SPRING_DATASOURCE_URL: jdbc:postgresql://postgres:5432/thingsboard
      SPRING_DATASOURCE_USERNAME: postgres
      SPRING_DATASOURCE_PASSWORD: postgres
      TB_QUEUE_TYPE: in-memory
      TB_SERVICE_ID: tb-node-1
    volumes:
      - tb-data:/data
      - tb-logs:/var/log/thingsboard

volumes:
  postgres-data:
  tb-data:
  tb-logs:
```

Start ThingsBoard:

```bash
docker compose up -d
docker compose logs -f
```

Wait until logs show startup success (first run can take a few minutes).

Access UI:

- `http://<pi-ip>:8080`
- Default tenant login: `tenant@thingsboard.org / tenant`
- Change default passwords immediately.

## 4) Make It Always Available After Boot

This is already handled by `restart: always` in `docker-compose.yml`.

Recommended checks:

```bash
docker ps
docker inspect -f '{{.HostConfig.RestartPolicy.Name}}' thingsboard
```

Expected restart policy output: `always`

Optional test:

```bash
sudo reboot
# after reboot
docker ps
```

You should see the `thingsboard` container running automatically.

---

## Full Bash Script (Copy/Paste)

> Run this on the Raspberry Pi terminal.  
> It is safe for first-time install and re-runs (idempotent for folder/file creation).

```bash
#!/usr/bin/env bash
set -euo pipefail

echo "== Step 1: Update Pi =="
sudo apt update
sudo apt full-upgrade -y
sudo apt autoremove -y

echo "== Step 2: Install Docker (first time only) =="
if ! command -v docker >/dev/null 2>&1; then
  curl -fsSL https://get.docker.com -o /tmp/get-docker.sh
  sudo sh /tmp/get-docker.sh
fi

sudo usermod -aG docker "$USER"

echo "== Step 3: Create ThingsBoard project files =="
mkdir -p "$HOME/thingsboard-water"
cd "$HOME/thingsboard-water"

cat > docker-compose.yml <<'EOF'
version: "3.8"
services:
  postgres:
    image: postgres:16
    restart: always
    environment:
      POSTGRES_DB: thingsboard
      POSTGRES_PASSWORD: postgres
    volumes:
      - postgres-data:/var/lib/postgresql/data

  thingsboard:
    image: thingsboard/tb-node:4.3.0.1
    container_name: thingsboard
    restart: always
    depends_on:
      - postgres
    ports:
      - "8080:8080"
      - "1884:1883"
      - "5683-5688:5683-5688/udp"
    environment:
      SPRING_DATASOURCE_URL: jdbc:postgresql://postgres:5432/thingsboard
      SPRING_DATASOURCE_USERNAME: postgres
      SPRING_DATASOURCE_PASSWORD: postgres
      TB_QUEUE_TYPE: in-memory
      TB_SERVICE_ID: tb-node-1
    volumes:
      - tb-data:/data
      - tb-logs:/var/log/thingsboard

volumes:
  postgres-data:
  tb-data:
  tb-logs:
EOF

echo "== Step 4: Start ThingsBoard =="
if command -v docker >/dev/null 2>&1; then
  if docker compose version >/dev/null 2>&1; then
    docker compose up -d
  else
    echo "Docker Compose plugin not available yet in this shell."
    echo "Log out/in (or reboot), then run:"
    echo "  cd ~/thingsboard-water && docker compose up -d"
    exit 0
  fi
fi

echo "== Done =="
echo "ThingsBoard UI: http://<pi-ip>:8080"
echo "Container restart policy is set to 'always' for auto-start after boot."
echo "If docker commands fail due to permissions, log out/in or reboot once."
```

## Manual Update Steps (No Script)

Use these commands any time you want to update ThingsBoard manually:

```bash
cd ~/thingsboard-water
docker compose pull
docker compose up -d
docker image prune -f
docker compose ps
docker compose logs --tail=50 thingsboard
```

What each command does:

- `docker compose pull` downloads the latest image version.
- `docker compose up -d` recreates/runs the container with the new image.
- `docker image prune -f` removes old unused images.
- `docker compose ps` confirms container status.
- `docker compose logs --tail=50 thingsboard` checks recent startup logs.

## Update/Upgrade Script (Copy/Paste)

> Use this script for ongoing maintenance after initial install.  
> It pulls the latest ThingsBoard image, recreates the container, and prunes old unused images.

```bash
#!/usr/bin/env bash
set -euo pipefail

PROJECT_DIR="$HOME/thingsboard-water"

if [ ! -d "$PROJECT_DIR" ]; then
  echo "Project directory not found: $PROJECT_DIR"
  echo "Run the full install script first."
  exit 1
fi

cd "$PROJECT_DIR"

echo "== Pull latest ThingsBoard image =="
docker compose pull

echo "== Recreate container with latest image =="
docker compose up -d

echo "== Remove old unused images =="
docker image prune -f

echo "== Current status =="
docker compose ps

echo "== Recent logs (last 50 lines) =="
docker compose logs --tail=50 thingsboard

echo "Update complete."
```
