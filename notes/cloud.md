# 90-Minute ThingsBoard Cloud Prototype Checklist

Use this checklist to prototype quickly without getting stuck in design loops.

## 0) Prep (10 min)

- [ ] Create one test device with canonical keys from `notes/telemetry-canonical.md`
- [ ] Send sample telemetry every 5-10 seconds (real or simulated)
- [ ] Confirm latest values update in the device telemetry tab
- [ ] Keep this minimum key set available:
  - `tank_percent_full`, `tank_gallons`
  - `house_pressure_psi`, `well3_pressure_psi`
  - `irrigation_gpm`
  - `irrigation_pump_on`, `well_pump_1_on`
  - `system_temp_f`
  - alarm-related booleans if available

## 1) Build Operations Page First (30 min)

- [ ] Create dashboard: `Water System - Ops`
- [ ] Add top status row:
  - [ ] Active alarms count
  - [ ] Last telemetry age / connectivity indicator
- [ ] Add central SCADA panel:
  - [ ] Tank fill widget bound to `tank_percent_full`
  - [ ] Pump status indicators for `irrigation_pump_on` and `well_pump_1_on`
- [ ] Add right-side critical values:
  - [ ] `tank_gallons`
  - [ ] `house_pressure_psi`
  - [ ] `well3_pressure_psi`
  - [ ] `irrigation_gpm`
- [ ] Add alarm list widget at bottom (severity sorted)
- [ ] Apply color rules:
  - [ ] Normal = neutral
  - [ ] Warning = amber
  - [ ] Critical = red

## 2) Add Core Alarm UX (15 min)

- [ ] Create 3-4 starter alarm conditions:
  - [ ] `tank_percent_full` low
  - [ ] pressure high
  - [ ] low pressure while pump on
  - [ ] stale telemetry
- [ ] Verify alarm appears in Operations alarm list
- [ ] Verify acknowledge flow works
- [ ] Verify clear condition removes alarm from active list

## 3) Build Diagnostics Page (20 min)

- [ ] Create second state/page: `Diagnostics`
- [ ] Add time-range controls (`1h`, `6h`, `24h`)
- [ ] Add pressure trend chart (`house_pressure_psi`, `well3_pressure_psi`)
- [ ] Add flow trend chart (`irrigation_gpm`)
- [ ] Add temperature trend chart (`system_temp_f`)
- [ ] Add pump state timeline (`irrigation_pump_on`)
- [ ] Add navigation back to `Operations`

## 4) Navigation + Alias Cleanup (10 min)

- [ ] Confirm all widgets use consistent entity aliases
- [ ] Add click-through from pump/tank on Operations to Diagnostics
- [ ] Standardize widget titles with units (`PSI`, `GPM`, `F`, `gal`)

## 5) Reality Check Run (5 min setup + observation)

- [ ] Let dashboard run with live/sim telemetry for at least 30 minutes
- [ ] Watch for:
  - [ ] unreadable layout at a glance
  - [ ] noisy/unhelpful alarms
  - [ ] slow widgets/charts
- [ ] Remove or merge anything not useful to the operator

## Done Criteria

- [ ] Operations page answers "Is system healthy?" in under 5 seconds
- [ ] Diagnostics page answers "Why is it unhealthy?" in under 30 seconds
- [ ] Alarm list + acknowledge + clear flow is proven
- [ ] No duplicate field naming or unit confusion
