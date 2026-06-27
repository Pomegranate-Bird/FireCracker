
# Motivations 
1. What problems do we want to address with our FireCrackers? 
    Improving wildfire detection and emergency response times within rural communities.
2. Why is this problem worth addressing?
    Rural communities lack the necessary infrastructure to detect wildifres until it's too late. Since many of the available products on the market are not afforable and lack the necessary commitment to changing rural communities, FireCracker was created. FireCrackers are designed to be modular, easily deployed and provide real time coverage for any rural enviroment. 
3. Who are the intended users?
    Everyday people living in a rural communties are the intended users, as FireCracker sensors would not only provide the hardware to detect wildfires but the software and API to monitor and detect high wildfire risk areas.
4. How are FireCrackers an effective solution?
    FireCracker sensors will address the needs of users by providing an early-fire detection system at a low-cost, live updates and warnings for users. FireCrackers are modular, created using afforable off the shelf electronics, making them easy to mass-produce and deploy. Additionally, FireCrackers are low-power, and self-sustaining meaning they can operate independently of infastructure, making them robust during strong weather conditons such as strong winds, but importantly during wildfires. Additionally the data collected through FireCracker sensors will provide users with important enviromental metrics such as temperature, humidity and air quality, important metrics vital for firefighting operations. 

## Purpose 
When discussing the design of our FireCrackers sensors, we came to the conclusion that we needed to create sensors that were independent of infrastructure. We could not rely on receiving a source of external power, as it was vulnerable to power outtages which would render them useless, which occurs often in the La Jolla reseravtion. SDG&E (San Diego Gas & Electric) utilizes planned power outtages during strong wind condtions as a preventive measure to prevent the rapid spread of a potential wildfire. Therefore the FireCracker has to be self-sustaining and have low-power consumption, all while maximizing area coverage. By inspecting other proposed solutions to the problem of early wildfire detection we were able to discover that our hypothesis worked, albeit that some of our sensors were not needed, such as a smoke sensor which fail outdoors. By utilizing low-power electronics and a low-power communication protocol and periodic sensor measurements, we could reliably utilze solar panels to keep our senors online making them self-reliant. We still had to come up with a solution to address two problems, Fire detection and sensor Placement. We discovered that we could utilize a node cluster architecture to detect wildifres and cross validate. By placing nodes some distance away from each other but still having an area overlap, we could cover more area and utilize one sensor's measurements to cross validate another node's wildfire warning. Another benefit that came from utilizing a node architecture was all our nodes would send their data to a base node, which would carry out the data processing and computations to detect forest fires, saving all the other sensors from expending power needed for constant monitoring. 

#### Python Dependencies:
1. time
2. serial
3. csv


