# client-serve-BMI
IMPLEMENT A CLIENT-SERVER SYSTEM COMPONENT TO HANDLE UDP/TCP COMMUNICATIONS. 


System that I have That I have developed is about client and server application which measure the BMI for clients , clients enter there height and weight to the server and ,the server calculates the Body Mass Index (BMI) and sends it back to the client , when there sever finishes calculating it prints the result in a file , and all that process is done by the help of socket communication and multi-threading to handle multiple client connections. 
Let's summarize the improvements made and how they positively affect efficiency and execution time:
•	Multi-Threading:
 this was the biggest improvements in the code it was the use of threading, so make us able to handle more than one clint at once , so instead giving each client a new process and new memory location and this might consume a lot of system resources  , threads allow multiple clients to be handled within a single process, so what I have gained after this improvement this allowed me to reduce the overhead and that leads to better consuming the system resources so the effectiveness of this adds is the grant an effective way for data is shares in a effective process  , and also by using the socket connection this can be useful .
•	Logging:
 all the clients who have used my BMI calculator , there logs was saved in an output fill called "bmi_results.txt." , so by the use of this feature I am able keep the records of my clients to use them in the future , this addition can a nice touch to the code , gain customer satisfaction so there data can be viewed whenever they want, but this process depend mainly on the hardware components such as (Memory specifications), on the other hand logging can be a relatively slow process, especially when there are a several clients are using the application.
•	Socket Communication: 
I have used the sockets connection to connect between server and clients effectively. So this mechanism is very useful to be implemented to this will give clients nice experience  and it provide our code with good level of data transformation between two sides , so as a result will ensure reliable data exchange. The efficiency of using Sockets  the connection between the clients and server is an Tcp. connection which more reliable  and efficient , so that will ensure that the data is transferred and received successfully without any losses 

•	Efficient BMI Calculation: 
The efficiency of how much is the BMI calculation is effect , for the formula that I have used I think it will be 100%, and the formula was developed to be as performance as possible .
•	Distribution of Tasks:
Evaluation: the code or the application is distributing task which the clients entries among the server server's threads. To be as effective as possible I have decided that each client will be handled from different thread , but as over all the memory will be shared , so this will also will not consume a lot system resources To ensure effective concurrent execution, each thread manages a different client connection.

