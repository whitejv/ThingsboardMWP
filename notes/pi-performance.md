# Raspberry Pi 5 Performance Profile (ThingsBoard SCADA)

Use these defaults to keep dashboards responsive on a local Pi 5.

## Dashboard Density Targets

- Operations page:
  - Keep to 8-12 primary widgets.
  - Avoid more than 2 live time-series widgets on this page.
  - Prefer value cards, gauges, state indicators, and one alarm table.
- Diagnostics page:
  - 6-10 charts max visible at once.
  - Split by tabs/states (`pressure`, `flow`, `temperature`, `alarms`) if needed.

## Refresh Interval Defaults

- Current value widgets: 5-10 seconds.
- SCADA status icons: 2-5 seconds.
- Alarm table: 5 seconds.
- Heavy time-series charts: 30-60 seconds.
- Historical dashboards (24h+): manual refresh or 60+ seconds.

Start slower, then tighten refresh only where needed.

## Data Retention and Query Guidance

- Use short default ranges:
  - Operations: latest values only
  - Diagnostics default: last 1 hour
- Avoid loading 7-day charts by default on initial page open.
- Add quick range chips: `1h`, `6h`, `24h`, `7d`.

## SCADA Visual Performance Rules

- Animate only pump on/off and active flow.
- Do not animate every pipe/label continuously.
- Use simple SVG shapes and minimal shadows/gradients.
- Keep text overlays short and fixed-size.

## Rule Chain and Telemetry Hygiene

- Normalize keys once in rule chain, not per widget.
- Drop or quarantine invalid/out-of-range values to reduce noisy redraws.
- Use stale telemetry alarm instead of forcing aggressive polling.

## Runtime Checks on Pi

Run during live testing:

```bash
docker stats
htop
docker compose logs --tail=100 thingsboard
```

Watch for:
- sustained high CPU spikes when opening dashboard
- memory pressure and swap growth
- repeated timeout warnings in ThingsBoard logs

## Operational SLO Targets

- Operations dashboard initial load: under 3 seconds on local LAN.
- Widget update latency (sensor -> visible): under 5 seconds.
- No dashboard freezes during 24-hour soak test.
