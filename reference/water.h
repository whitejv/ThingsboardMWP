

/*
* Block ID: I001D
* Block Name: irrigationMon
* Description: Irrigation Monitor
* From: Irrigation
* Category: monitor
* Type: data
* MQTT Client ID: Irrigation Monitor Client
* MQTT Topic ID: 
* MSG Length: 16
*  word #        data type            variable                description        min        max        nominal
*  0        float            pressurePSI                Pressure in PSI - Irrigation        0        50        10
*  1        float            temperatureF                Temperature - Irrigation Pump        0        5000        2000
*  2        float            intervalFlow                Gallons in interval        0        100        50
*  3        float            amperage                Amperage        -5        125        80
*  4        float            secondsOn                Second on for Pump        0        14400        60
*  5        float            gallonsMinute                Gallons per Minute        0        1        1
*  6        float            gallonsDay                Irrigation Total Gallons (24hrs)        1        22        1
*  7        float            controller                Controller        0        1        1
*  8        float            zone                Zone        1        22        1
*  9        float            spare1                Spare        0        28800        
*  10        float            spare2                Spare                        
*  11        float            spare3                Spare                        
*  12        float            spare4                Spare                        
*  13        float            spare5                Spare                        
*  14        float            cycleCount                Cycle Count                        
*  15        float            fwVersion                 FW Version 4 Hex                         
*/

const char IRRIGATIONMON_CLIENTID[] =    "Irrigation Monitor Client" ;
const char IRRIGATIONMON_TOPICID[] =  "mwp/data/monitor/Irrigation/I001D";
const char IRRIGATIONMON_JSONID[] =  "mwp/json/data/monitor/Irrigation/I001D";
#define IRRIGATIONMON_LEN 16

union   IRRIGATIONMON_  {
   float     data_payload[IRRIGATIONMON_LEN] ;

   struct  {
      float   pressurePSI	;		//   Irrigation Flow GPM
      float   temperatureF	;		//   Total Gallons Flowed in 24 hours
      float   intervalFlow	;		//   Irrigation Pressure
      float   amperage	;		//   house water pressure (psi)
      float   secondsOn	;		//   for Calculating Pump Run Times
      float   gallonsMinute	;		//   Rainbird ESP Controller 1=Front 2=Back
      float   gallonsDay	;		//   Rainbird Zone
      float   controller	;		//   
      float   zone	;		//   
      float   spare1	;		//   
      float   spare2	;		//   
      float   spare3	;		//   
      float   spare4	;		//   
      float   spare5	;		//   
      float   cycleCount	;		//   
      float   fwVersion	;		//   
   }  irrigation  ;
}  ;
union  IRRIGATIONMON_  irrigationMon_  ;

char* irrigationmon_ClientData_var_name [] = { 
    "I001D:pressurePSI",
    "I001D:temperatureF",
    "I001D:intervalFlow",
    "I001D:amperage",
    "I001D:secondsOn",
    "I001D:gallonsMinute",
    "I001D:gallonsDay",
    "I001D:controller",
    "I001D:zone",
    "I001D:spare1",
    "I001D:spare2",
    "I001D:spare3",
    "I001D:spare4",
    "I001D:spare5",
    "I001D:cycleCount",
    "I001D:fwVersion",
}  ;

/*
* Block ID: R001C
* Block Name: rainbirdCommand
* Description: Rainbird Command Block
* From: rainbirdPy
* To: xxx
* Category: sensor
* MQTT Client ID: RainbirdPy
* MQTT Topic ID: command/rainbird/command
* MSG Length: 7
*  word #        data type            variable                description        min        max        nominal
*  0        char            command[7]                Command Word                        
*/

const char RAINBIRDCOMMAND_CLIENTID[] =    "RainbirdPy" ;
const char RAINBIRDCOMMAND_TOPICID[] =  "mwp/command/rainbird/command";
const char RAINBIRDCOMMAND_JSONID[] =  "mwp/json/command/rainbird/command";
#define RAINBIRDCOMMAND_LEN 7

union   RAINBIRDCOMMAND_  {
   char     data_payload[RAINBIRDCOMMAND_LEN] ;

   struct  {
      char   command[7]	;		//   Text "check1" or "check2"
   }  rainbirdpy  ;
}  ;
union  RAINBIRDCOMMAND_  rainbirdCommand_  ;

char* rainbirdcommand_ClientData_var_name [] = { 
    "R001C:command[7]",
}  ;

