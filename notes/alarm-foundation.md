# Alarm Foundation (Threshold + Stale Data)

This defines the first alarm set to implement before visual polish.

## Alarm Model

- **Critical**: immediate operator action needed.
- **Major**: urgent but not emergency.
- **Minor**: warning trend, watch closely.

Use clear alarm types so widgets, notifications, and ack workflows stay consistent.

## Recommended Alarm Definitions

| Alarm Type | Condition | Severity | Clear Condition |
|---|---|---|---|
| `TankLowCritical` | `tank_percent_full < 15` for 2 min | Critical | `tank_percent_full >= 20` for 2 min |
| `TankLowWarning` | `tank_percent_full < 30` for 2 min | Major | `tank_percent_full >= 35` for 2 min |
| `HousePressureHigh` | `house_pressure_psi > 80` for 60 sec | Critical | `house_pressure_psi <= 75` for 60 sec |
| `HousePressureLowWhilePumpOn` | `house_pressure_psi < 35 AND irrigation_pump_on == 1` for 60 sec | Major | `house_pressure_psi >= 40 OR irrigation_pump_on == 0` for 60 sec |
| `Well3PressureHigh` | `well3_pressure_psi > 80` for 60 sec | Critical | `well3_pressure_psi <= 75` for 60 sec |
| `IrrigationFlowUnexpected` | `irrigation_pump_on == 1 AND irrigation_gpm < 0.5` for 90 sec | Major | `irrigation_gpm >= 0.8 OR irrigation_pump_on == 0` for 90 sec |
| `StaleTelemetry` | no telemetry for 120 sec | Critical | telemetry received in last 30 sec |
| `PressureSwitchMismatch` | `house_tank_pressure_switch_on == 0 AND house_pressure_psi < 25` for 60 sec | Minor | condition false for 60 sec |
| `SepticAlert` | `septic_alert_on == 1` | Critical | `septic_alert_on == 0` |

Tune thresholds to your actual system after observing 3-7 days of live data.

## Stale Data Rule (Required)

Implement stale detection with server-side time, not sensor time:

1. On every telemetry message, save latest server timestamp.
2. Run periodic check every 30 seconds.
3. If `now - last_telemetry_ts > 120000 ms`, create `StaleTelemetry`.
4. Clear when fresh telemetry returns.

## ThingsBoard Rule Chain Blueprint

1. **Message Type Switch**: telemetry only.
2. **Script/Transform Node**: enforce canonical keys (if still ingesting legacy fields).
3. **Save Timeseries Node**.
4. **Filter Node(s)** for each threshold condition.
5. **Create/Clear Alarm Node** using alarm type list above.
6. **Notification Node**:
   - Critical -> push/email/SMS target
   - Major -> push/email
   - Minor -> dashboard only
7. **Persist enriched metadata** (`alarm_source`, `threshold`, `last_value`).

## Acknowledgment Workflow

- Operator acknowledges in alarm widget.
- Keep alarm visible until clear condition is true (do not auto-hide on ack).
- Track:
  - `createdTime`
  - `ackTime`
  - `clearTime`
  - `ackUser`

This gives useful response-time metrics for future tuning.

## Dashboard Alarm Widgets

Operations page:
- Active alarms table (sorted by severity and newest first).
- Alarm count badge (Critical/Major/Minor counts).

Diagnostics page:
- Alarm history timeline (last 24h / 7d).
- Mean time to acknowledge (MTTA) and mean time to resolve (MTTR) cards.
