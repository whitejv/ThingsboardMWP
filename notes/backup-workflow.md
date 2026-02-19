# Dashboard Backup and Version Workflow

Use this workflow after each milestone so dashboard and config changes are recoverable.

## Folder Layout

- `backup/dashboard_exports/` -> exported dashboard JSON files
- `backup/snapshots/` -> timestamped tar.gz snapshots of project docs/config
- `backup/create-backup.sh` -> local backup script

## Milestone Process

1. Export dashboard JSON from ThingsBoard UI.
2. Save it into `backup/dashboard_exports/` using date-stamped names.
3. Run local snapshot script.
4. Verify archive exists and can be listed with `tar -tzf`.

## Naming Convention

Use:

- `dashboard-ops-YYYYMMDD-HHMM.json`
- `dashboard-diagnostics-YYYYMMDD-HHMM.json`
- `thingsboard-project-YYYYMMDD-HHMMSS.tar.gz`

## Manual Commands

```bash
mkdir -p backup/dashboard_exports backup/snapshots
./backup/create-backup.sh
ls -lah backup/snapshots
```

## Restore Process (Local Files)

```bash
tar -xzf backup/snapshots/thingsboard-project-YYYYMMDD-HHMMSS.tar.gz -C .
```

Then:
- Re-import dashboard JSON in ThingsBoard.
- Restart stack if needed:

```bash
docker compose --env-file config/.env -f config/docker-compose.yml up -d
```