/*
* Block ID: R001R
* Block Name: rainbirdResponse
* Description: Rainbird Response 
* From: rainbirdPy
* Category: sensor
* Type: response
* MQTT Client ID: RainbirdPy
* MQTT Topic ID: response/rainbird/+/active_zone
* MSG Length: 255
*  word #        data type            variable                description        min        max        nominal
*  0        char            command_response[255]                Command Response Word                        
*/

const char RAINBIRDRESPONSE_CLIENTID[] =    "RainbirdPy" ;
const char RAINBIRDRESPONSE_TOPICID[] =  "mwp/response/rainbird/+/active_zone";
const char RAINBIRDRESPONSE_JSONID[] =  "mwp/json/response/rainbird/+/active_zone";
#define RAINBIRDRESPONSE_LEN 255

union   RAINBIRDRESPONSE_  {
   char     data_payload[RAINBIRDRESPONSE_LEN] ;

   struct  {
      char   command_response[255]	;		//   
   }  rainbirdpy  ;
}  ;
union  RAINBIRDRESPONSE_  rainbirdResponse_  ;

char* rainbirdresponse_ClientData_var_name [] = { 
    "R001R:command_response[255]",
}  ;

/*
* Block ID: T001D
* Block Name: tankMon
* Description: Tank Monitor
* From: tank
* Category: monitor
* Type: data
* MQTT Client ID: Tank Monitor Client
* MQTT Topic ID: 
* MSG Length: 16
*  word #        data type            variable                description        min        max        nominal
*  0        float            pressurePSI                Pressure in PSI - Atmospheric                        
*  1        float            temperatureF                Temperature - Tank Valve                        
*  2        float            intervalFlow                Gallons in interval -N/A                        
*  3        float            amperage                Amperage -N/A                        
*  4        float            secondsOn                Second on for Pump        0        14400        60
*  5        float            gallonsMinute                Gallons per Minute                        
*  6        float            gallonsDay                Tank Total Gallons (24hrs)                        
*  7        float            controller                Controller                        
*  8        float            zone                Zone                        
*  9        float            water_height                Water Height                        
*  10        float            tank_gallons                 FW Version 4 Hex                         
*  11        float            tank_per_full                Tank Percent Full                        
*  12        float            float1                Overfill Float                        
*  13        float            float2                Tank Low Float                        
*  14        float            cycleCount                Cycle Count                        
*  15        float            fwVersion                 FW Version 4 Hex                         
*/

const char TANKMON_CLIENTID[] =    "Tank Monitor Client" ;
const char TANKMON_TOPICID[] =  "mwp/data/monitor/tank/T001D";
const char TANKMON_JSONID[] =  "mwp/json/data/monitor/tank/T001D";
#define TANKMON_LEN 16

union   TANKMON_  {
   float     data_payload[TANKMON_LEN] ;

   struct  {
      float   pressurePSI	;		//   
      float   temperatureF	;		//   
      float   intervalFlow	;		//   
      float   amperage	;		//   
      float   secondsOn	;		//   for Calculating Pump Run Times
      float   gallonsMinute	;		//   
      float   gallonsDay	;		//   
      float   controller	;		//   
      float   zone	;		//   
      float   water_height	;		//   
      float   tank_gallons	;		//   
      float   tank_per_full	;		//   
      float   float1	;		//   
      float   float2	;		//   
      float   cycleCount	;		//   
      float   fwVersion	;		//   
   }  tank  ;
}  ;
union  TANKMON_  tankMon_  ;

char* tankmon_ClientData_var_name [] = { 
    "T001D:pressurePSI",
    "T001D:temperatureF",
    "T001D:intervalFlow",
    "T001D:amperage",
    "T001D:secondsOn",
    "T001D:gallonsMinute",
    "T001D:gallonsDay",
    "T001D:controller",
    "T001D:zone",
    "T001D:water_height",
    "T001D:tank_gallons",
    "T001D:tank_per_full",
    "T001D:float1",
    "T001D:float2",
    "T001D:cycleCount",
    "T001D:fwVersion",
}  ;

/*
* Block ID: H001D
* Block Name: houseMon
* Description: House Monitor
* From: house
* Category: monitor
* Type: data
* MQTT Client ID: House Monitor Client
* MQTT Topic ID: 
* MSG Length: 16
*  word #        data type            variable                description        min        max        nominal
*  0        float            pressurePSI                Pressure in PSI - House        0        25        15
*  1        float            temperatureF                Temperature - House Supply        0        5000        100
*  2        float            intervalFlow                Gallons in interval        0        100        65
*  3        float            amperage                Amperage        0        125        80
*  4        float            secondsOn                Second on for Pump        0        14400        60
*  5        float            gallonsMinute                Gallons per Minute                        
*  6        float            gallonsDay                House Total Gallons (24hrs)                        
*  7        float            controller                Controller                        
*  8        float            zone                Zone                        
*  9        float            spare1                Spare 1        0        28800        
*  10        float            spare2                Spare 2                        
*  11        float            spare3                Spare 3                        
*  12        float            spare4                Spare 4                        
*  13        float            spare5                Spare 5                        
*  14        float            cycleCount                Cycle Count                        
*  15        float            fwVersion                 FW Version 4 Hex                         
*/

