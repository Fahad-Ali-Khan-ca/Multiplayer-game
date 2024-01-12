<a name="_89zxdbqnx28j"></a>Seh500 - Project: Interactive Game 


# <a name="_4kesz80tva7"></a><a name="_bkvo3hzfgguq"></a><a name="_sa26h4uhpwi5"></a>Introduction
In the rapidly evolving landscape of technology, interactive gaming experiences have become a cornerstone of entertainment and education. Embedded systems, characterised by their dedicated functions within larger electronic systems, are increasingly used to create engaging and interactive games. However, despite their widespread application, many games developed on these platforms are often limited by basic interactivity and simplistic mechanics, offering a narrow scope of user engagement. This report addresses the need to enhance the gaming experience on embedded systems, focusing on developing a game that entertains, challenges, and uniquely engages users.

Our project centres on developing an interactive game utilising the MK66F18 microcontroller, a robust platform known for its versatile features and capabilities. This game is designed to break the monotony of traditional embedded games by incorporating advanced features such as dynamic LED patterns, reaction-time-based scoring, and user input handling, which collectively elevate the user experience. The game operates in a multi-faceted environment, offering single-player and multiplayer modes, catering to a wider audience with varied preferences.

This project aims not merely to create another embedded system game but to push the boundaries of what is conventionally achievable in such compact systems. By leveraging the intricate functionalities of the MK66F18 microcontroller, including its SysTick timer for precise timing control, GPIO for interactive LED displays, and UART for efficient input handling, we have developed a game that stands out in its ability to engage users in a more immersive and interactive manner. This report delves into the journey of developing this game, exploring the challenges encountered, solutions implemented, and future enhancements that could further revolutionise gaming experiences in embedded systems.









<a name="_fpm3dm337l4h"></a>Background Research

<a name="_xky0zruy0ty6"></a>**Existing Solutions in Embedded Gaming**

Embedded gaming, a field combining entertainment with the compact power of embedded systems, has seen a variety of solutions over the years. Traditional embedded games, often found in handheld devices or as part of larger systems like home appliances, have typically been limited by the hardware constraints of these platforms. Classic examples include simple LED-based games or basic graphical games on small LCDs, often programmed in low-level languages to optimise resource usage.

Popular games in this category often revolve around puzzle-solving, reaction-based challenges, or adaptations of classic games like 'Snake' or 'Tetris.' These games, while entertaining, usually offer limited interactivity, relying on pre-set patterns or basic input mechanisms.

**Limitations of Current Solutions**

One primary limitation of embedded games is their simplistic interaction model. Many rely solely on fundamental LED indicators or rudimentary graphical interfaces, leading to a passive user experience. The hardware limitations often result in a lack of dynamic content, which is crucial for maintaining user engagement.

Additionally, the majority of these games need more scalability or adaptability. They are designed with a fixed set of rules and interactions, offering little in the way of personalised or varying gameplay. This limitation stems partly from the traditional approach to embedded system design, which prioritises functionality and efficiency over user experience.

**Comparative Analysis with Modern Gaming Trends**

Contrasting these embedded games with modern gaming trends highlights a significant gap. Modern games, even mobile or casual ones, offer rich, dynamic content with high levels of interactivity. They adapt to real-time user inputs and often include complex graphical and auditory feedback mechanisms.

While it's understood that embedded systems have inherent constraints, there is an emerging trend to push these boundaries. With advancements in microcontroller technology, there's a growing potential to enhance embedded gaming experiences, making them more interactive, engaging, and reflective of modern gaming standards.






<a name="_fxkjhvtemnka"></a>Proposed Solution

<a name="_hyrsl5qzqwjo"></a>**Overview of the Solution**

The proposed solution is an interactive game developed on the MK66F18 microcontroller, a powerful and versatile platform ideal for embedded system applications. This game is designed to enhance user engagement through its interactive elements and challenging gameplay. It offers a novel approach to gaming in embedded systems by incorporating dynamic visual elements and real-time user interactions.

The game operates in two modes: single-player and multiplayer, allowing users to compete against the system or engage in a competitive experience with another player. The core of the game revolves around reaction time. Players are challenged to respond to visual cues (LED patterns) as quickly as possible. The quicker the response, the higher the score achieved. This simple yet engaging concept tests and improves the players' reflexes and cognitive abilities.

**Technical Details**

- LED Display: The game employs an LED display system using the microcontroller's GPIO (General-Purpose Input/Output) ports. Different coloured LEDs create varying patterns, serving as visual stimuli for the players. The patterns change randomly, ensuring that each round of the game is unique and unpredictable.

- Scoring Mechanism: The scoring is based on the players' reaction times. For multiplayer mode, a point is awarded to whoever presses the button first, and their reaction time is printed; there are five rounds. For the single-player mode, you must press the button within one second of the light blinking, or else you won’t get the point. This mode also has five rounds.

This system makes the game competitive and provides a metric for players to track their improvement over time.

- User Input: Players interact with the game using buttons in the microcontroller. The game detects button presses in real-time, thanks to the efficient handling of interrupts and the utilisation of the UART (Universal Asynchronous Receiver/Transmitter) module for input processing.

- Custom Delay Function: The custom assembly-coded delay function is a significant solution feature. This function is crucial for controlling the timing of LED patterns and ensuring a synchronised and smooth gaming experience. It utilises a pseudo-random number generator (PRNG) for variability and unpredictability in the game’s flow.


<a name="_53u34kgz9fyr"></a>Solution Benefits and Concept Validation

<a name="_lmj3t6j2n6kp"></a>**Improvements Over Existing Solutions**

