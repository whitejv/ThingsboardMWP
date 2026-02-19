# Dashboard Page Blueprint (Operations + Diagnostics)

Use this structure for your SCADA dashboard so operators get fast status at a glance while keeping troubleshooting data on a separate page.

## Page 1: Operations

Primary goal: instant situational awareness and alarm response.

## Layout

- Header strip: current time, connection health, active alarms count.
- Main center SCADA canvas:
  - Tank symbol with dynamic fill (`tank_percent_full`)
  - Well and pump symbols with on/off animation (`well_pump_*_on`, `irrigation_pump_on`)
  - Pipe flow indicators tied to `house_gpm`, `well3_gpm`, `irrigation_gpm`
- Right summary rail:
  - `tank_gallons`
  - `house_pressure_psi`
  - `well3_pressure_psi`
  - `irrigation_pressure_psi`
  - `system_temp_f`
- Bottom alarm strip:
  - Active alarms list (severity sorted)
  - Ack button and time since alarm

## Minimum Widget Set

1. Tank level gauge (`tank_percent_full`)
2. Tank volume value card (`tank_gallons`)
3. House pressure gauge (`house_pressure_psi`)
4. Well3 pressure gauge (`well3_pressure_psi`)
5. Irrigation GPM gauge (`irrigation_gpm`)
6. Pump status indicators (`well_pump_1_on`, `well_pump_2_on`, `well_pump_3_on`, `irrigation_pump_on`)
7. Alarm table widget

## Interaction Rules

- Clicking tank opens tank trend state in Diagnostics.
- Clicking any pump opens diagnostics filtered to that pump.
- Color use:
  - Normal: neutral
  - Warning: amber
  - Critical: red

## Page 2: Diagnostics

Primary goal: root cause analysis and trend validation.

## Layout

- Top filters: last 1h, 6h, 24h, 7d plus subsystem filter.
- Left column: trend charts.
- Right column: event cards and computed KPIs.
- Footer: raw telemetry debug table for latest payload.

## Recommended Charts

- Pressure trends:
  - `house_pressure_psi`
  - `well3_pressure_psi`
  - `irrigation_pressure_psi`
- Flow trends:
  - `house_gpm`
  - `well3_gpm`
  - `irrigation_gpm`
- Daily totals:
  - `house_gallons_day`
  - `well3_gallons_day`
  - `irrigation_gallons_day`
- Temperature trends:
  - `system_temp_f`
  - `house_temp_f`
  - `well3_temp_f`
  - `irrigation_temp_f`
  - `air_temp_f`
- Runtime proxy:
  - `irrigation_pump_on` (state timeline)
  - `well_pump_1_on`, `well_pump_2_on`, `well_pump_3_on` (state timeline)

## Entity Alias and Grouping Convention

Use consistent aliases in all widgets:

- `ws_main` for system-level canonical telemetry device
- `tank` for tank-focused widgets
- `house` for house line
- `well3` for well3 line
- `irrigation` for irrigation line

If using one physical device, aliases still help reuse widget configs and simplify dashboard copy/edit.

## Navigation State Map

- `state_ops` -> default Operations page
- `state_diag` -> Diagnostics overview
- `state_diag_tank` -> tank-focused charts
- `state_diag_pumps` -> pump-focused charts

Keep state names stable so you can clone and export/import dashboards without broken links.