const char HOUSEMON_CLIENTID[] =    "House Monitor Client" ;
const char HOUSEMON_TOPICID[] =  "mwp/data/monitor/house/H001D";
const char HOUSEMON_JSONID[] =  "mwp/json/data/monitor/house/H001D";
#define HOUSEMON_LEN 16

union   HOUSEMON_  {
   float     data_payload[HOUSEMON_LEN] ;

   struct  {
      float   pressurePSI	;		//   
      float   temperatureF	;		//   
      float   intervalFlow	;		//   
      float   amperage	;		//   
      float   secondsOn	;		//   for Calculating Pump Run Times
      float   gallonsMinute	;		//   
      float   gallonsDay	;		//   
      float   controller	;		//   
      float   zone	;		//   
      float   spare1	;		//   
      float   spare2	;		//   
      float   spare3	;		//   
      float   spare4	;		//   
      float   spare5	;		//   
      float   cycleCount	;		//   
      float   fwVersion	;		//   
   }  house  ;
}  ;
union  HOUSEMON_  houseMon_  ;

char* housemon_ClientData_var_name [] = { 
    "H001D:pressurePSI",
    "H001D:temperatureF",
    "H001D:intervalFlow",
    "H001D:amperage",
    "H001D:secondsOn",
    "H001D:gallonsMinute",
    "H001D:gallonsDay",
    "H001D:controller",
    "H001D:zone",
    "H001D:spare1",
    "H001D:spare2",
    "H001D:spare3",
    "H001D:spare4",
    "H001D:spare5",
    "H001D:cycleCount",
    "H001D:fwVersion",
}  ;

/*
* Block ID: W001D
* Block Name: wellMon
* Description: Well Monitor
* From: well
* Category: monitor
* Type: data
* MQTT Client ID: Well Monitor Client
* MQTT Topic ID: 
* MSG Length: 18
*  word #        data type            variable                description        min        max        nominal
*  0        float            well_pump_1_on                Well Pump 1 On        0        1        
*  1        float            well_pump_2_on                Well Pump 2 On        0        1        
*  2        float            well_pump_3_on                Well Pump 3 On        0        1        
*  3        float            irrigation_pump_on                Irrigation Pump On        0        1        
*  4        float            house_water_pressure                House Water Pressure        0        100        
*  5        float            system_temp                System Temp        0        150        
*  6        float            House_tank_pressure_switch_on                House Tank Pressure Switch On        0        1        
*  7        float            septic_alert_on                Septic Alert On        0        1        
*  8        float            cycle_count                Cycle Count        0        28800        
*  9        float            fw_version                 FW Version 4 Hex                         
*  10        float            amp_pump_1                amp count pump 1        0        1024        
*  11        float            amp_pump_2                amp count pump 2        0        1024        
*  12        float            amp_pump_3                amp count pump 3        0        1024        
*  13        float            amp_pump_4                amp count pump 4        0        1024        
*  14        float            amp_5                amp count 5        0        1024        
*  15        float            amp_6                amp count 6        0        1024        
*  16        float            amp_7                amp count 7        0        1024        
*  17        float            amp_8                amp count 8        0        1024        
*/

const char WELLMON_CLIENTID[] =    "Well Monitor Client" ;
const char WELLMON_TOPICID[] =  "mwp/data/monitor/well/W001D";
const char WELLMON_JSONID[] =  "mwp/json/data/monitor/well/W001D";
#define WELLMON_LEN 18

union   WELLMON_  {
   float     data_payload[WELLMON_LEN] ;

   struct  {
      float   well_pump_1_on	;		//   
      float   well_pump_2_on	;		//   
      float   well_pump_3_on	;		//   
      float   irrigation_pump_on	;		//   
      float   house_water_pressure	;		//   
      float   system_temp	;		//   
      float   House_tank_pressure_switch_on	;		//   
      float   septic_alert_on	;		//   
      float   cycle_count	;		//   
      float   fw_version	;		//   
      float   amp_pump_1	;		//   
      float   amp_pump_2	;		//   
      float   amp_pump_3	;		//   
      float   amp_pump_4	;		//   
      float   amp_5	;		//   
      float   amp_6	;		//   
      float   amp_7	;		//   
      float   amp_8	;		//   
   }  well  ;
}  ;
union  WELLMON_  wellMon_  ;

