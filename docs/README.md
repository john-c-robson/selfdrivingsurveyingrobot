






Self-Driving RC Car using Lidar Technology to Map Environments





General Computing Project





John Robson

2021 / 2022


**DECLARATIONS**

I declare the following:

(1) that the material contained in this dissertation is the end result of my own work and that due acknowledgement has been given in the bibliography and references to **ALL** sources be they printed, electronic or personal.

(2) the Word Count of this Dissertation is 11676

(3) that unless this dissertation has been confirmed as confidential, I agree to an entire electronic copy or sections of the dissertation to being placed on the eLearning Portal (Blackboard), if deemed appropriate, to allow future students the opportunity to see examples of past dissertations.  I understand that if displayed on eLearning Portal it would be made available for no longer than five years and that students would be able to print off copies or download.  

(4) I agree to my dissertation being submitted to a plagiarism detection service, where it will be stored in a database and compared against work submitted from this or any other School or from other institutions using the service.  

In the event of the service detecting a high degree of similarity between content within the service this will be reported back to my supervisor and second marker, who may decide to undertake further investigation that may ultimately lead to disciplinary actions, should instances of plagiarism be detected.

(5) I have read the Northumbria University/Engineering and Environment Policy Statement on Ethics in Research and Consultancy and I confirm that ethical issues have been considered, evaluated and appropriately addressed in this research.



SIGNED: John Robson 24/08/2022




**Acknowledgements**

I want to take this opportunity to thank my family and friends for their support during my university studies. I would also like to extend thanks to my project supervisor Dr Martin Wonders as, without his help and expertise, this dissertation would not have been possible. Finally, I would like to thank Graham Coulby for their support during my studies at Northumbria University.













**Contents**

