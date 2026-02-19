# Water Data Items (JSON) from `reference/water.h`

This document maps the key data interfaces defined in `reference/water.h` into JSON payload examples.

Focus parameters requested:
- Gallons (`gallonsDay`, `tank_gallons`, `gallonsTank`)
- Flow rate / GPM (`gallonsMinute`)
- Temperature (`temperatureF`, `system_temp`, etc.)
- Pressure (`pressurePSI`, `house_water_pressure`, etc.)

## Units and Conventions

- `pressurePSI`, `house_water_pressure`, `House_Pressure`, `Well3_Pressure`, `Irrigation_Pressure`: PSI
- `temperatureF`, `system_temp`, `System_Temp`, `House_Water_Temp`, `Irrigation_Pump_Temp`, `Air_Temp`: Fahrenheit
- `gallonsMinute`, `*_Gallons_Minute`: Gallons per minute (GPM)
- `gallonsDay`, `*_Gallons_Day`, `tank_gallons`, `Tank_Gallons`, `gallonsTank`: Gallons
- Pump/switch status fields use numeric values (`0`/`1`) in the header

---

## 1) Irrigation Monitor (`I001D`)

Topic: `mwp/data/monitor/Irrigation/I001D`

```json
{
  "pressurePSI": 37.5,
  "temperatureF": 84.2,
  "intervalFlow": 12.3,
  "amperage": 8.6,
  "secondsOn": 420,
  "gallonsMinute": 9.8,
  "gallonsDay": 1260.0,
  "controller": 1,
  "zone": 4,
  "cycleCount": 21
}
```

## 2) Tank Monitor (`T001D`)

Topic: `mwp/data/monitor/tank/T001D`

```json
{
  "pressurePSI": 15.4,
  "temperatureF": 78.1,
  "intervalFlow": 3.1,
  "secondsOn": 95,
  "gallonsMinute": 4.7,
  "gallonsDay": 540.0,
  "water_height": 5.9,
  "tank_gallons": 1825.0,
  "tank_per_full": 73.0,
  "float1": 0,
  "float2": 0,
  "cycleCount": 8
}
```

## 3) House Monitor (`H001D`)

Topic: `mwp/data/monitor/house/H001D`

```json
{
  "pressurePSI": 58.0,
  "temperatureF": 76.5,
  "intervalFlow": 2.4,
  "secondsOn": 60,
  "gallonsMinute": 3.3,
  "gallonsDay": 410.0,
  "controller": 0,
  "zone": 0,
  "cycleCount": 16
}
```

## 4) Well Monitor (`W001D`)

Topic: `mwp/data/monitor/well/W001D`

```json
{
  "well_pump_1_on": 1,
  "well_pump_2_on": 0,
  "well_pump_3_on": 0,
  "irrigation_pump_on": 1,
  "house_water_pressure": 62.0,
  "system_temp": 81.0,
  "House_tank_pressure_switch_on": 1,
  "septic_alert_on": 0,
  "cycle_count": 45,
  "amp_pump_1": 320,
  "amp_pump_2": 0,
  "amp_pump_3": 0,
  "amp_pump_4": 210
}
```

## 5) Well 3 Monitor (`W003D`)

Topic: `mwp/data/monitor/well3/W003D`

```json
{
  "pressurePSI": 64.3,
  "temperatureF": 79.4,
  "intervalFlow": 6.2,
  "secondsOn": 240,
  "gallonsMinute": 7.1,
  "gallonsDay": 980.0,
  "controller": 0,
  "zone": 0,
  "cycleCount": 13
}
```

## 6) Aggregate Monitor Block (`monitor`)

Topic: `mwp/data/monitor/monitor/`

```json
{
  "Tank_Gallons": 1825.0,
  "Tank_Percent_Full": 73.0,
  "House_Pressure": 58.0,
  "Well3_Pressure": 64.3,
  "Irrigation_Pressure": 37.5,
  "House_Gallons_Minute": 3.3,
  "Well3_Gallons_Minute": 7.1,
  "Irrigation_Gallons_Minute": 9.8,
  "House_Gallons_Day": 410.0,
  "Well3_Gallons_Day": 980.0,
  "Irrigation_Gallons_Day": 1260.0,
  "System_Temp": 81.0,
  "House_Water_Temp": 76.5,
  "Irrigation_Pump_Temp": 84.2,
  "Air_Temp": 74.0
}
```

## Recommended Canonical Telemetry Payload (ThingsBoard-Friendly)

Use this flattened payload if you want one standard JSON object for dashboards/rules:

```json
{
  "tank_gallons": 1825.0,
  "tank_percent_full": 73.0,
  "tank_gpm": 4.7,
  "house_gpm": 3.3,
  "well3_gpm": 7.1,
  "irrigation_gpm": 9.8,
  "house_gallons_day": 410.0,
  "well3_gallons_day": 980.0,
  "irrigation_gallons_day": 1260.0,
  "house_pressure_psi": 58.0,
  "well3_pressure_psi": 64.3,
  "irrigation_pressure_psi": 37.5,
  "system_temp_f": 81.0,
  "house_temp_f": 76.5,
  "irrigation_temp_f": 84.2,
  "air_temp_f": 74.0,
  "well_pump_1_on": 1,
  "well_pump_2_on": 0,
  "well_pump_3_on": 0,
  "irrigation_pump_on": 1,
  "house_tank_pressure_switch_on": 1,
  "ts": 1739725200000
}
```

This canonical shape makes widget binding easier and avoids mixed naming styles from different blocks.