char* wellmon_ClientData_var_name [] = { 
    "W001D:well_pump_1_on",
    "W001D:well_pump_2_on",
    "W001D:well_pump_3_on",
    "W001D:irrigation_pump_on",
    "W001D:house_water_pressure",
    "W001D:system_temp",
    "W001D:House_tank_pressure_switch_on",
    "W001D:septic_alert_on",
    "W001D:cycle_count",
    "W001D:fw_version",
    "W001D:amp_pump_1",
    "W001D:amp_pump_2",
    "W001D:amp_pump_3",
    "W001D:amp_pump_4",
    "W001D:amp_5",
    "W001D:amp_6",
    "W001D:amp_7",
    "W001D:amp_8",
}  ;

/*
* Block ID: W003D
* Block Name: well3Mon
* Description: Well3 Monitor
* From: well3
* Category: monitor
* Type: data
* MQTT Client ID: Well3 Monitor Client
* MQTT Topic ID: 
* MSG Length: 16
*  word #        data type            variable                description        min        max        nominal
*  0        float            pressurePSI                Pressure in PSI - Well3        0        25        15
*  1        float            temperatureF                Temperature - Well3 Supply Line        0        5000        100
*  2        float            intervalFlow                Gallons in interval        0        100        65
*  3        float            amperage                Amperage        0        125        80
*  4        float            secondsOn                Second on for Pump        0        14400        60
*  5        float            gallonsMinute                Gallons per Minute                        
*  6        float            gallonsDay                Well3 Total Gallons (24hrs)                        
*  7        float            controller                Controller                        
*  8        float            zone                Zone                        
*  9        float            spare1                Spare 1        0        28800        
*  10        float            spare2                Spare 2                        
*  11        float            spare3                Spare 3                        
*  12        float            spare4                Spare 4                        
*  13        float            spare5                Spare 5                        
*  14        float            cycleCount                Cycle Count                        
*  15        float            fwVersion                 FW Version 4 Hex                         
*/

const char WELL3MON_CLIENTID[] =    "Well3 Monitor Client" ;
const char WELL3MON_TOPICID[] =  "mwp/data/monitor/well3/W003D";
const char WELL3MON_JSONID[] =  "mwp/json/data/monitor/well3/W003D";
#define WELL3MON_LEN 16

union   WELL3MON_  {
   float     data_payload[WELL3MON_LEN] ;

   struct  {
      float   pressurePSI	;		//   
      float   temperatureF	;		//   
      float   intervalFlow	;		//   
      float   amperage	;		//   
      float   secondsOn	;		//   for Calculating Pump Run Times
      float   gallonsMinute	;		//   
      float   gallonsDay	;		//   
      float   controller	;		//   
      float   zone	;		//   
      float   spare1	;		//   
      float   spare2	;		//   
      float   spare3	;		//   
      float   spare4	;		//   
      float   spare5	;		//   
      float   cycleCount	;		//   
      float   fwVersion	;		//   
   }  well3  ;
}  ;
union  WELL3MON_  well3Mon_  ;

char* well3mon_ClientData_var_name [] = { 
    "W003D:pressurePSI",
    "W003D:temperatureF",
    "W003D:intervalFlow",
    "W003D:amperage",
    "W003D:secondsOn",
    "W003D:gallonsMinute",
    "W003D:gallonsDay",
    "W003D:controller",
    "W003D:zone",
    "W003D:spare1",
    "W003D:spare2",
    "W003D:spare3",
    "W003D:spare4",
    "W003D:spare5",
    "W003D:cycleCount",
    "W003D:fwVersion",
}  ;