[1.0	Abstract	6](#_toc112163442)

[2.0	Introduction	7](#_toc112163443)

[3.0	Research and Planning	9](#_toc112163444)

[3.1	Problem Identification	9](#_toc112163445)

[3.2	Literature Review	9](#_toc112163446)

[3.2.1	Overview of Relevant Research	9](#_toc112163447)

[3.2.2	Technical Areas to Solve	11](#_toc112163448)

[3.2.2.1	LiDAR	11](#_toc112163449)

[3.2.2.2	Point Clouds	11](#_toc112163450)

[3.2.2.3	Simultaneous Localisation and Mapping	11](#_toc112163451)

[3.2.2.4	Technological limitations	12](#_toc112163452)

[3.2.2.5	Gold Standard vs Low-cost Hardware	13](#_toc112163453)

[3.2.2.6	Car	13](#_toc112163454)

[3.2.2.7	Environmental Impacts	13](#_toc112163455)

[3.2.2.8	Point Clouds	13](#_toc112163456)

[3.2.2.9	Sensor Accuracy	13](#_toc112163457)

[3.2.2.10	Robotic Impacts	14](#_toc112163458)

[3.2.2.11	MPU and MCU	14](#_toc112163459)

[3.3	Approaches to problem solution	14](#_toc112163460)

[3.3.1	Priority requirements	14](#_toc112163461)

[3.3.2	Product requirements discussion	15](#_toc112163462)

[3.4	Justification of the tools and techniques	15](#_toc112163463)

[3.4.1	LiDAR	15](#_toc112163464)

[3.4.2	Hector SLAM	16](#_toc112163465)

[3.4.3	ROS	16](#_toc112163466)

[3.4.4	Raspberry PI	16](#_toc112163467)

[3.4.5	Arduino	16](#_toc112163468)

[3.4.6	Desktop Machine	16](#_toc112163469)

[4.0	Design, Implementation and Testing	18](#_toc112163470)

[4.1	Design	18](#_toc112163471)

[4.2	Implementation	21](#_toc112163472)

[4.2.1	Logic System	21](#_toc112163473)

[4.2.2	Movement System	23](#_toc112163474)

[4.2.3	Combining the systems	24](#_toc112163475)

[4.3	Testing	25](#_toc112163476)

[5.0	Evaluation and Conclusions	30](#_toc112163477)

[5.1	An evaluation of the product.	30](#_toc112163478)

[5.2	An evaluation of the project process.	31](#_toc112163479)

[5.3	Conclusions	32](#_toc112163480)

[5.4	Recommendations	33](#_toc112163481)

[6.0	References	34](#_toc112163482)

[7.0	Appendices	37](#_toc112163483)

[7.1	Terms of Reference	37](#_toc112163484)

[Self-Driving RC Car using Lidar Technology to Map Environments	38](#_toc112163485)

[Proposed Work	38](#_toc112163486)

[Aims and Objectives	39](#_toc112163487)

[Aims	39](#_toc112163488)

[Objectives	39](#_toc112163489)

[Skills	39](#_toc112163490)

[KF5042 Intelligent systems	39](#_toc112163491)

[KF6052 Machine Learning and Computer Vision	39](#_toc112163492)

[KV6006 Internet of Things	39](#_toc112163493)

[KF5012 Software Engineering Practice	40](#_toc112163494)

[Sources of information/bibliography	40](#_toc112163495)

[Resources – statement of hardware/software required	40](#_toc112163496)

[Assessment Criteria	40](#_toc112163497)

[7.2	Other appendices	42](#_toc112163498)

[7.2.1	Arduino Code for MQTT Instructions	42](#_toc112163499)

[7.2.2	Arduino Code for Variable Wheel Speed	42](#_toc112163500)




1. # <a name="_toc112163442"></a>**Abstract** 
During 2019-2020 there were a total of 1,580 road deaths that occurred in Great Britain, with 24,470 people being killed or seriously injured. In 2018 a fatal accident occurred with an Uber Self-driving vehicle that collided with a pedestrian. Further studies performed by Intel showed their "MobileEye" system could only detect the pedestrian in the dashcam footage 1 second before the accident happened using visual sensor data. This dissertation aims to research and develop a prototype LiDAR autonomous vehicle capable of detecting obstacles.

This dissertation completed a literature review of the current standard of robotic systems used for vehicle movement, assessing the viable options available to create a robust, accurate prototype capable of producing 2d point-cloud scans of environments and producing live movement corrections. 

The final model produced comparably accurate scans to physical measurements with less than 4% measurement error while also providing live, low-latency movement instructions that allow a robot to navigate an environment safely, avoiding static and temporary obstacles.





1. # <a name="_toc112163443"></a>**Introduction**
During 2019-2020 there were a total of 1,580 road deaths that occurred in Great Britain, with 24,470 people being killed or seriously injured (Haylock and Tranter, 2021). Road traffic accidents are an issue that could be addressed with self-driving or even assisted driving systems to provide road users with a safer choice when driving on roads. Although they may help address the number of incidents, there have been cases where accidents have still occurred in these systems. 

For example, in 2018, a fatal accident occurred with an Uber Self-driving vehicle that collided with a pedestrian. It was believed to have happened due to low lighting conditions affecting the system's performance (Kohli and Chadha, 2020). Studies being performed by Intel showed that their "MobileEye" system itself was only able to detect the pedestrian in the dashcam footage 1 second before the accident happened (Shashua, 2018). It can be deduced that work is still required to make these systems safer and more robust.

Tesla's design choice is to use a collection of distance and visual sensors to deliver a safe and practical model to protect against the drawbacks each other have (Miguel *et al.*, 2016). However, when weather conditions worsen, such as low lighting, fog and heavy rainfall, these systems' performances can worsen and struggle to perform accurately (Vishalakshi, Gopalakrishna and Hanumantharaju, 2016), which could potentially lead to accidents still occurring. Currently, in the front bumper of some Tesla Models, radars and cameras are used. Radars can detect the distance of objects, much like Light detection and ranging sensors (LiDAR). However, they cannot detect motionless objects like stationary humans and parked cars (Miguel *et al.*, 2016). 

LiDAR functions by emitting lasers against surfaces and then precisely measuring the time the laser took to return from the reflected surface to calculate the distance. This allows LiDAR to detect motionless objects. The accuracy of LiDAR's ranging ability is a benefit due to the highly reliable physical information it gathers (Li and Ibanez-Guzman, 2020). The performance of LiDAR outperforms visual odometry regarding distance ranging due to its robustness in light and dark environments (Harik and Korsaeth, 2018). Although this is the case, LiDARs are commonly combined with a camera to complement one another when used in practice. Cameras are known for their poor ability to provide distance estimations but the functional ability for object recognition, whereas LiDAR performs the contrary of this (Li, 2013). Therefore, due to the benefits of LiDAR, it is seen as a promising technology for autonomous driving solutions (Thakur, 2016).

The aims of this dissertation are to research how autonomous systems for vehicles are used and their feasibility in safely mapping environments and also to build a prototype system that allows a vehicle to manoeuvre itself through a destination using LIDAR technology. 

Several objectives have been outlined to achieve these aims for this dissertation:

1. **Conduct a literature review surrounding autonomous vehicles identifying their methodology and design choices.**
   1. Produce a literature review
   1. Create a list of requirements
   1. Select design choices backed by literature
1. **Develop new skills within the internet of things.**
   1. Review the field of internet of things
   1. Experiment with hardware applications
1. **Creating design for the vehicle and program system being developed.**
   1. Create design templates for hardware layout
   1. Create a template for communication architecture
1. **Create the prototype.**
   1. Create a practical prototype
   1. Configure programmatically
1. **Experimental work on the system to ensure it is performing as per the design stage.**
   1. Conduction testing against system requirements
   1. Ensure the prototype is achieving the aims of the dissertation
1. **Evaluation of the project, literature review and systems used in the project.**
1. **Conclusion of the project and recommended future work.**

This dissertation plans to demonstrate the performance of low costing LIDAR, micro control units (MCU) and micro processing units (MPU) technologies to generate autonomously mapped environments by developing a prototype that provides an accurate collision avoidance system. 

Chapter 2 will cover a review of the literature to evaluate the current state of technology and current systems to ensure that critical choices are made in the design choices of the prototype. This will assist in finding requirements and ensuring that the tools and techniques chosen for the system are appropriate solutions to creating a LiDAR-based autonomous driving system. This will allow the appropriate methods to be selected for the design stage and assist in driving the development forward. 

Chapter 3 will cover the design, implementation and testing of the prototype. The prototype design will consist of concluded choices made for the prototype from findings within the literature. Implementation will discuss the processes involved during the prototype construction and the difficulties or changes that were required during the build. Testing will include experiments that evaluate the finished product against the requirements that were discussed in chapter 2.

Chapter 4  will contain the evaluation and conclusions made from this dissertation. It will include an evaluation of the prototype created, with a critical discussion of the final product against the requirements. It also includes a review of the project process, discussing how it kept on track with time allocations, skills acquired, and legal and ethical discussion on the subject matter. Finally, a dissertation's conclusion and what future recommendations could be looked into to improve the work completed further.


1. # <a name="_ref112108431"></a><a name="_ref112108435"></a><a name="_toc112163444"></a>**Research and Planning**
This chapter aims to evaluate the literature in the subject area to ensure that the most viable choices are made for the prototype system. a collection of requirements will be drawn up to define and the allocation of tools and techniques to be justly selected to ensure that these requirements are met.
1. ## ` `**<a name="_toc112163445"></a>Problem Identification**
During 2019-2020 there were a total of 1,580 road deaths that occurred in Great Britain, with 24,470 people being killed or seriously injured (Haylock and Tranter, 2021). Research has been completed in the field of driving assisting systems to assist in danger detections for drivers. Tesla's design choice is to use a collection of distance and visual sensors to deliver a safe and practical model to protect against the drawbacks each other have (Miguel *et al.*, 2016). Although this system has limitations when deployed in specific environmental settings. For example, when weather conditions worsen in terms of low lighting, fog and heavy rainfall, these system performances can worsen and struggle to perform accurately (Vishalakshi, Gopalakrishna and Hanumantharaju, 2016), which could potentially lead to accidents still occurring. Vision sensors are utilised in the industry currently over LiDAR due to the cost and maintenance involved (Pazhayampallil and Kuan, 2013). New low-cost developments in LiDAR solutions require a review of their ability to assist in this system needs to evaluate the viability of its use within this sector.
1. ## ` `**<a name="_ref112108248"></a><a name="_ref112108262"></a><a name="_ref112108268"></a><a name="_ref112108373"></a><a name="_ref112108378"></a><a name="_toc112163446"></a>Literature Review**
   1. ### <a name="_ref112107089"></a><a name="_ref112107099"></a><a name="_ref112107127"></a><a name="_ref112108363"></a><a name="_toc112163447"></a>***Overview of Relevant Research***
This section aims to review current work to identify processes and technical areas which require further research to solidify a technical understanding. 

Gatesichapakorn (2019) produced a study that reviewed ROS-based robot navigation that included the use of both a 2D LiDAR and RGB-D camera. The prototype system used Docker images to install ROS and the required packages to run. Raspberry Pi 3 was used with a "Raspbian Stretch" operating system, allowing for a development environment with low power consumption requirements on inexpensive technology. This experiment was compared over two different onboard computers to evaluate if the experiments were possible to be completed. This is only a small subset of onboard computers were compared. All the used onboard computers were able to complete the map scans without issues, noted that Raspberry Pi had the longest successful runtime of 6 hours, only ending when manually stopped. The 2D LiDAR was positioned flat and 40cm above the floor during prototype development. LiDAR's limited field of view makes it unable to detect obstructions above or below its scanning plane, restricting the LiDAR from identifying obstructions nearer the movement portion of the prototype. The goal of avoiding obstacles was achieved in this study. However, it was noted that network communication delays could cause difficulties for remote calculations as there is a heavy throughput of data being sent, which could interfere with ROS’s navigation node. 

Similarly, a LiDAR bases robot solution was used by Malavaz (2018) in a review of its application in an agricultural environment. Due to the prototype being deployed in a GPS-denied environment, point cloud maps were captured of several environments that allowed the robot to follow preselected pathing routes. Initial developments of this system were created using a camera-based system, but due to sensitivity issues to light and atmospheric effects, the system's robustness was significantly impacted. This study aimed to cluster obstruction readings from the LiDAR in classifications of plant rows (preselected data points) and weeds (rogue data points). Unlike other papers, this system did not use multiple Simultaneous Localisation and Mapping (SLAM) techniques for either manoeuvring or mapping the environment but instead captured a dataset for later analysis. Although this still allowed for conclusions to be drawn for the system, research could be done to evaluate if SLAM would be a productive tool to use in this case study. Limitations were highlighted with the 2D-based LiDAR, depending on the sensor's height, as when too low the LiDAR was unable to identify plants due to weeds interrupting the LiDARS field of view. In contrast, when the sensor was too high, it could not sense weeds below its scanning plane. However, when positioned correctly, the work carried out showed promise in identifying weeds. Due to the issues found with the LiDARS field of view, it was suggested to use a 3D LiDAR in future work to negate this limitation.

In a study by Hutabarat (2019), the aim was to evaluate the autonomous application of LiDAR-based robots in obstacle-based environments. The prototype used was similar in design to that of Gatesichapakorn (2019), using a 2D LiDAR sensor for obstacle detection while utilising a Raspberry Pi 3 for data collection and motor control. This system also used ROS as its communication method for data handling the LiDAR readings. The experiments conducted were to evaluate the prototype's performance in an environment with several different shapes and coloured obstructions to identify limitations that the LiDAR may have. The findings resulted in the prototype having a 100% success rate in avoiding the obstacles but failing to identify transparent objects such as acrylic and polycarbonate bottles as the laser pulses that LiDAR emits do not get reflected by the objects or they are refracted in such a way that they do not return light back to the light sensor in the LiDAR.

Gul (2019) performed a comprehensive study on robot navigation techniques. It is mentioned that understanding the environment that the robot will be working in is essential, and defining the environment is needed to select a pathing algorithm correctly. Static and Dynamic environments have different obstacle definitions. A static environment has obstacles that do not change their position with respect to time, whereas a dynamic environment's obstacles do change. Utilising the correct pathing algorithm is essential in this, as with a static environment, an offline algorithm can be used to calculate a path for the robot to use. In contrast, a dynamic environment requires an online algorithm to calculate a path. Live sensor data is required to provide new information about the environment to avoid collisions with newly discovered obstructions. Because the these explored appoarchs, ensuring that the approach taken is fit for the work this dissertation plans to do is suitable. Incorrect design choices could cause safety issues which makes this a vital decision to be made. 

Rivai (2020) created a prototype robot equipped with a low-cost 2D LiDAR, a Raspberry Pi 3 for its size and computing capability and an Arduino for motor control. The purpose of this study is to review the performance of the prototype's ability to automatically construct accurate maps of environments. Multiple environments were scanned using the prototype, and Occupancy Grid maps were created with Hector-SLAM. These tests were performed in static environments, which do not demonstrate the effects of dynamically changing obstacles. To perform scans a “wall-following” algorithm was used, which kept the prototype a set distance from the wall and updated motor instructions to keep this state. The results showed that the prototype was able to localise correctly with only 3.9% error, and when allowed to move automatically to construct maps, produced them accurately with only an error rate of 4.59%.

2D LiDARs were utilised in all the reviewed studies, with limitations to the sensor's ability to detect transparent objects and the restrictive plane of view the LiDARs have due to only being able to scan a single plane. Malavaz (2018) demonstrated the importance of correct sensor positioning and the impact this had on capturing obstructions. When designing the prototype, ensuring enough consideration has been given to the placement of LiDAR sensors is vital as incorrect placement may cause the system to fail to detect obstructions. As Hutabarat (2019) pointed out, knowing what objects and materials are present in an environment should be considered. This is vital for the work the dissertation plans to complete, as the environments the prototype will be mapping are buildings which use glass. A futher consideration is that the restrictive capture plane outlined by Malavaz (2018) could have profound implications depending on where the sensor is placed. If the sensor is too high on a vehicle, it would fail to capture small vehicles, animals and children. Whereas, if it were placed too low, it could capture under large vehicles. Furthermore, if it is captured at the average window height on vehicles, the findings outlined in this review would indicate that LiDAR beams could be refracted by windows of other vehicles resulting in the LiDAR failing to capture critical obstacles.

Further research into LiDAR use is required to ensure the correct deployment used for this dissertation is functional. It would also be worth capturing data in an environment that has obstacles of different heights and transparent surfaces. This could provide further insight into the challenge and limitations of using LiDAR within this sector.

ROS was a commonly mentioned system that was used to facilitate communication methods between systems on the prototypes. However, it was mentioned by Gatesichapakorn (2019) that network communication delays could negatively impact this system's performance. With ROS being a highly selected choice and positively commented on, as well as highly successful system deployment in most of the studies, further research into this system is required to understand what the system provides and how it can be beneficial to this dissertation.

SLAM techniques were used throughout the reviewed studies, which functioned differently but provided similar mapping outputs. Although this system was not used in the study performed by Malavaz (2018), other studys created prototypes which produce accurate results when deploying SLAM techniques on their prototypes. Further research into these techniques will evaluate if the outcomes to using SLAM are beneficial to creating a solution for this dissertation.

Multiple low-powered processing circuits were used through these studies like Raspberry Pi and Arduino for performing movement calculations, environmental mapping solutions and motor control. Although these are popular solutions for solving onboard computer requirements (Gatesichapakorn, Takamatsu and Ruchanurucks, 2019; Hutabarat *et al.*, 2019; Rivai, Hutabarat and Jauhar Nafis, 2020), they are only a tiny subset of what is available for use. Research into these systems to understand their benefits and drawbacks is required. This will provide an understanding of which applications are applicable to these hardwares.

Following these papers' testing outcomes, a review of the sensor's accuracy to physical measurements should be completed once the prototype is created. This has proven to be to a proven method for assessing the accuracy. This is believed to be the case as the sensor's accuracy appears to be directly connected to both the prototype's ability to localise in an environment and the accuracy of the map being produced (Rivai, Hutabarat and Jauhar Nafis, 2020).
1. ### <a name="_ref112107433"></a><a name="_ref112107438"></a><a name="_toc112163448"></a>***Technical Areas to Solve***
   1. #### <a name="_ref111636293"></a><a name="_toc112163449"></a>***LiDAR***
Mobile laser scanning (MLS) is an approach which includes using laser measurements provided by moving vehicles to generate accurate spatial data of roads and surroundings in the form of point clouds maps (Li *et al.*, 2018). From this data collected by a laser scanner, conclusions can be made on the number, size and positions of both temporary objects (Vehicles and people) and permanent ones (Buildings, signs.). 

However, a technical problem found with LIDAR was with point cloud generation. Due to continuously mutating due to the LiDARs' inability to provide readings at a frequency that would allow for the detection of obstacles, as well as performing tracking and localisation solutions while travelling at speed (Domínguez *et al.*, 2011). 

A method of tracking used by Domínguez *et al. (2011)* was performed by clustering close measurements together to form obstacles. By doing this, they can continue to monitor these clustered over iterations of readings to keep their change in space accurate and identifiable. The value of using LiDARs for laser scanning is their ability to provide accurately ranged measurements of environments in real-time to facilitate the creation of a Point Cloud-based representation of its surroundings.
1. #### <a name="_toc112163450"></a>***Point Clouds***
Point clouds are a data list of coordinate readings held within a matrix. (Yang and Förstner, 2010) An appeal of creating point clouds with LiDAR is that the low latency between sensing to inspecting a surface is reduced to almost zero, allowing the point to be viewable almost instantaneously as the data is received from the sensor (Leberl, Irschara and Pock, 2010). Due to the complexity and variety present in point clouds, due to the variety of variables between datasets, irregular sampling, changing density, and various types of objects, the topic of classification and segmentation within the area of point clouds has become a very active topic (Grilli, Menna and Remondino, 2017). This has also shown issues with machine learning with point clouds, creating challenges due to point clouds not containing a regular data structure such as that in an image; pixels by width and height (Zhang *et al.*, 2019). 
1. #### <a name="_ref111727080"></a><a name="_ref111727090"></a><a name="_toc112163451"></a>***Simultaneous Localisation and Mapping***
SLAM is a technique used to estimate a sensor's motion within a reconstruction of a visited area. This was designed to achieve autonomous control of robots in 1985 (Chatila and Laumond, 1985). SLAM provides the ability to simultaneously estimate the position of a robot while also reconstructing the geometrical map of the visited area using point cloud mapping techniques. Both the estimation and reconstruction are heavily reliant on one another as a good map is required to compute the position; however, only a correct map can yield an accurate position (Ruckert, 2009).

A method known as scan-to-scan matching is often used to calculate position in laser-based SLAM approaches, but this can quickly accumulate errors with the position estimation (Hess et al., 2016). However, Scan-to-map matching restricts this error by limiting it with approaches such as Gauss-Newton, which can be performed to find a local optimum. When this approach is used with a sufficiently high rate of LiDAR, scan-to-map matching is found to be efficient and robust. 

SLAM has been applied and studied for use over many sensors for different robotic platforms and uses (Azzam et al., 2020) and can have many iterations that provide many alternative features. As a result, some well-refined versions of SLAM have been developed but are still dependent on the parameter tuning, specific platform use and the environment the robot is being deployed within. Because of this, a review of different techniques is appropriate to ensure the correct one is selected for this study.
##### **IMLS-SLAM**
IMLS-SLAM is a technique Deschaud (2018) developed to create a system that improves localisation accuracy by creating a map with an implicit moving least squares surface. This was evaluated using the KITTI training dataset (Menze and Geiger, 2015), which showed a premise of low drift for the simulation. Although the results of this algorithm show great promise in accuracy, it, unfortunately, does not work in real-time data capture exercises.
##### **Orb-SLAM**
Orb-SLAM is an algorithm that provides a real-time loop closing-based visual SLAM solution to point cloud creation using cameras (Mur-Artal, Montiel and Tardos, 2015). Although this method shows excellent results for place recognition (Mur-Artal and Tardós, 2014), the system requires a camera that provides a lower field of view than a LiDAR and provides less accurate range measurements (Zhen *et al.*, 2019). 
##### <a name="_ref111727078"></a>**Hector-SLAM**
The Hector-SLAM algorithm provides an accurate pose estimation of the mobile robot within its environment, which has been shown to perform very well in world-class competitions and for various real-world applications (Kohlbrecher *et al.*, 2014). With a single LIDAR mounted on the front of a robot and with the deployment of Hector SLAM for pose estimation, Harik and Korsaeth (2018) were able to present their robot's ability to adapt to structural changes present in crop growth in a greenhouse while still operating in the presence of humans. This demonstrates that not only is it possible for robots to work in static/slow-changing environments, but they can functionally operate with unpredictable human movement. During trial testing by Olalekan (2021), Hector SLAM provided lower accuracy results when the robot manoeuvred at high speeds, which tended to cause distortions in the map. This is thought to be caused by high-speed movement and turning, resulting in a distortion of the generated map. 
1. #### <a name="_toc112163452"></a>***Technological limitations***
The modern method used for external localisation is the use of Global Navigation Satellite System (GNSS) solutions. This can provide the absolute position on earth with reasonable precision when used in the right situation but can produce errors of around 5 meters in unacceptable environments like tunnels and caves (Debeunne and Vivet, 2020). L5 GPS is a service planned to provide a higher-powered service that includes increased bandwidth and an improved signal design but is not scheduled to be operational until 2027 (U.S. government, 2020). Although this provides position data, mobile robots require more than this information. Data is required on potential obstacles in a dynamic environment that the robot is exploring.

Cameras inherently have limitations due to their restrictive field of view and inability to provide accurate ranged data of environments (Zhen *et al.*, 2019). However, the information that can be extracted and classified from a camera allows it to provide a high level of environmental context. Ultrasonic sensors are used on vehicles to warn the driver when the sensor detects the vehicle is approaching an obstruction at short distances. This is primarily due to the sensors' restriction in ranging long distances, as although this sensor can provide accurate measurements for up to a few meters when met with noisy open-air conditions, problems arise with both the behaviour and accuracy of the sensor (Carullo and Parvis, 2001).
1. #### <a name="_toc112163453"></a>***Gold Standard vs Low-cost Hardware***
Gold standard LiDAR technologies are designed to perform high-frequency scans with accurate distant readings. Alternatively, new iterations of LiDAR have been developed that perform on a 2D scanning plane, which provides a similar result to gold standards in some cases with a much lower budgeting cost. Currently, the average price of a LiDAR sensor of a gold standard is around £18000. 

Because of this, the sensor is not being utilised in mobile vehicles as the average family car costs about £12000, making the cost not feasible for consumers. Because of this, there is a need for low-cost alternatives that can perform this task. The new iterations of low-cost LiDAR are sold for around £100, but provide readings at a lower frequency. The reduced laser strength restricts the ability to range over long distances and also potentially makes them susceptible to noise and interference.
1. #### <a name="_ref111639732"></a><a name="_toc112163454"></a>***Car*** 
Due to the danger of using a motor vehicle to test the practicality of LiDAR and SLAM techniques and the cost of a vehicle, a low costing alternative will be used to demonstrate the system. This allows for scaleable testing on all parts of the hardware to establish a proof of concept.
1. #### <a name="_toc112163455"></a>***Environmental Impacts***
A concern brought up in literature revolves around environmental impacts on robotic systems (Kohlbrecher et al., 2014). Regarding using cameras for environmental context, the lightening of the environment, fog and non-textured surfaces can cause issues for determining obstructions (Debeunne and Vivet, 2020). 

LiDAR, however, uses a near-infrared laser to perform scans to avoid interference with other sensors. Due to this laser type, the wavelength range of the infrared spectrum makes the sensor susceptible to high background light (Beer et al., 2018). An area that causes issues for LiDAR is natural obstructions, for example, rain and dust. Not only are these issues for the sensor, but they cause problems with mechanical designs and require these systems to be hardened against these conditions to make them applicable to a real-world application (Kohlbrecher et al., 2014).
1. #### <a name="_toc112163456"></a>***Point Clouds***
Point clouds are generated by drawing comparisons of readings from LiDAR sensors to create a mapped layout from the robot to its surrounding surfaces. Although point clouds hold ranging information about the environment (Leberl, Irschara and Pock, 2010), they can only be as accurate as the sensor being used. When creating these said maps, considerations must be made for the robot's distance to the scanned surface. 

An issue known as angular size is an inherited issue for LiDARs when scanning over a distance; as the distance increases, the resolution decreases (Domínguez *et al.*, 2011). Because of this, LiDAR performs poorly in open, natural outdoor unstructured environments (Debeunne and Vivet, 2020). Because of this, treating the LiDAR as a measuring sensor is required as, due to resolution, it becomes difficult to derive contextual information from the environment. 
1. #### <a name="_toc112163457"></a>***Sensor Accuracy***
When LiDARs are compared against cameras and radars which are being used in the field of self-driving cars, LiDAR is the most precise sensor when measuring range. As a result, the physical information evaluated by LiDAR algorithms is deemed highly reliable (Li and Ibanez-Guzman, 2020). However, the data collected by LiDAR makes it difficult to classify an object. Li (2020) found in their experiment that they could provide a vehicle classification in their dataset but could only detect pedestrians with an accuracy of 52.40%.
1. #### <a name="_ref111653727"></a> ***<a name="_toc112163458"></a>Robotic Impacts***
When attempting to locate the position of a robot while using LiDAR, there is a potential it can cause large computational requirements, which could cause issues for smaller IoT devices (Ruckert, 2009). An issue with robots during localisation is wheel slippage, but a LiDAR scanner can mostly compensate for this. Using the scan-to-map method allows for a new, acceptable pos-position of the robot within an environment (Harik and Korsaeth, 2018). 
1. #### ` `***<a name="_ref111658891"></a><a name="_ref111658899"></a><a name="_toc112163459"></a>MPU and MCU***
Micro-Processing Units (MPU) and Micro-Controller Units (MCU) can be used to facilitate different requirements. MPUs operate much like desktop computers, typically having separated memory, graphics processing and CPU on a single board and allowing operating system installation (Wunderlich, 1999). MCUs combine both the memory and CPU into a single microchip and are designed to execute a series of instructions contrary to MPUs (Berlia and Santosh, 2014).

MPU and MCU can use General Purpose Input Output (GPIO) pins to allow for low-level circuit control (Coulby *et al.*, 2020). However, MPUs can require additional libraries and permissions to be set to enable this feature (Loyse, 2017), whereas MCUs are designed out of the box to utilise this. Although MCUs are explicitly designed for GPIO control, in many cases (Gaillard and Eieland, 2013), MCU has clear advantages over MPUs for low-level hardware control as they often support analogue inputs with the need for additional circuitry. For example, Raspberry Pi does not support analogue inputs and requires separate analogue to digital converter (AD) circuitry.

MPUs are advantageous as they can run operating systems capable of running multiple applications simultaneously. This means they can provide GPIO control while also running webservers, processing applications, task scheduling, wait queues, and memory allocations and often have multicore and virtual memory support (Francis-Mezger and Weaver, 2018). 




1. ## ` `**<a name="_toc112163460"></a>Approaches to problem solution**

1. ### <a name="_ref111659612"></a><a name="_ref111659616"></a><a name="_toc112163461"></a>***Priority requirements***
From the literature review, a list of requirements for the system can be established for the prototype.

|No.|Requirement Description|
| - | - |
|1|Make movement decisions independently. |
|2|The system must be rigorous and must not crash.|
|3|Provide accurate scan results.|
|4|Be able to generate point cloud maps in real-time.|
|5|The system must be lightweight enough to function on a low computational device.|
|6|Must be functional in limited lighting environments.|
|7|Responsive to environmental changes.|

1. ### <a name="_toc112163462"></a>***Product requirements discussion***
Developing a complete system that can independently and safely move throughout an environment will confirm if a LiDAR can perform scans without human input [Section 3.3.1, Requirement 1]. The system should be able to perform these scans independently and could even be used with multiple devices to scan large environments without the cost of labour. Not only should the system be able to perform these scans, but it should also be designed as a motor vehicle safety system, as it must be able to identify dangers on its own. Ensuring the prototype is functional and stable enough to complete its task safely and without failing its main requirement [Section 3.3.1, Requirement 2]. For this to be possible, more research may be required to produce a minimal viable option that meets the required safety standard.

For papers that have used LiDAR in the past, reviewing the accuracy of the LiDAR's readings is a requirement that most papers meet [Section 3.2.2.1, Pg 11]. Due to this and the dissertation evaluating a low-cost alternative, a check will be done to ensure that the measurements being received are accurate and correct [Section 3.3.1, Requirement 3]. To be able to visually inspect how the system performs, it must produce point cloud maps in real-time [Section 3.3.1, Requirement 4]. Through doing this, a valid representation can be made of what the system can see can be created and evaluated.

Due to the limited space on the platform, this system must be able to perform on small, limited computational-powered technology. Ensuring that the system is lightweight enough to perform its tasks without restricting the performance of the rest of the system is essential [Section 3.3.1, Requirement 5]. Once this is done, a test can be performed to ensure that the system can perform in limited lighting environments. The basis for using the LiDAR sensor is to accommodate the shortfalls of other deployed sensors in the field [Section 3.3.1, Requirement 6]. A review of the system's ability to detect newly appearing obstructions and perform movement corrections is required to ensure the safety of the system and the environment [Section 3.3.1, Requirement 7]. 



1. ## ` `**<a name="_toc112163463"></a>Justification of the tools and techniques**

1. ### <a name="_toc112163464"></a>***LiDAR***
LiDAR typically consists of a pulsed laser diode (PLD) with avalanche photodetectors (APD) that are aligned to the focal plane of a telescoping lens which forms a rangefinder (Liu, Zhang and Hong, 2022). This rangefinder is then rotated at a frequency along the vertical axis, allowing it to capture ranges of objects along the plane (2D line-of-sight).

Other sensors like ultrasonic sensors, cameras, and radar are currently being used in newly manufactured cars to assist the driver in road safety. However, these sensors have drawbacks, including restricted distance monitoring, limited field of view, and poor performance in low lighting. These drawbacks have previously in the past have not been enough to accomplish a robust enough safety system in vehicles to avoid accidents (Shashua, 2018; Kohli and Chadha, 2020; Haylock and Tranter, 2021).

The advantage of using LiDAR is its ability to have 360 degrees of view with a functional distance ranging. From the drawbacks established by current industry standards, the benefits of LiDARs' ability to provide ranging measurements in low lighting conditions could play an essential role in increasing this system's overall robustness and safety. RPLiDAR by Slamtec is the model that will be used for this prototype. This LiDAR is only 2D, making it less proficient than that of a 3d LiDAR as the field of view on the Y axis is limited to a single plane. This is the case, the purpose of this dissertation is to evaluate the performance of an autonomous system on a smaller scale, and this choice of LiDAR is fit for this purpose.
1. ### <a name="_toc112163465"></a>***Hector SLAM***
<a name="_ref111653300"></a><a name="_ref111653311"></a>Using Hector SLAM with the RPLiDAR produces a point cloud map using constant readings from the LiDAR, allowing for the Hectors pose position algorithm to expand with each received scan. Hector slam uses the Gauss-Newton method to solve scan-matching problems. This also removes the need for an odometer, allowing for uncrewed ground vehicle mapping in uneven areas. Although many LiDAR SLAM solutions are available, Hector-SLAM has a larger selection of past examples of use and documentation to assist in the development of this prototype. By doing this, an accurate mapped representation of what the sensors can see will be possible to help assess LiDAR's performance.
1. ### <a name="_ref112100182"></a><a name="_toc112163466"></a>***ROS***
Communication for the robotic system is achieved using the Robotic Operating System 1 (ROS). The reasoning behind using ROS 1 over ROS 2 was the abundance of documentation and accessibility to the past documentation for systems developed using ROS 1. Due to this being the first exposure to the ROS systems, it was deemed viable to go with the more documented and accessible version. This will allow for a more robust and quickly developed communication system to be developed. The task of ROS as a whole will be to perform communication tasks fluently between languages through the use of node and subscription-based communication, both by serial communication and over the network, allowing for the transitions of both data and movement instructions to be communicated from RAW data to python (MPU), and finally to C (MCU).

1. ### <a name="_toc112163467"></a>***Raspberry PI***
Due to the size and low cost associated with the Raspberry Pi, it is the go-to choice for handling the low-level MPU requirements of the system. It also allows for a development environment to be installed upon it, allowing for more dynamic and complicated code to be deployed over other Internet of Things devices. It facilitates many languages to be used to fit whichever tasks are required for the task at hand, as well as the many benefits inherent in MPU systems [Section 3.2.2.11, Pg 14]. 
1. ### <a name="_toc112163468"></a>***Arduino***
For activating the motor controllers for the RC car, an Arduino was chosen, as it functions as a low-power MCU that can perform intelligent circuit executions. As mentioned earlier, MCU are designed out of the box to utilise GPIO, which allows for rapid movement system development without difficulties from sorting through pin enabling and permissions [Section 3.2.2.11, Pg 14]. It also allows for communication to be made through serial data with the PI and perform live, low-latency updates effectively. Many alternatives are available when choosing an MCU, but Arduinos are the standard selection and provide a comprehensive collection of documentation.
1. ### <a name="_toc112163469"></a>***Desktop Machine***
As a means to reduce the chances of system failures within the system, the point cloud generation will be performed by a high-powered desktop machine to alleviate the memory and computational requirement of the Raspberry PI. This is precautionary, as one of the main aims of this dissertation is to develop an autonomous driving system, and the risk of generating the maps on this system potentially crashing the driving logic would be detrimental to the system.




1. # <a name="_ref112108444"></a><a name="_ref112108448"></a><a name="_toc112163470"></a>**Design, Implementation and Testing**
This chapter aims to construct a design plan through the outcome of the literature review. Throughout this process, the choices made will be reflective of both the research and the requirements discovered for the system during chapter 2.
1. ## ` `**<a name="_ref112108013"></a><a name="_ref112108020"></a><a name="_toc112163471"></a>Design**
The need to imitate a vehicle is required due to vehicle costs and health and safety concerns [Section 3.2.2.6, Pg 13]. To achieve this, a platform with 5v motors will be used. This will allow space for the components to be placed while keeping a 4-wheel drive output (Figure 1). This does not reflect the steering of a modern vehicle (Ackerman steering) which uses an axel to shift the turning angle of the wheels. It instead can manually update the speed and direction of each motor individually, which will allow the platform to perform turning similarly to that of a car. The motor solution was chosen over the Ackerman steering due to its simplicity to avoid further impacts and time constraints for building the prototype. The motors are capable of mimicking the results of Ackerman steering.

![Diagram

Description automatically generated](Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.001.png)

<a name="_ref111639848"></a>*Figure 1 – Movement Platform Design*

With the platform and motion of the vehicle decided on, choosing the correct central computing device is the next step [Section 3.2.2.11, Pg 14]. After reviewing several low-cost IoT devices like ESP and MBED, it was decided to use a Raspberry Pi 2 because of its ability for code language freedom and feature of having an installed operating system and compatibility with low-cost LiDAR choices. This also allows for packages such are ROS and SLAM to be utilised for this project. 

![A picture containing rectangle

Description automatically generated](Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.002.png)

<a name="_ref112059674"></a>*Figure 2 - Logic Platform Design*

Several systems are required to ensure that the prototype will be capable of independent movement decisions (Figure 2). First, a communication method for the data to be accessible between multiple systems will be needed. ROS will be used due to its ability to facilitate communication between devices through the use of topics and nodes and the ease of access to documentation online [Section 3.4.3, Pg 16] and will facilitate the transport of LiDAR data live over a network to other devices. This allows independent devices to complete separate tasks with the captured data to produce different outputs. ROS also allows for serial communication between a Raspberry Pi and an Arduino to allow for live, low latency movement updates to be received and performed. For the software on the Raspberry Pi, a pre-loaded version of Ubuntu 16.04 with Kinetic ROS was used, which is supplied by Ubiquity Robotics (https://learn.ubiquityrobotics.com/kinetic\_pi\_image\_downloads). 

The Scan to Map technique creates a computational requirement for generating point cloud maps as the memory requirement increase for the map as well as the computation required to fit and update the scan to map. Ensuring that there is a system in place capable of completing this task is vital [Section 3.2.2.10, Pg 14]. Using ROS communication nodes allows for real-time topics and subscriptions communication between devices over a network, allowing for larger computational costing tasks such as the Scan to Map SLAM computations to be performed by capable hardware (Figure 3). This allows all the devices to work within their boundaries without impacting any other programs, further reducing the risk of crashes occurring in the prototype.

![](Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.003.png)

<a name="_ref112060240"></a>*Figure 3 - Prototype's ROS communication Architecture*

The use of an observation machine was used to handle this task. This is required due to the restrictiveness of the selected MCU (Arduino) and MPU (Raspberry Pi) boards, which have limited memory storage and processing power needed to perform other tasks for the prototype [Section 3.2.2.11, Pg 14]. By doing this, the rest of the system can manage the rest of the work without restrictions.

Ubuntu 16.04 was used for the observer machine as it is a requirement for kinetic ROS, following the instructions (http://wiki.ros.org/kinetic/Installation) supplied by ROS.org. The Raspberry Pi and the Observer machine must be set up and connected to the same network, with the ROS URI and IP addresses correctly set for communication.

A network scan for connected devices was performed to find the correct IP addresses for the devices. With the Master and Observers' IP addresses correctly found, the ROS\_MASTER\_URI variable was set to <http://192.168.0.27:11311> on both environments, being the IP of the Raspberry PI. The second variable, ROS\_IP, was set to its device's IP address, 192.168.0.27 for the master and 192.168.0.30 for the observer.

To avoid creating a overly large power draw on the raspberry pi, the motors of the prototype were powered by standalone 9-volt batteries. This alleviates the risk of placing too large of a demand on the Raspberry Pi's limited power supply, which will protect the Pi against power failures, allowing it to complete its tasks robustly without risk. As a further step to ensure the robustness of the raspberry pi, a low-resource, terminal-based Linux operating system can be installed and utilised to perform all the program running requirements for the prototype. This can be evaluated during testing to view the success rate of the prototype and monitor any failure that may occur.

Evaluating the measured accuracy of the scans is required, which will be done by comparing physical recordings to evaluate the accuracy that both the LiDAR and the produced map are capturing. Although LiDAR has a reputation for being accurate ranging sensors [Section 3.2.2.1, Pg 11], ensuring that the distances recorded are correct after being computed by the SLAM algorithm is a must. Securing the LiDAR to a level surface without obstruction will avoid possible false readings from the sensor. 

The system needs to perform in different lighting environments without affecting the results of the data captured to ensure that the prototype is robust enough to perform its tasks. As data capture is core to the whole system's performance, for both creating the point cloud maps and creating movement instructions, ensuring that the sensor is acceptable and reliable enough for this task is essential. 

When capturing the data and creating a point cloud map, the system needs to recognise that potential obstacles are changing in the environment and not allow these obstacles to affect the outcome of the map.

1. ## ` `**<a name="_ref112108040"></a><a name="_ref112108044"></a><a name="_toc112163472"></a>Implementation**

1. ### <a name="_ref112108110"></a><a name="_ref112108113"></a><a name="_toc112163473"></a>***Logic System***
During the Raspberry Pi setup, a knowledge gap was discovered due to the limited exposure to the hardware and ROS. Time was taken to complete tutorials to gain basic knowledge of setup, system features and multiple terminal executions. The operating system used for the Raspberry Pi was Ubuntu 16.04 due to the compatibility requirements for ROS Kinetic Kame. This ROS package was chosen due to the access to documentation and use in other example projects to help guide the learning process.

This framework facilitates a wide variety of packages for controlling a robot. It is designed to provide a relatively simple way to interface with a robot and allows developers to create custom packages for their specific projects. These packages typically range from path planning, mapping, motion control, localisation, SLAM, communication and more. By using RPLiDAR, the distributed package created by Robopeak is accessible for use for the prototype. This package allows for the creation of topic communication using nodes and listeners. Multiple devices can use the data captured by the LiDAR. This allows the Raspberry Pi to create movement decisions while offloading data to an observer machine to visualise the map being created using RVIXZ and allow the maps to be saved and viewed later.

An issue found during this process the understanding of the "Master" and "Worker" relationship between devices. This caused issues when configuring the address for both the remote computer and the prototype (Figure 3). 

When setting up ROS, the Master IP and the observer IP is required, which allows the devices to communicate with one another over a network directly. When setting this up, it was noticeable that the raspberry pi 2 was performing slowly, and after a review decided to change to a raspberry pi 4, which increased the memory of the device.

Now that the raspberry pi has all the software required to read the data stream from the LiDAR, a test can be performed to visualise this process by running the Robopeak test file called "view\_rplidar.launch".

![Graphical user interface

Description automatically generated](Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.004.png)

<a name="_ref111724366"></a><a name="_ref111724362"></a>*Figure 4 - Rviz visualistion of the LiDAR*

Rviz displays a live visualisation of the data being captured by the LiDAR through the laser\_frame topic (Figure 4). This allows for checks to be done to ensure that the sensor is clear of obstructions and is functioning as expected. This method does not save the history of the scans, which is a task that will be accomplished through Hector-SLAM to create point cloud maps. 

Hector-SLAM was installed using the repository at "github.com/tu-darmstadt-ros-pkg/hector\_slam". Once installed, the odom\_frame variable located in “~/catkin\_ws/src/hector\_slam/hector\_mapping/launch/mapping\_default.launch” needed to be changed to base\_footprint to follow the communication structure used by Robopeak. 

The system, at this point, can now create maps; this is done by running both the lidar.launch file, and the Hector-SLAM file in conjunction with one another. Data captured by the LiDAR is broadcasted over the ROS Node, which is then taken by Hector-Slam, which is listening for a topic for new posts. This data is then put through the Hector-Slam algorithm to estimate the data best fitting position on the map close to the localisation point.

![Graphical user interface, website

Description automatically generated](Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.005.jpeg)

<a name="_ref111724765"></a>*Figure 5 - Hector SLAM test map scan*

In a walk-around test with the logic platform, a scan of the environment was created by carrying the platform at chest height while slowly moving and turning around the room shown by the green line (Figure 5). With each scan, the readings taken by the LiDAR are checked against the map being created for its correct position close to the platform's current localisation point shown by the position marker. When a surface is detected that matches close to a point seen before on the map, edge points at these locations darken to black, creating a 2d environment with measurable distances.
1. ### <a name="_ref112108065"></a><a name="_ref112108069"></a><a name="_toc112163474"></a>***Movement System***
While purchasing the parts for the prototype, the total cost of components was higher than anticipated, which caused a slowdown in production. The first build of the prototype began with ensuring that the motors, motor controller and Arduino were all functional and working. When developing this, it was clear there was an issue with understanding how the motor controller works, which became more problematic as it came with no documentation when purchased. After much trial and error, the mentioned motor controllers were connected correctly, allowing testing to begin (Figure 6). 

![Diagram

Description automatically generated]

<a name="_ref111724949"></a>*Figure 6 - Wiring Diagram of Movement System*

A low-level application was created that used MQTT messages to update instructions to the Arduino and perform movement updates [Appendix 7.2.1]. This code listens for a new update to be delivered to the MQTT broker. When this happens, the message is stepped through each character using a switch statement to complete a movement instruction if the correct character is present. As a very low-level test, this showed that the movement system could perform movement updates. After further research was done, a functional prototype was created with changing motor speeds [Appendix 7.2.2]. 

1. ### <a name="_toc112163475"></a>***Combining the systems***

![Diagram

Description automatically generated]

*Figure 7 - Complete System Wiring Diagram*

While combining the movement and logic systems, a spacing issue became apparent for trying to fit all the components onto the platform. Keeping the LiDAR centred on the prototype for localisation is required. It was opted to move the Arduino onto the lower level to allow enough space for other vital components to fit correctly (Figure 1, Figure 2). This caused cabling issues due to the lack of access to short cables, which caused obstructions to the laser during testing. To ensure that the LiDAR can work correctly, ensuring that its field of view is not obstructed is a must otherwise, it will cause issues later with mapping and obstruction detection. With the lack of budgeting, strapping down the wires was the only alternative. However, weight was added with this, which began causing issues due to the motor strength. Minor changes were made to anything to reduce this issue, like rewiring and component placement to centre the weight and fairly distribute the work over the motors.

![A screenshot of a computer

Description automatically generated with medium confidence](Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.008.png)

<a name="_ref111725483"></a>*Figure 8 - Fast movement causing map mismatching*

With previous experiments completed while holding the logic platform (Figure 5), it was noticed that mismatching occurred when turning sharply (Figure 8). This was believed to be avoidable due to the movement methods utilised through ROS, allowing for softer curved turns to be completed [Section 3.2.2.3, Pg 11]. Unfortunately, this highlighted another issue with the prototype being the model's weight, which made it impossible for the prototype to complete slow turns as the torque produced by the motors when at low speed, cannot push the weight.

When testing the robot with different weights and code configurations of the wall follower sim (Shaoul, 2021) and the Arduino code that translates the instructions (Appendix 7.2.2), it was apparent that the performance of the motors is just too weak to move everything that is required for the prototype to work. Although the prototype correctly followed the movement instructions it sent, it could not move as designed. As a result, it was decided to perform the tests with only the logic system, as it was still possible to test and review of this system.

1. ## ` `**<a name="_ref112108208"></a><a name="_ref112108213"></a><a name="_toc112163476"></a>Testing**
A test was performed early in the prototype's development before adding a power supply battery for the Raspberry Pi. Autonomous visualisations were created in RVIZ to ensure that communication between the prototype and the remote machine was correctly set up. Communication was functioning, and a map could be created, but space was a concern due to limited space when testing the device, which resulted in the prototype driving in a circle. Testing was moved to the university, resulting in the addition of a power supply to the prototype to allow for testing in a larger controlled environment to ensure that it was performing as expected. Upon testing in a larger area, the issue of motors not turning at low speed became majorly apparent. However, the motors did not perform correctly after multiple iterations and configurations to allow for accurate scanning.

Being the case, the only way for the prototype to perform turns was to activate them at full power. This resulted in failures with the Hector-SLAM scan to map algorithm, which failed to provide an accurate map but produced clusters of unintelligible points (Figure 8). The prototype creates capable scans when removed from the motors and carried manually for scans, following the slow movement and turning speeds required for Hector-SLAM to work.

Alternatively, as it is impractical to test the movement of the prototype due to restrictions caused by the motors resulting in issues with the mapping software, it is possible to read the movement instructions that are being sent by the Teleop program. By listening to this communication, although a practical exercise cannot be completed with the movement system, the movement data can be evaluated to see if updates are being made and new movement instructions are being generated (Figure 9).

![](Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.009.png)

<a name="_ref111740531"></a>*Figure 9 - Movement updates left and Wall following program right*

|Instruction|Linear|Angular|Wall Following Output|
| :- | :- | :- | :- |
|1|<p>`  `x: 1.0</p><p>`  `y: 0.0</p><p>`  `z: 0.0</p>|<p>`  `x: 0.0</p><p>`  `y: 0.0</p><p>`  `z: -1.04\*</p>|<p>'ANGLE', -0.1372968393385167, 'DIST', 0.67519327541167162</p><p></p>|
|2|<p>`  `x: 1.0</p><p>`  `y: 0.0</p><p>`  `z: 0.0</p>|<p>`  `x: 0.0</p><p>`  `y: 0.0</p><p>`  `z: -0.83\*</p>|<p>'ANGLE', -0.031810464667146876, 'DIST', 0.80917777265838708</p><p></p>|
|3|<p>`  `x: 1.0</p><p>`  `y: 0.0</p><p>`  `z: 0.0</p>|<p>`  `x: 0.0</p><p>`  `y: 0.0</p><p>`  `z: -0.35\*</p>|<p>'ANGLE', 0.13210388166329692, 'DIST', 0.98435778214674607</p><p></p>|
|4|<p>`  `x: 1.0</p><p>`  `y: 0.0</p><p>`  `z: 0.0</p>|<p>`  `x: 0.0</p><p>`  `y: 0.0</p><p>`  `z: -0.48\*</p>|<p>'ANGLE', -0.014202741855553444, 'DIST', 1.1019902180984174</p><p></p>|
|5|<p>`  `x: 1.0</p><p>`  `y: 0.0</p><p>`  `z: 0.0</p>|<p>`  `x: 0.0</p><p>`  `y: 0.0</p><p>`  `z: -0.69\*</p>|<p>'ANGLE', -0.1636217714766259, 'DIST', 1.1163758885671948</p><p></p>|
|6|<p>`  `x: 1.0</p><p>`  `y: 0.0</p><p>`  `z: 0.0</p>|<p>`  `x: 0.0</p><p>`  `y: 0.0</p><p>`  `z: -0.88\*</p>|<p>'ANGLE', -0.2503085209078294, 'DIST', 1.0421565340841228</p><p></p>|
|7|<p>`  `x: 1.0</p><p>`  `y: 0.0</p><p>`  `z: 0.0</p>|<p>`  `x: 0.0</p><p>`  `y: 0.0</p><p>`  `z: -0.89\*</p>|<p>'ANGLE', -0.200269570013792, 'DIST', 0.90541217609222913</p><p></p>|
|8|<p>`  `x: 1.0</p><p>`  `y: 0.0</p><p>`  `z: 0.0</p>|<p>`  `x: 0.0</p><p>`  `y: 0.0</p><p>`  `z: -0.88\*</p>|<p>'ANGLE', -0.14803688943927026,</p><p>` `'DIST', 0.80145068638298589</p><p></p>|
|9|<p>`  `x: 1.0</p><p>`  `y: 0.0</p><p>`  `z: 0.0</p>|<p>`  `x: 0.0</p><p>`  `y: 0.0</p><p>`  `z: -0.96\*</p>|<p>('ANGLE', -0.16159144121350522, 'DIST', 0.74587104272039995</p><p></p>|
<a name="_ref111741237"></a><a name="_ref111908620"></a>*Table 1 - Movement Instructions compared to Wall Following Output*

This shows that new linear (linear x for forward and backward) and angular (angular z for left and right) instructions are being sent through the serial communication to the Arduino to change the motor's state (Figure 9, Table 1). Although this is not entirely functional due to the hardware drawbacks, this would work had more powerful motors been accessible for the prototype.

The programs and subsystems have worked without failure during the implementation or testing stages. The main reason for this is believed to be due to the correct distribution of workloads and ensuring that high power demanding parts of the system are supplied with individual power supplies. However, the shortcomings of the motors not being powerful enough to move the prototype are not an indicator of the system failing but showcasing their lack of torque to move the prototype at low speeds.

To evaluate the accuracy of the LiDAR, a scan of the university lounge room (Figure 10) and physical measurements were taken using a tape measure (Table 2).

![](Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.010.png)

<a name="_ref111741790"></a><a name="_ref112058132"></a>*Figure 10 - SLAM map measurements of points A, B and C are shown at the bottom*


|Points|Tape Measure Measurement|LiDAR Measurement|Measurement Error|
| - | - | - | - |
|A|3\.86m|3\.85m|0\.26%|
|B|1\.62m|1\.68m|3\.64%|
|C|2\.37m|2\.34m|1\.27%|

<a name="_ref111741813"></a><a name="_ref111908607"></a>*Table 2 - Measurements from tape measure and LiDAR*

The measures captured from the SLAM map are close to the measurements taken with the tape measure, with a maximum difference of 6cm. Due to the difficulties in matching the exact measured angle, starting and end point completed in the tape measure measurement to that measured in the Rviz map, this slight difference does not show inaccuracy in the LiDAR. This demonstrates that the distances captured in a complete map show a high level of accuracy after completion of the Hector-SLAM algorithm.

Computational offloading was accomplished using the ROS communication nodes, which allow for real-time topics and subscriptions between devices over a network. By doing this, the prototype logic system's workload is reduced by communicating LiDAR data over the node, filtering to only closed ranged readings, and translating this information into movement updates for the Arduino.

<a name="_ref111727623"></a>*Figure 11 - Single State Scan of Lounge Room with logic system centred on table*

![](Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.011.png)![](Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.012.png)

The system needs to perform in different lighting environments without affecting the results of the data captured to ensure that the prototype is robust enough to perform its tasks. As the data captured is the foundation for the whole system for both creating the point cloud maps and creating movement instructions, ensuring that the sensor is acceptable and reliable enough to be relied on for this task is essential. LiDAR, when tested in both a naturally lit room (Figure 11) and an artificially lit corridor (Figure 12), captured accurate data both environments.

![A picture containing text, indoor, wall, computer

Description automatically generated](Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.013.jpeg)

<a name="_ref111727678"></a>*Figure 12 - Single State Scan of Corridoor with logic system in hand*

![](Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.014.png)Maps were created in the same room with different lighting conditions (blinds open and closed). In both cases, the LiDAR produced accurate scans of the environment, highlighting obstructions on its visual plane (pillars, chairs, walls).

When tested in an environment with limited natural lighting, the logic system still functions well, showing ranging markers for everything within its field of view. This demonstrates that both the LiDAR and the logic system can perform their tasks functionally in different environments.

As seen in Figure 12, centred on the monitor are two people scanned by the LiDAR at the time of the scan. When moving the logic system, the scan data is updated on the screen to reflect the new environment. 



When completing the walk-around tests with the logic system on hand, although the LiDAR was giving readings that there was an obstruction (a person) close behind it, the map does not show any ghosting artefacts of this object being present. This is because the object is not static, and so the model does not build a high enough confidence to darken markings on the map to show an obstacle. 

For the movement system, a new move instruction is generated by each reading when the distance threshold is met with an object (Figure 9, Table 1). This means that if a moving obstacle were to move by the robot during a scan, the program would indicate something too close to the robot and update the movement instructions to avoid collision with it.







1. # <a name="_toc112163477"></a>**Evaluation and Conclusions**
This chapter will summarise the outcomes of the prototype's development and its testing results. It will also evaluate the personal development achieved throughout this dissertation, review the steps taken throughout this process, both positives and negatives, and potential future work.
1. ## ` `**<a name="_toc112163478"></a>An evaluation of the product.**  
Throughout the testing of the prototype, the system demonstrated a level of robustness as no issues occurred programmatically. When deployed, the logic system can perform its tasks by collecting data through the LiDAR sensors and distributing it to its correct locations for further work.

Tasks were split among devices to reduce the chances of failure by minimising the sizeable computational costing tasks on any specific device. The whole system would function on a single unit in a practical setting as mapping would not be required if only used as an obstruction detection system. 

During testing, the LiDAR's measurements showed reliable accuracy and could identify obstructions in each test (Figure 10, Table 2). Not only this, but the LiDAR was also capable of doing this in alternative lighting environments. The performance of the LiDAR did not appear to alter during these experiments and produced similar results. Because of this, the sensor could provide enough context of the prototype's surroundings to highlight potential obstacles, which could be filtered down, allowing for logical decisions to be completed, which provided responsive movement changes (Shaoul, 2021). Although mapping was offloaded to a higher-performing machine, the movement updates were all produced and executed on the Arduino and Raspberry Pi. This would indicate that the complexity of this system is low enough and responsive enough to detect an obstacle and effectively deliver a movement update to the driving system.

However, the issues discovered with the Hector-SLAM algorithm failing to correctly update the map and localisation of the robot due to high turning caused issues and delays in producing an acceptable prototype. Also, it is noted that due to the restriction caused by the limited amount of environmental context that the LiDAR can capture, its performance as a single sensor system for vehicles would prove poor on a vehicle system. Although, as a system to responsively detect hazardous obstructions and perform a movement update, testing has shown the system is capable of this. With this being the case, future work reviewing how LiDAR could increase the safety performance of vehicles in tangent to other sensors like cameras, ultrasonic and radar.

Although the system in its state does not entirely function as designed, the individual components have been tested. The movement system was primarily tested through the MQTT test to receive remote commands and execute movement instructions as per the messages. This enabled the system to be driven by a web server, internet control, or communications nodes, where commands could be sent from a controller.

The Logic system was tested and validated and is proficient in creating 2D positional maps that highlight obstacles and identify temporary obstacles while in motion. Not only was it able to detect the position of objects, but it could also detect the scale of the environment in which it was measuring and the distance between obstacles.

This satisfies one of the primary aims of this dissertation which was to "Build a prototype system that allows a vehicle to manoeuvre itself throughout an environment using LiDAR technology", and by proving that each of the individual components does work, a proof of concept can be established to address this aim. The prototype developed demonstrates a proof of concept, but to put this technology onto a real vehicle would require further study, as this prototype acts as a scaled-down system rather than that used for an actual vehicle. This means that the cost of the hardware, the scan frequency, size of the system, and alternative sensor synergy would all become require re-evaluation
1. ## <a name="_toc208295570"></a> **<a name="_toc112163479"></a>An evaluation of the project process.**  
Due to departmental restructuring, a Technical Extenuating Circumstance (TEC) was issued. The proposed project plan became increasingly challenging to follow, as not only did the project fall behind schedule, but the time selected for the plan was too short for completing the work being carried out to an acceptable level. Moreover, the change in supervision resulted in a directional shift in the project, which resulted in increased time pressures and deviations from the original ToR.

Due to the limited time given, it was highlighted early in the project that there was an issue of limited exposure to hardware and IoT devices, which resulted in a learning curve to attempt working through the requirements of this project. Because of this, all portions of the project took longer than expected to complete as more research was required, iterations of design choices and the difficulty involved in constructing the prototype. 

In hindsight, allocating more time to the more challenging work areas could have kept the project on track better. An earlier acquirement of the equipment required and changing some of the parts would have made the prototype perform closer to what was envisioned.

Early in development, potential AI methods to create movement instructions for the prototype were reviewed but deemed unnecessary for the task. This is because the exact outcome of an AI model can be produced using logical statements. The speed that both methods can predict the outcome would be similar, and the work required to gather the data and build a classification model would not be beneficial.

However, other objectives outlined in the ToR were addressed in the completion of this project. The ending prototype uses multiple IoT devices, including working with circuitry, independent programming languages and both serial and network communication architectures. With the prototype's robustness demonstrated, the IoT devices are systematically working as expected. This was possible due to reviewing other systems using similar hardware and continuous design development throughout the project. By combining all of this, it was possible to create a successful prototype with minor limitations caused by the motors, which allowed for experiments to review the system's accuracy while also evaluating the collision avoidance program. 

From the entire process, several skills have been acquired. Throughout the prototype's design and building, researching and reviewing similar works became one of the most critical steps. ROS was a previously unused operating system before this dissertation.

A greater understanding of power distribution was acquired, as well as the drawbacks of increasing battery capacity. To allow the system to work in a manner that allowed it to perform scans and movement on its own, ensuring that the raspberry pie had a significant enough power supply to keep the LiDAR scanning and the Arduino powered was crucial. Because of this already high demand for the Raspberry Pi, the motors required their power source. Trying to draw the voltage and current required for four motors from an already saturated circuit could cause under-power failings in the system. 

Although this facilitated all the system's power requirements, it harmed the prototype's ability to move. With the increased weight from the added power supplies, the motors come under too much weight to function correctly. This highlighted an issue within the electronic car industry, where upgrading battery capacity may not always prove beneficial to the vehicle as the increased weight could potentially reduce the vehicle's performance by adding extra work for the motors.

When controlling movement with robotic projects, ROS became an excellent tool for executing communication throughout the prototype to deliver data and instructions to their destinations. Working with communication nodes over the network and serial lines, controlling messages, and handling data and deploying multiple devices in unison without affecting the independent programs running was a new learning process. This also opened an understanding of how multiple different languages can communicate with one another when handled and sanitised correctly. Learning about localisation issues and implementing slam techniques to create accurate point cloud maps scan of environments was another skill acquired from this dissertation. 

Building this prototype was filled with failure and misunderstanding due to the lack of expertise in the area. Although this may seem negative, the lessons and skills acquired through the rigorous testing, experimenting and evolution of the prototype have proved to be more impactful on the understanding of this dissertation than potentially that which would have been if the prototype and project had functioned first time without fail.

Ethical and legal issues require addressing in regards to smart cars. A known conundrum in this area is the "trolley problem" and the evaluation of the outcome of an accident. An example of the trolley problem would be, 

"*If the vehicle were to detect a risk that could endanger the passengers of the vehicle, but the only alternative is for the vehicle to turn and endanger an alternative party, which option should be chosen*?"

This has been a long-debated question in computer science for several years with no ethically sound conclusion. Currently, legislation and regulations within smart assisted vehicles allow vehicles to function autonomously with the express supervision of the user, which also requires the user to keep their hands on the wheel. Although this legislation protects developers in this industry, it could potentially reduce the speed at which innovations are being made in this sector.

Another potential threat highlighted in the prototype is insecure network communication between the prototype and the observer computer. Although in this case, there is no handling method for the prototype to receive commands from the computer, meaning no man-in-the-middle attack could cause harm to the prototype's actions, as the final movement instructions are sent from the Raspberry Pi to the Arduino over serial communication. If there were commands that the prototype expects, it could be possible for someone to send malicious instructions to the device.

1. ## ` `**<a name="_toc112163480"></a>Conclusions**
This dissertation set out with the aims to research how autonomous systems for vehicles are used as well as their feasibility in safely mapping environments [Chapter 3.0, Pg 9]. Another aim is to build a prototype system that allows a vehicle to manoeuvre itself throughout an environment using LIDAR technology [Chapter 4.0, Pg 18]. 

Through the completion of researching, designing and testing the hardware, this dissertation can address the research questions of "*Are self-driving RC cars capable of mapping environments using LiDAR technology*?".

Before doing this, there was a need to explore the literature to understand the current state of knowledge and to identify critical technologies and the technological challenges involved in their use. This was achieved by reviewing relevant research [Section 3.2.1, Pg 9] to identify how similar work has been achieved to guide further research into technical areas that required further exploration [Section 3.2.2, Pg 11]. The outcomes of this assisted in identifying a clear development path through finding system requirements [Section 3.3.1, Pg 14] that helped formulate the methods used to produce a prototype for this dissertation.

In chapter 4, designs were constructed to create the system [Section 4.1, Pg 18], which allowed for the required positioning of critical components. This allowed for small test cases to be created during the implementation section [Section 4.2, Pg 21] to review the performance of both the movement and logic system before fitting the systems together. When carrying a light load, these tests showed that the movement system could receive movement instructions and perform movement updates [Section 4.2.2, Pg 23]. The logic system also demonstrated its ability to map environments and facilitate all the communication requirements for the system [Section 4.2.1, Pg 21].

Testing [Section 4.3, Pg 25] was conducted using the technologies identified from research [Section 3.2, Pg 9]. This demonstrated using LiDAR to identify obstructions and provide movement changes. LiDAR has shown its ability to capture accurate ranged data with less than 4% measurement error (Table 2), allowing a highly accurate map to be created using Hector-SLAM (Figure 10). As a result, the prototype can identify obstructions live while in motion and provide new movement updates to avoid said obstacles (Figure 9, Table 1). By performing this in real-time, it means that the prototype can perform mapping of an environment safely with a low risk of damage occurring to obstructions within its scan area.

This has practical implications for the future of self-driving car research. Methods used in this dissertation have proven the prototype to be more than adequate in safely and autonomously manoeuvre through an environment. Although a LiDAR solution inherently has limitations, looking into potential future work that could be completed to address this needs to be mentioned.
1. ## ` `**<a name="_toc112163481"></a>Recommendations**
Several recommendations should be considered when approaching this field of work again. This could include looking at the performance of these systems on a single unit system. When a general understanding of ROS is achieved, it would be beneficial to consider the possibility of using ROS 2. This would open new possibilities for the system as the system would no longer be restricted to Ubuntu operating systems. Also, ROS 2 utilises a higher development of the C++ language, providing access to new features in its API. 

Future work for this area could include using 3D LiDAR, which could allow for more significant obstacle detection by further increasing the field of view that the sensor would provide. Performing a similar exercise on a higher performing LiDAR that provides scans at a higher frequency could be reviewed against this work to evaluate if scaling up the hardware provides similar results. A review of alternative SLAM techniques with the same hardware could be worth researching to evaluate which are the most performing. A comparative study could be conducted to investigate the performance of LiDAR working with alternative sensors such as cameras and radar.


1. # <a name="_toc112163482"></a>**References**

Azzam, R. *et al.* (2020) ‘Feature-based visual simultaneous localization and mapping: a survey’, *SN Applied Sciences*, 2(2). doi: 10.1007/s42452-020-2001-3.

Beer, M. *et al.* (2018) ‘Background light rejection in SPAD-based LiDAR sensors by adaptive photon coincidence detection’, *Sensors (Switzerland)*, 18(12). doi: 10.3390/s18124338.

Berlia, R. and Santosh, P. (2014) ‘Mouse brace: A convenient computer mouse using accelerometer, flex sensors and microcontroller’, *Proceedings of 2014 International Conference on Contemporary Computing and Informatics, IC3I 2014*. IEEE, pp. 558–561. doi: 10.1109/IC3I.2014.7019684.

Carullo, A. and Parvis, M. (2001) ‘An ultrasonic sensor for distance measurement in automotive applications’, *IEEE Sensors Journal*, 1(2), pp. 143–147. doi: 10.1109/JSEN.2001.936931.

Chatila, R. and Laumond, J. P. (1985) ‘Position referencing and consistent world modeling for mobile robots’, *Proceedings - IEEE International Conference on Robotics and Automation*, pp. 138–145. doi: 10.1109/ROBOT.1985.1087373.

Coulby, G. *et al.* (2020) ‘Towards remote healthcare monitoring using accessible IoT technology: state-of-the-art, insights and experimental design’, *BioMedical Engineering Online*. BioMed Central Ltd, 19(1), pp. 1–24. doi: 10.1186/S12938-020-00825-9/TABLES/4.

Debeunne, C. and Vivet, D. (2020) ‘A review of visual-lidar fusion based simultaneous localization and mapping’, *Sensors (Switzerland)*, 20(7). doi: 10.3390/s20072068.

Domínguez, R. *et al.* (2011) ‘LIDAR based perception solution for autonomous vehicles’, *International Conference on Intelligent Systems Design and Applications, ISDA*, (November), pp. 790–795. doi: 10.1109/ISDA.2011.6121753.

Francis-Mezger, P. and Weaver, V. M. (2018) ‘A raspberry pi operating system for exploring advanced memory system concepts’, *ACM International Conference Proceeding Series*. doi: 10.1145/3240302.3240311.

Gaillard, F. and Eieland, A. (2013) ‘Microprocessor ( MPU ) or Microcontroller ( MCU )? What factors should you consider when selecting the right processing device for your next design’, pp. 1–4.

Gatesichapakorn, S., Takamatsu, J. and Ruchanurucks, M. (2019) ‘ROS based Autonomous Mobile Robot Navigation using 2D LiDAR and RGB-D Camera’, *2019 1st International Symposium on Instrumentation, Control, Artificial Intelligence, and Robotics, ICA-SYMP 2019*. IEEE, pp. 151–154. doi: 10.1109/ICA-SYMP.2019.8645984.

Grilli, E., Menna, F. and Remondino, F. (2017) ‘A review of point clouds segmentation and classification algorithms’, *International Archives of the Photogrammetry, Remote Sensing and Spatial Information Sciences - ISPRS Archives*, 42(2W3), pp. 339–344. doi: 10.5194/isprs-archives-XLII-2-W3-339-2017.

Gul, F., Rahiman, W. and Nazli Alhady, S. S. (2019) ‘A comprehensive study for robot navigation techniques’, *Cogent Engineering*. Cogent, 6(1). doi: 10.1080/23311916.2019.1632046.

Harik, E. H. C. and Korsaeth, A. (2018) ‘Combining hector SLAM and artificial potential field for autonomous navigation inside a greenhouse’, *Robotics*, 7(2). doi: 10.3390/robotics7020022.

Haylock, S. and Tranter, M. (2021) *Reported road casualties in Great Britain: provisional estimates year ending June 2020*, *Department of Transport*. Available at: https://www. (Accessed: 27 October 2021).

Hess, W. *et al.* (2016) ‘Real-time loop closure in 2D LIDAR SLAM’, *Proceedings - IEEE International Conference on Robotics and Automation*, 2016-June, pp. 1271–1278. doi: 10.1109/ICRA.2016.7487258.

Hutabarat, D. *et al.* (2019) ‘Lidar-based obstacle avoidance for the autonomous mobile robot’, *Proceedings of 2019 International Conference on Information and Communication Technology and Systems, ICTS 2019*. IEEE, (October), pp. 197–202. doi: 10.1109/ICTS.2019.8850952.

Kato, S. *et al.* (2015) ‘An open approach to autonomous vehicles’, *IEEE Micro*, 35(6), pp. 60–68. doi: 10.1109/MM.2015.133.

Kohlbrecher, S. *et al.* (2014) ‘RoboCupRescue 2014 - Robot League Team’, (1).

Kohli, P. and Chadha, A. (2020) ‘Enabling pedestrian safety using computer vision techniques: A case study of the 2018 uber inc. self-driving car crash’, *Lecture Notes in Networks and Systems*, 69, pp. 261–279. doi: 10.1007/978-3-030-12388-8_19.

Leberl, F., Irschara, A. and Pock, T. (2010) ‘Point cloud: Lidar vs 3D vision’, *Photogrammetric Engineering & Remote Sensing*, 76(10), pp. 1123–1134. Available at: https://doi.org/10.14358/PERS.76.10.1123.

Li, G. *et al.* (2018) ‘Detection of Cars in Mobile Lidar Point Clouds’, *2018 3rd IEEE International Conference on Intelligent Transportation Engineering, ICITE 2018*, pp. 259–263. doi: 10.1109/ICITE.2018.8492695.

Li, Y. (2013) ‘Stereo vision and LIDAR based Dynamic Occupancy Grid mapping : Application to scenes analysis for Intelligent Vehicles’. Available at: https://tel.archives-ouvertes.fr/tel-00982325 (Accessed: 16 February 2022).

Li, Y. and Ibanez-Guzman, J. (2020) ‘Lidar for Autonomous Driving: The Principles, Challenges, and Trends for Automotive Lidar and Perception Systems’, *IEEE Signal Processing Magazine*, 37(4), pp. 50–61. doi: 10.1109/MSP.2020.2973615.

Liu, Z., Zhang, F. and Hong, X. (2022) ‘Low-Cost Retina-Like Robotic Lidars Based on Incommensurable Scanning’, *IEEE/ASME Transactions on Mechatronics*, 27(1), pp. 58–68. doi: 10.1109/TMECH.2021.3058173.

Loyse, G. (2017) ‘Raspberry-Pi Documentation’.

Malavazi, F. B. P. *et al.* (2018) ‘LiDAR-only based navigation algorithm for an autonomous agricultural robot’, *Computers and Electronics in Agriculture*, 154, pp. 71–79. doi: 10.1016/j.compag.2018.08.034.

Marr, B. (2019) *7 Amazing Examples Of Computer And Machine Vision In Practice*, *Forbes*. Available at: https://www.forbes.com/sites/bernardmarr/2019/04/08/7-amazing-examples-of-computer-and-machine-vision-in-practice/?sh=7aab18301018 (Accessed: 27 October 2021).

Menze, M. and Geiger, A. (2015) ‘Object scene flow for autonomous vehicles’, *Proceedings of the IEEE Computer Society Conference on Computer Vision and Pattern Recognition*, 07-12-June, pp. 3061–3070. doi: 10.1109/CVPR.2015.7298925.

Miguel, N. *et al.* (2016) ‘Tesla Autopilot : Semi Autonomous Driving, an Uptick for Future Autonomy’, *International Research Journal of Engineering and Technology*. Available at: www.irjet.net (Accessed: 27 October 2021).

mqtt-v5.0 (2019) ‘MQTT Version 5.0’, *Oasis-Open*, (March), p. 137. Available at: https://docs.oasis-open.org/mqtt/mqtt/v5.0/mqtt-v5.0.html (Accessed: 25 October 2021).

Mur-Artal, R., Montiel, J. M. M. and Tardos, J. D. (2015) ‘ORB-SLAM: A Versatile and Accurate Monocular SLAM System’, *IEEE Transactions on Robotics*, 31(5), pp. 1147–1163. doi: 10.1109/TRO.2015.2463671.

Mur-Artal, R. and Tardós, J. D. (2014) ‘Fast relocalisation and loop closing in keyframe-based SLAM’, *Proceedings - IEEE International Conference on Robotics and Automation*, pp. 846–853. doi: 10.1109/ICRA.2014.6906953.

Olalekan, A. F. *et al.* (2021) ‘Comparison of two SLAM algorithms provided by ROS (Robot Operating System)’, *2021 2nd International Conference for Emerging Technology, INCET 2021*, (June). doi: 10.1109/INCET51464.2021.9456164.

Pazhayampallil, J. and Kuan, K. Y. (2013) ‘Deep Learning Lane Detection for Autonomous Vehicle Localization’, pp. 1–5.

Rivai, M., Hutabarat, D. and Jauhar Nafis, Z. M. (2020) ‘2D mapping using omni-directional mobile robot equipped with LiDAR’, *Telkomnika (Telecommunication Computing Electronics and Control)*, 18(3), pp. 1467–1474. doi: 10.12928/TELKOMNIKA.v18i3.14872.

Ruckert, E. A. (2009) ‘Simultaneous localisation and mapping for mobile robots with recent sensor technologies’, (December).

Shaoul, Y. (2021) *wall_follower_sim*, *Github*. Available at: https://github.com/yoraish/lidar_bot/tree/wall-follow-example/src/ros/wall_follower_sim/src.

Shashua, A. (2018) *Experience Counts, Particularly in Safety-Critical Areas | Intel Newsroom*. Available at: https://newsroom.intel.com/editorials/experience-counts-particularly-safety-critical-areas/ (Accessed: 27 October 2021).

Thakur, R. (2016) ‘Scanning LIDAR in advanced driver assistance systems and beyond’, *IEEE Consumer Electronics Magazine*. IEEE, 5(3), pp. 48–54. doi: 10.1109/MCE.2016.2556878.

U.S. government (2020) *GPS.gov: New Civil Signals*, *U.S. government*. Available at: https://www.gps.gov/systems/gps/modernization/civilsignals/#L5 (Accessed: 1 March 2022).

Vishalakshi, G. R., Gopalakrishna, M. T. and Hanumantharaju, M. C. (2016) ‘Comprehensive review of video enhancement algorithms for low lighting conditions’, *Advances in Intelligent Systems and Computing*, 435(February 2016), pp. 475–485. doi: 10.1007/978-81-322-2757-1_47.

Wunderlich, J. T. (1999) ‘Session 3547 Focusing on the Blurry Distinction between Microprocessors and Microcontrollers’, *American Society for Engineering Education Annual Conference & Exposition*.

Yang, M. Y. and Förstner, W. (2010) ‘Plane Detection in Point Cloud Data’, *Proceedings of the 2nd International Conference on Machine Control Guidance Bonn*, (1), pp. 95–104.

Zhang, Z. *et al.* (2019) ‘Rotation Invariant Convolutions for 3D Point Clouds Deep Learning’, *Proceedings - 2019 International Conference on 3D Vision, 3DV 2019*, pp. 204–213. doi: 10.1109/3DV.2019.00031.

Zhen, W. *et al.* (2019) ‘A Joint Optimization Approach of LiDAR-Camera Fusion for Accurate Dense 3-D Reconstructions’, *IEEE Robotics and Automation Letters*, 4(4), pp. 3585–3592. doi: 10.1109/LRA.2019.2928261.




1. # <a name="_toc112163483"></a>**Appendices**
   1. ## <a name="_toc112163484"></a>**Terms of Reference**



KV6003: Individual Computing Project





















Project Terms of Reference

John Robson, W19036980, Comp Sci with Artificial Intelligence

Self-Driving RC Car using Lidar Technology to Map Environments 

Supervisor: Martin Wonder 	2<sup>nd</sup> Marker: Fouad Khelifi

Project type: General Computing Project
### <a name="_toc112163485"></a>***Self-Driving RC Car using Lidar Technology to Map Environments*** 

Computer vision (CV) is a required step in providing a step for artificial intelligence to improve and allow machines to accurately analyse and make decisions in situations a lot like humans (Marr, 2019). CV is being used in facial recognition systems, healthcare, agriculture and autonomous vehicles to name a few.

A lot of work has been completed on CV to assist in automating the process of driving vehicles, through the use of Light Detection and Ranging (LIDAR) sensor, Ultrasonic sound wave sensors and video camera to create different obstruction detecting systems for motor vehicles. Tesla uses these sensors together to deliver a safe and practical model to protect against the drawbacks each other have (Miguel *et al.*, 2016). When weather conditions worsen for example low lighting, fog and heavy rainfall these systems performances can become worse and struggle to perform accurately (Vishalakshi, Gopalakrishna and Hanumantharaju, 2016) which could lead to accidents occurring. 

A fatal accident occurred in 2018 with a Uber Self-driving vehicle colliding with a pedestrian. Kohli and Chadha (2020) explain their reason for this accident is believed to be due to low lighting problem, with further studies being performed by Intel which showed their "MobileEye" system itself was only able to detect the pedestrian in the dashcam footage 1 second before the accident happened (Shashua, 2018). 

Sensors that could be used beneficially to improve autonomous vehicles vision in low lighting conditions could be LIDAR sensors. A technical problem found with LIDAR is its ability to detect obstacle perceptions and perform tracking while travelling at speed as the point cloud being generated is continuously mutating (Domínguez *et al.*, 2011). 

Kato *et al.* (Kato *et al.*, 2015) explain that autonomous vehicles are comprised of diverse technologies which require the collaboration of multiple disciplines in their research and development. By using the dataflow framework proposed by Kato *et al*. we can look at developing a method for the rover to continue travelling without the need for human input.

As a means to deliver instructions to a car MQTT provides several advantages as of its low bandwidth communications, simplicity and usability in constrained environments allowing communications between Internet of Thing systems (MQTT-v5.0, 2019). Not only this but the messages delivered through MQTT when sent to the car can be queued for executions.

During 2019-2020 there were a total of 1,580 road deaths that occurred with 24,470 people being killed or seriously injured (Haylock and Tranter, 2021). Road traffic accidents are an issue that I believe can be addressed with the use of self-driving or even assisted driving systems to provide road users with a safer choice when driving on roads. Computer vision and autonomous systems are of interest to me, and as a probable future in technology, I want to expand my skills in these fields for future work or research.
### <a name="_toc112163486"></a>***Proposed Work***
This paper will demonstrate the performance of lost costing LIDAR, micro control units (MCU) and micro processing units (MPU) technologies to generate autonomously mapped environments. Developing a model that provides an accurate collision avoidance system. By developing this mapped environment, it may be possible to create pathing algorithms to find the fastest paths out of the environment. Once a system is created an experiment will be performed by presenting obstructions to a moving car and reviewing how the LIDAR detects the obstructions and the accuracy of the mapped models.
### <a name="_toc112163487"></a>***Aims and Objectives***
#### <a name="_toc112163488"></a>***Aims***
1. To research how autonomous systems for vehicles are used and their feasibility of safely mapping environments.
1. To build a prototype system that allows a vehicle to manoeuvre itself to destinations using LIDAR technology.
#### <a name="_toc112163489"></a>***Objectives***
1. Conduct a literature review surrounding autonomous vehicles identifying their methodology and design choices.
1. Develop new skills within the internet of things, computer vision.
1. Creating design for the vehicle and program system being developed.
1. Create the prototype.
1. Experimental work on the system to ensure it is performing as per the design stage.
1. Evaluation of the project, literature review and systems used in the project.
1. Conclusion of the accuracy and success of the prototype and recommendations that could be investigated in the future.
### <a name="_toc112163490"></a>***Skills***
#### <a name="_toc112163491"></a>***KF5042 Intelligent systems***
- Principal Component Analysis
- Viola-Jones Object Detection Algorithm
- Random Forest
- K-Neural Networks
- Regression and Classification
- Data Transformation
- Model Deployment
#### <a name="_toc112163492"></a>***KF6052 Machine Learning and Computer Vision***
- Artificial Neural Networks
- Linear and Non-Linear Classification and Regressions
- SVM and BPNN 
- Image Transformations
- Convolutional Neural Networks
#### <a name="_toc112163493"></a>***KV6006 Internet of Things***
- MQTT
- Azure Services
- C++
- Arduino
- Data Collections
- API
#### <a name="_toc112163494"></a>***KF5012 Software Engineering Practice***
- Python
- Tensorflow
- Image Processing
- Data Transformation
- Algorithm Comparisons
### <a name="_toc112163495"></a>***Sources of information/bibliography***

### <a name="_toc112163496"></a>***Resources – statement of hardware/software required***
Car

- x4 5v motors
- x1 Motor controller
- x1 Breadboard
- 2D LIDAR

For processing data

- A desktop computer
- A low costing MCU/MPU

Software

- C++
- TensorFlow
- Python
### <a name="_toc112163497"></a>***Assessment Criteria***
Project Type:

- Report (50%)
- Product (40%)
- Viva (10%)
- Total (100%)

Project Report:

- Introduction (10%)
- Literature Review (30%)
- Implementation (30%)
- Evaluation (15%)
- Conclusion (15%)
- Total (100%)

Product:

- Fit for purpose (40%)
- Build Quality (60%)
- Total (100%)

|**Task**|**Start Date**|**End Date**|**Duration**||||||||||||||||||||||||||||
| - | -: | -: | -: | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- | :- |
|1 Literature Review of current methods|22/11/2021|06/12/2021|14||||||||||||||||||||||||||||
|2 Skill Developing using methods collected from lit review|07/12/2021|21/12/2021|14||||||||||||||||||||||||||||
|3 Create design for vehicle and detection system|22/12/2021|05/01/2022|14||||||||||||||||||||||||||||
|4 Create the prototype |06/01/2022|20/01/2022|14||||||||||||||||||||||||||||
|5 Experiment with the different sensors to review performances|21/01/2022|28/01/2022|7||||||||||||||||||||||||||||
|6 Evaluation of work completed|29/01/2022|06/02/2022|8||||||||||||||||||||||||||||
|7 Conclusion|07/02/2022|14/02/2022|7||||||||||||||||||||||||||||
|8 Complete Write-up|15/02/2022|28/03/2022|41||||||||||||||||||||||||||||
||||||||||||||||||||||||||||||||

|Weeks|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15|16|17|18|
| - | -: | -: | -: | -: | -: | -: | -: | -: | -: | -: | -: | -: | -: | -: | -: | -: | -: | -: |
|1| | | | | | | | | | | | | | | | | | |
|2| | | | | | | | | | | | | | | | | | |
|3| | | | | | | | | | | | | | | | | | |
|4| | | | | | | | | | | | | | | | | | |
|5| | | | | | | | | | | | | | | | | | |
|6| | | | | | | | | | | | | | | | | | |
|7| | | | | | | | | | | | | | | | | | |
|8| | | | | | | | | | | | | | | | | | |

||||||||||||||||||||||||||||||||
| - | - | -: | -: | -: | -: | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | - | :- | :- | :- | :- | :- |


1. ## <a name="_toc112163498"></a>**Other appendices**

1. ### <a name="_ref111821701"></a><a name="_toc112163499"></a>***Arduino Code for MQTT Instructions***
https://github.com/iamloxton/AurdinoCode/blob/main/car\_code\_with\_mqtt\_broker.ino

1. ### <a name="_ref111820969"></a><a name="_toc112163500"></a>***Arduino Code for Variable Wheel Speed***
https://github.com/iamloxton/AurdinoCode/blob/main/car\_code\_with\_wheel\_speed.ino






[Diagram

Description automatically generated]: Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.006.png
[Diagram

Description automatically generated]: Aspose.Words.0e074a89-19e6-46ef-bd33-3bb566e5d394.007.png
