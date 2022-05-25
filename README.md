# SingleWheel

## What is it? 
The Single wheel is our attempt at making a [OneWheel]([https://www.google.com](https://onewheel.com/?nbt=nb%3Aadwords%3Ag%3A597585506%3A39312416398%3A573373801154&nb_adtype=&nb_kwd=onewheel%20%2B&nb_ti=kwd-657093419034&nb_mi=&nb_pc=&nb_pi=&nb_ppi=&nb_placement=&nb_si={sourceid}&nb_li_ms=&nb_lp_ms=&nb_fii=&nb_ap=&nb_mt=e&gclid=CjwKCAjwp7eUBhBeEiwAZbHwkdSuBAPFqm_wTRfxSZVAjpu4NjOy7WkXVFnnXvONL2WU1h8_QV9bMBoCCQMQAvD_BwE))
  ### Hardware
     - Electronic Speed Controller (ESC)
     - 48V in hub motor
     - Homemade frame
     - Micro controller  (Blue Pill)
     - Inertial Messurment Unit (IMU)

   ### Software
    - PID Loop
    - Motor Controller
    - IMU data collecter

## How it works
  Our software is going to pull the IMU for new data, when new data is collected the main loop is going to be flagged that data is ready to be used. The
  main loop will consume the new data and process it through the PID controller and use the output as a value to be consumed by the motor controller.
  
  