/*
* Block ID: 
* Block Name: monitor
* Description: Monitor Data for Blynk
* From: monitor
* Category: monitor
* Type: data
* MQTT Client ID: Monitor Client
* MQTT Topic ID: 
* MSG Length: 38
*  word #        data type            variable                description        min        max        nominal
*  0        float            Tank_Water_Height                        0        8        
*  1        float            Tank_Gallons                        0        2500        
*  2        float            Tank_Percent_Full                        0        100        
*  3        float            House_Pressure                        0        100        
*  4        float            Well3_Pressure                        0        100        
*  5        float            Irrigation_Pressure                        0        100        
*  6        float            House_Gallons_Minute                        0        80        
*  7        float            Well3_Gallons_Minute                        0        80        
*  8        float            Irrigation_Gallons_Minute                        0        80        
*  9        float            House_Gallons_Day                        0        4000        
*  10        float            Well3_Gallons_Day                        0        4000        
*  11        float            Irrigation_Gallons_Day                        0        4000        
*  12        float            System_Temp                        -32        120        
*  13        float            House_Water_Temp                        -32        120        
*  14        float            Irrigation_Pump_Temp                        -32        120        
*  15        float            Air_Temp                        -32        120        
*  16        float            Spare1                        0        0        
*  17        float            Spare2                        0        0        
*  18        float            Well_1_LED_Bright                        0        255        
*  19        float            Well_2_LED_Bright                        0        255        
*  20        float            Well_3_LED_Bright                        0        255        
*  21        float            Irrig_4_LED_Bright                        0        255        
*  22        float            Spare1_LED_Bright                        0        255        
*  23        float            Spare2_LED_Bright                        0        255        
*  24        float            Well_1_LED_Color                        0        6        
*  25        float            Well_2_LED_Color                        0        6        
*  26        float            Well_3_LED_Color                        0        6        
*  27        float            Irrig_4_LED_Color                        0        6        
*  28        float            Controller                        0        6        
*  29        float            Zone                        0        32        
*  30        float            Pump_1_RunCount                        5        25        
*  31        float            Pump_1_RunTIme                        5        15        
*  32        float            Pump_2_RunCount                        5        25        
*  33        float            Pump_2_RunTIme                        5        15        
*  34        float            Pump_3_RunCount                        3        10        
*  35        float            Pump_3_RunTIme                        290        300        
*  36        float            Pump_4_RunCount                        12        35        
*  37        float            Pump_4_RunTIme                        200        200        
*/

const char MONITOR_CLIENTID[] =    "Monitor Client" ;
const char MONITOR_TOPICID[] =  "mwp/data/monitor/monitor/";
const char MONITOR_JSONID[] =  "mwp/json/data/monitor/monitor/";
#define MONITOR_LEN 38

union   MONITOR_  {
   float     data_payload[MONITOR_LEN] ;

   struct  {
      float   Tank_Water_Height	;		//   
      float   Tank_Gallons	;		//   
      float   Tank_Percent_Full	;		//   
      float   House_Pressure	;		//   
      float   Well3_Pressure	;		//   
      float   Irrigation_Pressure	;		//   
      float   House_Gallons_Minute	;		//   
      float   Well3_Gallons_Minute	;		//   
      float   Irrigation_Gallons_Minute	;		//   
      float   House_Gallons_Day	;		//   
      float   Well3_Gallons_Day	;		//   
      float   Irrigation_Gallons_Day	;		//   
      float   System_Temp	;		//   
      float   House_Water_Temp	;		//   
      float   Irrigation_Pump_Temp	;		//   
      float   Air_Temp	;		//   
      float   Spare1	;		//   
      float   Spare2	;		//   
      float   Well_1_LED_Bright	;		//   
      float   Well_2_LED_Bright	;		//   
      float   Well_3_LED_Bright	;		//   
      float   Irrig_4_LED_Bright	;		//   
      float   Spare1_LED_Bright	;		//   
      float   Spare2_LED_Bright	;		//   
      float   Well_1_LED_Color	;		//   
      float   Well_2_LED_Color	;		//   
      float   Well_3_LED_Color	;		//   
      float   Irrig_4_LED_Color	;		//   
      float   Controller	;		//   
      float   Zone	;		//   
      float   Pump_1_RunCount	;		//   
      float   Pump_1_RunTime	;		//   
      float   Pump_2_RunCount	;		//   
      float   Pump_2_RunTime	;		//   
      float   Pump_3_RunCount	;		//   
      float   Pump_3_RunTime	;		//   
      float   Pump_4_RunCount	;		//   
      float   Pump_4_RunTime	;		//   
   }  monitor  ;
}  ;
union  MONITOR_  monitor_  ;

