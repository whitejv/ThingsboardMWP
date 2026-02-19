# Canonical Telemetry Specification

This file defines the single telemetry schema to use for all dashboard widgets, alarms, and rule chains.

Use these keys consistently across all publishers and ThingsBoard widgets to avoid alias drift and duplicate widget configs.

## Naming Rules

- Use lowercase snake case.
- Add unit suffix when useful (`_psi`, `_f`, `_gpm`, `_gal`, `_day`).
- Status values are numeric (`0` or `1`) for easy threshold logic.
- Publish one flat payload per telemetry message.

## Canonical Keys and Units

| Key | Unit | Type | Source in `water.h` |
|---|---|---|---|
| `tank_gallons` | gal | number | `tank_gallons`, `Tank_Gallons` |
| `tank_percent_full` | % | number | `tank_per_full`, `Tank_Percent_Full` |
| `tank_height_ft` | ft | number | `water_height`, `Tank_Water_Height` |
| `house_pressure_psi` | psi | number | `pressurePSI`, `house_water_pressure`, `House_Pressure` |
| `well3_pressure_psi` | psi | number | `pressurePSI`, `Well3_Pressure` |
| `irrigation_pressure_psi` | psi | number | `pressurePSI`, `Irrigation_Pressure` |
| `house_gpm` | gpm | number | `gallonsMinute`, `House_Gallons_Minute` |
| `well3_gpm` | gpm | number | `gallonsMinute`, `Well3_Gallons_Minute` |
| `irrigation_gpm` | gpm | number | `gallonsMinute`, `Irrigation_Gallons_Minute` |
| `house_gallons_day` | gal/day | number | `gallonsDay`, `House_Gallons_Day` |
| `well3_gallons_day` | gal/day | number | `gallonsDay`, `Well3_Gallons_Day` |
| `irrigation_gallons_day` | gal/day | number | `gallonsDay`, `Irrigation_Gallons_Day` |
| `system_temp_f` | F | number | `system_temp`, `System_Temp` |
| `house_temp_f` | F | number | `temperatureF`, `House_Water_Temp` |
| `well3_temp_f` | F | number | `temperatureF` |
| `irrigation_temp_f` | F | number | `temperatureF`, `Irrigation_Pump_Temp` |
| `air_temp_f` | F | number | `Air_Temp` |
| `well_pump_1_on` | bool(0/1) | number | `well_pump_1_on` |
| `well_pump_2_on` | bool(0/1) | number | `well_pump_2_on` |
| `well_pump_3_on` | bool(0/1) | number | `well_pump_3_on` |
| `irrigation_pump_on` | bool(0/1) | number | `irrigation_pump_on` |
| `house_tank_pressure_switch_on` | bool(0/1) | number | `House_tank_pressure_switch_on` |
| `septic_alert_on` | bool(0/1) | number | `septic_alert_on` |

## Canonical Publish Payload

```json
{
  "tank_gallons": 1825.0,
  "tank_percent_full": 73.0,
  "tank_height_ft": 5.9,
  "house_pressure_psi": 58.0,
  "well3_pressure_psi": 64.3,
  "irrigation_pressure_psi": 37.5,
  "house_gpm": 3.3,
  "well3_gpm": 7.1,
  "irrigation_gpm": 9.8,
  "house_gallons_day": 410.0,
  "well3_gallons_day": 980.0,
  "irrigation_gallons_day": 1260.0,
  "system_temp_f": 81.0,
  "house_temp_f": 76.5,
  "well3_temp_f": 79.4,
  "irrigation_temp_f": 84.2,
  "air_temp_f": 74.0,
  "well_pump_1_on": 1,
  "well_pump_2_on": 0,
  "well_pump_3_on": 0,
  "irrigation_pump_on": 1,
  "house_tank_pressure_switch_on": 1,
  "septic_alert_on": 0,
  "ts": 1739725200000
}
```

## Migration Rule (Legacy to Canonical)

If your publisher still emits legacy keys from `water.h`, normalize in one place before dashboards:

1. Read incoming legacy telemetry.
2. Map legacy names to canonical names in a transform script or ThingsBoard rule chain.
3. Save only canonical keys for dashboard use.

This keeps widgets simple and stable while firmware evolves.
