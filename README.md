# PID: A19149079
# Name: Marvin Cruz Gomez

# PID: A19185386
# Name: Caleb Ong

## FireCracker Slides
https://docs.google.com/presentation/d/1zmcKbAPm6wtAK6BY36sYZwY3UlBFZXPV3XgwUgp0h9M/edit?slide=id.g3c0a05cde5f_0_2180#slide=id.g3c0a05cde5f_0_2180

1. What problems do we want to address with our FireCrackers? 
    Improving early wildfire detection and emergency response times within rural communities.
2. Why is this problem worth addressing?
    Rural communities lack the necessary infrastructure to detect wildifres until it's too late. Since there have been many products that lack the affordability or commitment to changing rural communities, we identified the need for a product that was open source, cheap to manufacture and easily reproducable that would address early-wildfire prevention. On a personal note, I have experinced having local wildfires near my home and understand the feeling of dread, the feeling of not only potentially losing your home but the life built within it. Which could've been prevented through an early wildfire detection system. The problem is worth addressing not only because it's personal but because we could help all rural communities around the globe. 
3. Who are the intended users?
    The intended users are the everyday people in a rural community. The purpose of our product is to provide a cheap and cost effective solution to creating clusters of fire detection stations across rural communities that could be built by anyone. In addition, our FireCrackers have access to weather APIs such as Synoptic, the largest global repository of weather and enviroment data, to use their data to train our machine learning model to detect fires. 
4. How are FireCrackers an effective solution?
    FireCracker sensors will address the needs of rural communities by providing an early-fire detection system at a low cost, transperency through an open source model, and live fire updates and warnings for users. Our FireCrackers are low-power, and self-sustaining sensors meaning they can operate independently of infastructure, making them robust during strong weather conditons such as strong winds, but importantly during wildfires. Additionally the data collected through FireCracker sensors will provide users with important enviromental metrics such as temperature, humidity and air quality, important metrics vital for firefighting operations. 

FireCracker Design thought process:

5. README discussion of your solution design
When discussing the design of our FireCrackers sensors, we came to the conclusion that we needed to create sensors that were independent of infrastructure. We could not rely on receiving a source of external power, as it was vulnerable to power outtages which would render them useless, which occurs often in the La Jolla reseravtion. SDG&E (San Diego Gas & Electric) utilizes planned power outtages during strong wind condtions as a preventive measure to prevent the rapid spread of a potential wildfire. Therefore the FireCracker has to be self-sustaining and have low-power consumption, all while maximizing area coverage. By inspecting other proposed solutions to the problem of early wildfire detection we were able to discover that our hypothesis worked, albeit that some of our sensors were not needed, such as a smoke sensor which fail outdoors. By utilizing low-power electronics and a low-power communication protocol and periodic sensor measurements, we could reliably utilze solar panels to keep our senors online making them self-reliant. We still had to come up with a solution to address two problems, Fire detection and sensor Placement. We discovered that we could utilize a node cluster architecture to detect wildifres and cross validate. By placing nodes some distance away from each other but still having an area overlap, we could cover more area and utilize one sensor's measurements to cross validate another node's wildfire warning. Another benefit that came from utilizing a node architecture was all our nodes would send their data to a base node, which would carry out the data processing and computations to detect forest fires, saving all the other sensors from expending power needed for constant monitoring. 


[FireCracker Overview](https://www.youtube.com/watch?v=OKe77LQL5o8)
[FireCracker Demo](https://www.youtube.com/watch?v=O5Td7177wPE)

7. Division of work
- Marvin:
    - Researched on forest fire detection and data
    - Worked on presentation
    - Got ESP32's solar panels and microprocessors
    - Incorporated sensors with board
    - Enabled communication across boards
    - Added thresholding to detect "smoldering" fires
- Caleb:
    - Researched on forest fire detection methods
    - Worked on presentation
    - Got PM sensors and charging battery modules
    - Worked on space invaders project


#### Python Dependencies:
1. time
2. serial
3. csv