char* monitor_ClientData_var_name [] = { 
    "Tank_Water_Height",
    "Tank_Gallons",
    "Tank_Percent_Full",
    "House_Pressure",
    "Well3_Pressure",
    "Irrigation_Pressure",
    "House_Gallons_Minute",
    "Well3_Gallons_Minute",
    "Irrigation_Gallons_Minute",
    "House_Gallons_Day",
    "Well3_Gallons_Day",
    "Irrigation_Gallons_Day",
    "System_Temp",
    "House_Water_Temp",
    "Irrigation_Pump_Temp",
    "Air_Temp",
    "Spare1",
    "Spare2",
    "Well_1_LED_Bright",
    "Well_2_LED_Bright",
    "Well_3_LED_Bright",
    "Irrig_4_LED_Bright",
    "Spare1_LED_Bright",
    "Spare2_LED_Bright",
    "Well_1_LED_Color",
    "Well_2_LED_Color",
    "Well_3_LED_Color",
    "Irrig_4_LED_Color",
    "Controller",
    "Zone",
    "Pump_1_RunCount",
    "Pump_1_RunTIme",
    "Pump_2_RunCount",
    "Pump_2_RunTIme",
    "Pump_3_RunCount",
    "Pump_3_RunTIme",
    "Pump_4_RunCount",
    "Pump_4_RunTIme",
}  ;

/*
* Block ID: 
* Block Name: alert
* Description: Alert Data for Blynk
* From: alert
* Category: alert
* Type: data
* MQTT Client ID: Alert Client
* MQTT Topic ID: 
* MSG Length: 40
*  word #        data type            variable                description        min        max        nominal
*  0        int            Alert1                Alert 1        0        100        
*  1        int            Alert2                 Alert 2        0        100        
*  2        int            Alert3                Alert 3        0        100        
*  3        int            Alert4                Alert 4        0        100        
*  4        int            Alert5                Alert 5        0        100        
*  5        int            Alert6                Alert 6        0        100        
*  6        int            Alert7                Alert 7        0        100        
*  7        int            Alert8                Alert 8        0        100        
*  8        int            Alert9                Alert 9        0        100        
*  9        int            Alert10                Alert 10        0        100        
*  10        int            Alert11                Alert 11        0        100        
*  11        int            Alert12                Alert 12        0        100        
*  12        int            Alert13                Alert 13        0        100        
*  13        int            Alert14                Alert 14        0        100        
*  14        int            Alert15                Alert 15        0        100        
*  15        int            Alert16                Alert 16        0        100        
*  16        int            Alert17                Alert 17        0        100        
*  17        int            Alert18                Alert 18        0        100        
*  18        int            Alert19                Alert 19        0        100        
*  19        int            Alert20                Alert 20        0        100        
*  20        int            Alert21                Alert 21        0        100        
*  21        int            Alert22                Alert 22        0        100        
*  22        int            Alert23                Alert 23        0        100        
*  23        int            Alert24                Alert 24        0        100        
*  24        int            Alert25                Alert 25        0        100        
*  25        int            Alert26                Alert 26        0        100        
*  26        int            Alert27                Alert 27        0        100        
*  27        int            Alert28                Alert 28        0        100        
*  28        int            Alert29                Alert 29        0        100        
*  29        int            Alert30                Alert 30        0        100        
*  30        int            Alert31                Alert 31        0        100        
*  31        int            Alert32                Alert 32        0        100        
*  32        int            Alert33                Alert 33        0        100        
*  33        int            Alert34                Alert 34        0        100        
*  34        int            Alert35                Alert 35        0        100        
*  35        int            Alert36                Alert 36        0        100        
*  36        int            Alert37                Alert 37        0        100        
*  37        int            Alert38                Alert 38        0        100        
*  38        int            Alert39                Alert 39        0        100        
*  39        int            Alert40                Alert 40        0        100        
*/

const char ALERT_CLIENTID[] =    "Alert Client" ;
const char ALERT_TOPICID[] =  "mwp/data/alert/alert/";
const char ALERT_JSONID[] =  "mwp/json/data/alert/alert/";
#define ALERT_LEN 40

union   ALERT_  {
   int     data_payload[ALERT_LEN] ;

   struct  {
      int   Alert1	;		//   
      int   Alert2 	;		//   
      int   Alert3	;		//   
      int   Alert4	;		//   
      int   Alert5	;		//   
      int   Alert6	;		//   
      int   Alert7	;		//   
      int   Alert8	;		//   
      int   Alert9	;		//   
      int   Alert10	;		//   
      int   Alert11	;		//   
      int   Alert12	;		//   
      int   Alert13	;		//   
      int   Alert14	;		//   
      int   Alert15	;		//   
      int   Alert16	;		//   
      int   Alert17	;		//   
      int   Alert18	;		//   
      int   Alert19	;		//   
      int   Alert20	;		//   
      int   Alert21	;		//   
      int   Alert22	;		//   
      int   Alert23	;		//   
      int   Alert24	;		//   
      int   Alert25	;		//   
      int   Alert26	;		//   
      int   Alert27	;		//   
      int   Alert28	;		//   
      int   Alert29	;		//   
      int   Alert30	;		//   
      int   Alert31	;		//   
      int   Alert32	;		//   
      int   Alert33	;		//   
      int   Alert34	;		//   
      int   Alert35	;		//   
      int   Alert36	;		//   
      int   Alert37	;		//   
      int   Alert38	;		//   
      int   Alert39	;		//   
      int   Alert40	;		//   
   }  alert  ;
}  ;
union  ALERT_  alert_  ;

