

YouTube video demonstrating prototype design and addressing design questions

1. What is the use case that you are trying to address? 
    Improving emergency response times and early wildfire detection and prevention within rural communities.

2. Why is this problem worth addressing?
    Rural communities lack the necessary infastructure to detect wildifres early until it's too late. We identified the need for a product that was open source, cheap to manufacture and easily reproducable that could address this problem. The problem is worth addressing not only because it's personal but because we could help all rural communities around the globe. On a personal note the problem is worth addressing since there have been many products that lack the affordability or commitment to changing rural communities. Additionally I have experinced having local wildfires near my home and understand the feeling of dread, the feeling of not only potentially losing your home but the life built withing it. Which could've been prevented through an early wildfire detection system.
3. Who is the intended user(s)?
    The intended users are the everyday person in a rural community. The purpose of our product is to provide a cheap and cost effective solution to creating a set of fire detection stations across a rural community, that could be built by aynone. An additional user of our FireCrackers will be weather APIs such as Synoptic data, the largest global repository of weather and eviroment data. 
4. How is your solution addressing the needs of the user?
    Our FireCracker sensor will be addressing the needs  rural communities by providing a low cost sensor that could detect wildfires during the smoldering growth phase. Additionally through a collaboration with Synoptic data we hope to integrate our live data into their global weather and eviromental data repository, allowing our data to be used for research and other fire detection platforms. Most importantly the purpose of our data aquistion through our FireCracker sensors is to give the La Jolla Indian reservation the ability to detect early fires, and Cal Fire with on the ground live data during power outtages and Wildifres. 

FireCracker Design thought process:

5. README discussion of your solution design
When discussing the design of our FireCrackers sensors, we came to the conclusion that we needed to create sensors that were independent of infrastructure. We could not rely on receiving a source of external power, as it was vulnerable to power outtages which would render them useless, which occurs often in the La Jolla reseravtion. SDG&E utilizes planned power outtages during strong wind condtions as a prevenative measure to prevent the rapid spread of a potential wildfire. Therefore we needed to be self-sustaining, and lower-power, all while maximizing area coverage. By inspecting other proposed solutions to the problem of early wildfire detection we we able to discover that our hypothesis worked, albeit that some of our sensors were not needed, such as a smoke sensor which fail outdoors. By utilizing low-power electronics and a low-power communication protocol and periodic sensor measurements, we could reliably utilze solar panels to keep our senors online making them self-reliant. We still had to come up with a solution to address two problems, Fire detection and sensor Placement. We discovered that we could utilize a node cluster architecture to detect wildifres and cross validate. By placing nodes some distance away from each other but still having an area overlap, we could cover more area and utilize one sensor's measurements to validate another node's wildfire warning. Another benefit that came from utilizing a node architecture was all our nodes would send their data to a base node, which would carry out the fire detection computations saving all the other sensors from expending power needed for around the clock sensing. 



#### Python Dependencies:
1. time
2. serial
3. csv