The interactive game developed on the MK66F18 microcontroller significantly advances traditional embedded gaming solutions. The primary benefit lies in its enhanced interactivity and engagement. By incorporating dynamic LED patterns and a reaction-time-based scoring system, the game introduces an element of excitement and challenge that is often missing in conventional embedded games. This approach makes the game more enjoyable and mentally stimulating, as it encourages quick thinking and reflexive responses.

Furthermore, the dual-mode functionality (single-player and multiplayer) broadens the game's appeal, making it suitable for a wider range of users with different preferences. This flexibility is a step up from the one-size-fits-all model prevalent in many existing embedded games.

Another significant improvement is the use of custom assembly-coded functions for delays. This demonstrates a deeper understanding of the microcontroller's capabilities and allows for more precise control over the game mechanics, leading to a smoother and more responsive gaming experience.

**Concept Validation**

The solution's effectiveness was tested through iterative development and testing phases. Initial prototypes were evaluated for response time accuracy and user interface intuitiveness. Subsequent refinements were made based on user feedback, focusing on improving input handling reliability and the diversity of LED patterns.

The game was also subjected to performance testing, ensuring it remained stable and responsive under different conditions. The scoring system was calibrated to ensure fairness and give players a meaningful challenge.

User trials played a crucial role in validating the concept. Feedback from a diverse group of test users confirmed that the game was more engaging and challenging than traditional embedded system games. Users particularly appreciated the real-time interaction and the competitive element introduced by the scoring system.

**Validation Outcomes**

The validation process demonstrated that the proposed solution successfully addressed the identified gaps in embedded gaming. It showed that creative use of available resources could lead to a significantly enhanced user experience even with hardware limitations. The project also validated the concept that integrating simple yet effective design elements, like LED patterns and reaction-time scoring, could transform the dynamics of an embedded system game.


<a name="_ic8sf65105u8"></a>Development Process and Challenges

<a name="_8e323x1kzrd4"></a>**Solution Development**

The journey to develop this interactive game on the MK66F18 microcontroller was challenging and enlightening, involving a blend of creative problem-solving and technical prowess. The development process began with a clear objective: to create a functional but also engaging and responsive embedded game.

Initially, the focus was on understanding the capabilities and limitations of the MK66F18 microcontroller. This involved exploring its GPIO (General-Purpose Input/Output) capabilities for LED control, its UART (Universal Asynchronous Receiver/Transmitter) module for handling user input, and its SysTick timer for managing time-sensitive operations. The development process was iterative, with each prototype bringing new insights and opportunities for refinement.

**Challenges and Solutions**

One of the primary challenges faced was optimising the game's responsiveness. There was a noticeable lag between user input and the game's reaction in early prototypes. To address this, we delved deeper into interrupt handling and real-time processing, significantly improving the game's responsiveness.

Another challenge was creating dynamic and unpredictable game patterns. This was crucial for maintaining user interest and ensuring the game offered a fresh experience with each play. The solution was a custom assembly-coded delay function, which used a pseudo-random number generator (PRNG) to create varied LED patterns. This enhanced the game's appeal and showcased the ability to integrate low-level programming techniques in embedded systems.

The most daunting challenge, however, was balancing complexity with system resources. Embedding sophisticated game mechanics without overwhelming the microcontroller’s limited processing power required careful planning and optimisation. This was achieved through efficient code structuring and judicious use of the microcontroller's features.

**Overcoming Obstacles**

Each obstacle encountered during development provided valuable lessons in embedded system design. Whether optimising for speed, developing custom algorithms, or refining user interfaces, each challenge pushed the boundaries of what was achievable within the constraints of an embedded system.





<a name="_mtx4nsnvo1e4"></a>Future Work

<a name="_ixpmt7gb4hok"></a>**Enhancing Game Features**

The current version of the interactive game on the MK66F18 microcontroller opens avenues for numerous enhancements. Future work could focus on introducing more complex game levels and patterns, adapting the difficulty based on the player's performance. This adaptive difficulty system would maintain player engagement and offer a personalised gaming experience.

**Integrating Advanced Graphics and Audio**   

While the current game primarily utilises LED patterns for user interaction, there is potential for integrating more advanced graphical displays or even audio feedback. Incorporating an OLED or LCD screen could bring a new dimension to the game, offering richer visual feedback and more intricate game mechanics. Similarly, adding sound effects or musical elements in response to player actions could create a more immersive experience.

**Connectivity and Data Analytics**

Another exciting direction for future development is integrating connectivity features, such as Bluetooth or Wi-Fi modules, to enable data sharing or multiplayer gaming over a network. This could open up possibilities for competitive play, global leaderboards, and community engagement. Additionally, data analytics could be used to track player progress over time, providing insights into player behaviour and preferences.

**Power Optimization and Portability**

Improving the game's power efficiency would be crucial for its adaptability in portable or battery-powered scenarios. Optimising the code for lower power consumption and exploring power-saving modes of the microcontroller could extend the game's usability in various environments.

**Educational Applications**

The game has potential applications in educational settings as well. It can be used to teach programming and embedded system design concepts. Future work could involve developing a customisable game version that allows users to modify or create their game patterns, fostering a deeper understanding of embedded programming.

**Broader Implications**

The techniques and concepts developed in this project have broader implications beyond gaming. The skills in efficient resource management, real-time processing, and user interface design are applicable in various fields of embedded system applications, from IoT devices to industrial control systems.


<a name="_59vpof6burk4"></a>References

<a name="_w9k33dc96cwd"></a>For PRNG:<https://stackoverflow.com/questions/90184/pseudorandom-generator-in-assembly-language>

<https://wiki.osdev.org/Random_Number_Generator>

userinput:<https://www.tutorialspoint.com/c_standard_library/c_function_getchar.htm>

Ideas for Project: <https://all3dp.com/2/easy-simple-arduino-projects/>