char* alert_ClientData_var_name [] = { 
    "Alert1",
    "Alert2 ",
    "Alert3",
    "Alert4",
    "Alert5",
    "Alert6",
    "Alert7",
    "Alert8",
    "Alert9",
    "Alert10",
    "Alert11",
    "Alert12",
    "Alert13",
    "Alert14",
    "Alert15",
    "Alert16",
    "Alert17",
    "Alert18",
    "Alert19",
    "Alert20",
    "Alert21",
    "Alert22",
    "Alert23",
    "Alert24",
    "Alert25",
    "Alert26",
    "Alert27",
    "Alert28",
    "Alert29",
    "Alert30",
    "Alert31",
    "Alert32",
    "Alert33",
    "Alert34",
    "Alert35",
    "Alert36",
    "Alert37",
    "Alert38",
    "Alert39",
    "Alert40",
}  ;

/*
* Block ID: A001C
* Block Name: alertCommand
* Description: Alert Command Block
* From: blynkAlert
* To: xxx
* Category: alert
* MQTT Client ID: 
* MQTT Topic ID: command/rainbird/command
* MSG Length: 7
*  word #        data type            variable                description        min        max        nominal
*  0        int            clearCommand                Command Word - Clear        0        1        0
*/

const char ALERTCOMMAND_CLIENTID[] =    "" ;
const char ALERTCOMMAND_TOPICID[] =  "mwp/command/rainbird/command";
const char ALERTCOMMAND_JSONID[] =  "mwp/json/command/rainbird/command";
#define ALERTCOMMAND_LEN 7

union   ALERTCOMMAND_  {
   int     data_payload[ALERTCOMMAND_LEN] ;

   struct  {
      int   clearCommand	;		//   1=Clear Alerts
   }  blynkalert  ;
}  ;
union  ALERTCOMMAND_  alertCommand_  ;

char* alertcommand_ClientData_var_name [] = { 
    "A001C:clearCommand",
}  ;

/*
* Block ID: L001D
* Block Name: logger
* Description: logger Data
* From: logger
* Category: logger
* Type: data
* MQTT Client ID: Logger Client
* MQTT Topic ID: 
* MSG Length: 10
*  word #        data type            variable                description        min        max        nominal
*  0        int            pump                Pump Number 1,2,3 Wells & 4 Irrigation                        
*  1        int            param1                Additional source desc - 1 front 2 back 3 outback                        
*  2        int            param2                Additional source desc - 1-22 zones                        
*  3        int            intervalFlow                Gallons Flowed in Interval                        
*  4        int            pressure                Static Pressure                        
*  5        int            amperage                Integer Represents Amps                        
*  6        int            temperature                Temperature                        
*  7        int            timestamp                unix timestamp                        
*  8        int            unused1                                        
*  9        int            unused2                                        
*  10        int            unused3                                        
*  11        int            unused4                                        
*  12        int            unused5                                        
*  13        int            unused6                                        
*  14        int            unused7                                        
*  15        int            unused8                                        
*  16        int            unused9                                        
*  17        int            unused10                                        
*  18        int            unused11                                        
*  19        int            unused12                                        
*/

const char LOGGER_CLIENTID[] =    "Logger Client" ;
const char LOGGER_TOPICID[] =  "mwp/data/logger/logger/L001D";
const char LOGGER_JSONID[] =  "mwp/json/data/logger/logger/L001D";
#define LOGGER_LEN 10

union   LOGGER_  {
   int     data_payload[LOGGER_LEN] ;

   struct  {
      int   pump	;		//   
      int   param1	;		//   
      int   param2	;		//   
      int   intervalFlow	;		//   
      int   pressure	;		//   
      int   amperage	;		//   
      int   temperature	;		//   
      int   timestamp	;		//   
      int   unused1	;		//   
      int   unused2	;		//   
      int   unused3	;		//   
      int   unused4	;		//   
      int   unused5	;		//   
      int   unused6	;		//   
      int   unused7	;		//   
      int   unused8	;		//   
      int   unused9	;		//   
      int   unused10	;		//   
      int   unused11	;		//   
      int   unused12	;		//   
   }  logger  ;
}  ;
union  LOGGER_  logger_  ;

