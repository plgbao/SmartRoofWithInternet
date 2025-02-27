SMART ROOF  CONNECTED WITH INTERNET 
In this project, I have designed a smart roof using in smart home model using ESP8266
To explore the project you can git clone using this command: gitclone 
TABLE OF CONTENT
1. Introduction
2. Connect ESP8266 with Arduino Uno
3. Thingspeak alert
4. Referrences
INTRODUCTION
In today's digital era, wireless networks (WiFi) have become an essential part of our daily lives. From accessing the Internet, connecting smart devices, to supporting high-tech applications, WiFi plays an important role in improving quality of life and work efficiency.
This project focuses on researching and applying WiFi technology in remote device control, specifically controlling rain covers through the ESP01-S module and Atmega328P chip. The goal of the project is to build a SmartHome system via WiFi, allowing users to open/close the cover remotely through smartphones or laptops.
Through implementing this project, I hope to not only better understand the operating principles of WiFi and wireless communication protocols, but also apply this knowledge in practice, contributing to the development of smart technology solutions in the future.
CIRCUIT DIAGRAM
![image](https://github.com/user-attachments/assets/f6cbd15b-4fdf-4095-a74e-bbc985bf475c)

THINGSPEAK ALERT (I USE THINGSPEAK SO IN CASES IF YOU CONNECT TO ANOTHER WIFI, YOU STILL CAN SEE WHAT HAPPEN AT YOUR HOME :>)
% Thông tin kênh ThingSpeak
channelID = 2753218;  % Thay bằng Channel ID của bạn
readAPIKey = 'D97RHAVJQ8MEQZMW';  % Thay bằng API Key đọc
% Thông tin email
myEmail = 'bao.pham28903@hcmut.edu.vn';  % Thay bằng email của bạn
myPassword = 'pdvb ggkt khcs pztv';  % Thay bằng mật khẩu ứng dụng nếu dùng xác thực 2 yếu tố
recipient = 'giabao28903@gmail.com';  % Địa chỉ email người nhận
subject = 'Alert from ThingSpeak';  % Tiêu đề email
message = 'Cảnh báo có mưa';  % Nội dung email
% Bắt đầu đo thời gian thực thi
tic;
% Đọc dữ liệu từ ThingSpeak
fieldID = 1;  % Trường cần đọc, thay bằng field tương ứng
numPoints = 1;  % Số lượng điểm dữ liệu cần đọc (1 là điểm mới nhất)
try
    data = thingSpeakRead(channelID, 'Fields', fieldID, 'NumPoints', numPoints, 'ReadKey', readAPIKey, 'Timeout', 15);  % Timeout set to 15 seconds
    disp(['Dữ liệu từ ThingSpeak: ', num2str(data)]);
catch ME
    disp('Lỗi khi đọc dữ liệu từ ThingSpeak:');
    disp(ME.message);
    return;  % Dừng chương trình nếu lỗi đọc dữ liệu
end
% Kiểm tra dữ liệu và gửi email nếu cần
threshold = 40;  % Ngưỡng để kiểm tra
if isempty(data) || isnan(data)
    disp('Không có dữ liệu để phân tích.');
elseif data > threshold
    try
        % Cấu hình SMTP cho Gmail
        setpref('Internet', 'SMTP_Server', 'smtp.gmail.com');  % Máy chủ SMTP của Gmail
        setpref('Internet', 'SMTP_Username', myEmail);  % Tên người dùng (email của bạn)
        setpref('Internet', 'SMTP_Password', myPassword);  % Mật khẩu ứng dụng của bạn
        setpref('Internet', 'SMTP_Port', 587);  % Cổng 587 cho TLS
        setpref('Internet', 'SMTP_SSL', 'false');  % Không bật SSL, bật TLS
        setpref('Internet', 'SMTP_TLS', 'true');  % Bật TLS
        setpref('Internet', 'E_mail', myEmail);  % Địa chỉ email người gửi
        % Gửi email
        sendmail(recipient, subject, message);
        disp('Email đã được gửi thành công!');
    catch ME
        disp('Đã có lỗi xảy ra khi gửi email:');
        disp(ME.message);  % In ra lỗi nếu có
    end
else
    disp('Dữ liệu an toàn, không cần gửi email.');
end
% Kết thúc đo thời gian thực thi
toc;
HOW TO USE:
First, access Thinkspeak. Then navigate to MATLAB Analytics, then copy the code
Result:
![image](https://github.com/user-attachments/assets/78d27b95-6e1b-4230-be90-c5d1d1c9d015)
REFERRENCES
1.	Giáo trình Vi xử lý (2023), trường Đại học Bách Khoa – Đại học Quốc gia thành phố Hồ Chí Minh.
2.	Giáo trình Truyền số liệu và mạng (2024), trường Đại học Bách Khoa – Đại học Quốc gia thành phố Hồ Chí Minh.
3.	https://docs.arduino.cc/built-in-examples/arduino-isp/ArduinoToBreadboard/
4.	ESP01-S Datasheet, Microchip Company.
5.	“How to make an IoT based Temperature and Humidity monitoring system using Nodemcu and Thingspeak”, https://srituhobby.com/how-to-make-an-iot-based-temperature-and-humidity-monitoring-system-using-nodemcu-and-thingspeak/