char* logger_ClientData_var_name [] = { 
    "L001D:pump",
    "L001D:param1",
    "L001D:param2",
    "L001D:intervalFlow",
    "L001D:pressure",
    "L001D:amperage",
    "L001D:temperature",
    "L001D:timestamp",
    "L001D:unused1",
    "L001D:unused2",
    "L001D:unused3",
    "L001D:unused4",
    "L001D:unused5",
    "L001D:unused6",
    "L001D:unused7",
    "L001D:unused8",
    "L001D:unused9",
    "L001D:unused10",
    "L001D:unused11",
    "L001D:unused12",
}  ;

/*
* Block ID: 
* Block Name: log
* Description: Log Data
* From: log
* Category: log
* Type: data
* MQTT Client ID: Log Client
* MQTT Topic ID: 
* MSG Length: 8
*  word #        data type            variable                description        min        max        nominal
*  0        int            Controller                Controller        1        5        1
*  1        int            Zone                Zone        1        32        1
*  2        float            pressurePSI                Pressure in PSI - Well3        0        100        65
*  3        float            temperatureF                Temperature - Well3 Supply Line        0        125        80
*  4        float            intervalFlow                Gallons in interval        0        5        0.5
*  5        float            amperage                Amperage        0        2024        1000
*  6        float            secondsOn                Seconds On Time for Pump        0        2024        14400
*  7        float            gallonsTank                Gallons in Tank (pressure sensor)        0        2024        2000
*/

const char LOG_CLIENTID[] =    "Log Client" ;
const char LOG_TOPICID[] =  "mwp/data/log/log/";
const char LOG_JSONID[] =  "mwp/json/data/log/log/";
#define LOG_LEN 8

union   LOG_  {
   int     data_payload[LOG_LEN] ;

   struct  {
      int   Controller	;		//   
      int   Zone	;		//   
      float   pressurePSI	;		//   
      float   temperatureF	;		//   
      float   intervalFlow	;		//   
      float   amperage	;		//   
      float   secondsOn	;		//   
      float   gallonsTank	;		//   
   }  log  ;
}  ;
union  LOG_  log_  ;

char* log_ClientData_var_name [] = { 
    "Controller",
    "Zone",
    "pressurePSI",
    "temperatureF",
    "intervalFlow",
    "amperage",
    "secondsOn",
    "gallonsTank",
}  ;


//#define MilanoWaterProject\IrrigationHeader.h  (created and maintained in Excel)
/*********************************************************************************
 *********************************************************************************
 **** ^^^           ^^^           ^^^           ^^^          ^^^          ^^^ ****
 **** |||           |||           |||           |||          |||          ||| ****
 **** Data Above This Line is Auto Generated from the Excel Spreadsheet Above ****
 ****                                                                         ****
 *********************************************************************************
 ********************************************************************************/

/*********************************************************************************
 *********************************************************************************
 ******   Sensors 0-3 are standard flow sensors with 10 data words         *******
 ******   Sensors 4-7 are extended sensors with 20 data words              *******
**********************************************************************************/

struct flowSensorConfigTable flowSensorConfig[8] = {
    {0, "Well3",         WELL3SENS_CLIENTID, WELL3SENS_TOPICID, WELL3SENS_JSONID, WELL3SENS_LEN},
    {1, "TANK",          TANKSENS_CLIENTID,     TANKSENS_TOPICID,TANKSENS_JSONID, TANKSENS_LEN},
    {2, "IRRIGATION",    IRRIGATIONSENS_CLIENTID, IRRIGATIONSENS_TOPICID, IRRIGATIONSENS_JSONID,IRRIGATIONSENS_LEN},
    {3, "HOUSE",         HOUSESENS_CLIENTID, HOUSESENS_TOPICID, HOUSESENS_JSONID, HOUSESENS_LEN},
    {4, "SPARE",         GENERICSENS_CLIENTID, GENERICSENS_TOPICID , GENERICSENS_JSONID, GENERICSENS_LEN},
    {5, "SPARE",         GENERICSENS_CLIENTID, GENERICSENS_TOPICID , GENERICSENS_JSONID, GENERICSENS_LEN},
    {6, "WELL",         WELLSENS_CLIENTID, WELLSENS_TOPICID, WELLSENS_JSONID, WELLSENS_LEN},
    {7, "SPARE",         GENERICSENS_CLIENTID, GENERICSENS_TOPICID, GENERICSENS_JSONID, GENERICSENS_LEN},
};
