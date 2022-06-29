/* *****************************************************************
 *
 * Download latest Blinker library here:
 * https://github.com/blinker-iot/blinker-library/archive/master.zip
 * 
 * 
 * Blinker is a cross-hardware, cross-platform solution for the IoT. 
 * It provides APP, device and server support, 
 * and uses public cloud services for data transmission and storage.
 * It can be used in smart home, data monitoring and other fields 
 * to help users build Internet of Things projects better and faster.
 * 
 * Make sure installed 2.7.4 or later ESP8266/Arduino package,
 * if use ESP8266 with Blinker.
 * https://github.com/esp8266/Arduino/releases
 * 
 * Make sure installed 1.0.5 or later ESP32/Arduino package,
 * if use ESP32 with Blinker.
 * https://github.com/espressif/arduino-esp32/releases
 * 
 * Docs: https://diandeng.tech/doc
 *       
 * 
 * *****************************************************************
 * 
 *       
 * 
 * *****************************************************************/

#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT

#include <Blinker.h>

char auth[] = "b2d8xxxxxx";  //填写电灯科技设备码
char ssid[] = "esp";         //填写wifi名
char pswd[] = "asdfghjkl";   //填写wifi密码
//串口2
HardwareSerial mySerial(2);
//变量定义
bool button1_state,button2_state,button3_state,button4_state,button5_state,button6_state,button7_state,button8_state;
bool Slider1_state,Slider2_state,Slider3_state,Slider4_state,Slider5_state;
//按键组态对象
BlinkerButton Button1("btn-abc");  //white
BlinkerButton Button2("btn-534");  //yellow
BlinkerButton Button3("btn-jkf");  //rgb
BlinkerButton Button4("btn-gxd");  //all_off
BlinkerButton Button5("btn-s4o");  //scene1
BlinkerButton Button6("btn-fk2");  //scene2
BlinkerButton Button7("btn-c4p");  //scene3
BlinkerButton Button8("btn-5q5");  //scene4
//滑块组态对象
BlinkerSlider Slider1("ran-kcs");  //white_slider
BlinkerSlider Slider2("ran-m01");  //yellow_slider
BlinkerSlider Slider3("ran-a7j");  //red_slider
BlinkerSlider Slider4("ran-uob");  //green_slider
BlinkerSlider Slider5("ran-zxa");  //blue_slider
//文本组态编写
BlinkerText Text1("tex-u5u");
BlinkerText Text2("tex-gel");
BlinkerText Text3("tex-klo");
//LED_TEST函数
void LED_TEST(void)
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
//BUTTON的回调函数
void button1_callback(const String & state)
{
    LED_TEST();
    button1_state=!button1_state;
    mySerial.print("010:");
    mySerial.println(button1_state);
    Text1.print(button1_state);   //用来把LED状态返回到APP上，方便控制；
    
}
void button2_callback(const String & state)
{
    LED_TEST();
    button2_state=!button2_state;
    mySerial.print("011:");
    mySerial.println(button2_state);
    Text2.print(button2_state);
}
void button3_callback(const String & state)
{
  LED_TEST();
    button3_state=!button3_state;
    mySerial.print("012:");
    mySerial.println(button3_state);
    Text3.print(button3_state);
}
void button4_callback(const String & state)
{
   LED_TEST();
    button4_state=!button4_state;
    mySerial.print("013:");
    mySerial.println("1");  //这里把状态默认1了；即为应该向上面一样检测按下状态，但是我都没操作
    button1_state=0;button2_state=0;button3_state=0;
    Text1.print("0");
    Text2.print("0");
    Text3.print("0");
}
void button5_callback(const String & state)
{
   LED_TEST();
    button5_state=!button5_state;
    mySerial.print("014:");
    mySerial.println(button5_state);
}
void button6_callback(const String & state)
{
  LED_TEST();
    button6_state=!button6_state;
    mySerial.print("015:");
    mySerial.println(button6_state);
}
void button7_callback(const String & state)
{
  LED_TEST();
    button7_state=!button7_state;
    mySerial.print("016:");
    mySerial.println(button7_state);
}
void button8_callback(const String & state)
{
  LED_TEST();
    button8_state=!button8_state;
    mySerial.print("017:");
    mySerial.println(button8_state);
}
//滑动条回调函数
void slider1_callback(int32_t value)
{
    LED_TEST();
    mySerial.print("020:");
    mySerial.println(value);
}
void slider2_callback(int32_t value)
{
    LED_TEST();
    mySerial.print("021:");
    mySerial.println(value);
}
void slider3_callback(int32_t value)
{
    LED_TEST();
    mySerial.print("022:");
    mySerial.println(value);
}
void slider4_callback(int32_t value)
{
    LED_TEST();
    mySerial.print("023:");
    mySerial.println(value);
}
void slider5_callback(int32_t value)
{
   LED_TEST();
    mySerial.print("024:");
    mySerial.println(value);
}
//小爱的回调函数
void miotPowerState(const String & state)
{
    if (state == BLINKER_CMD_ON) {

        mySerial.println("010:1");
        delay(10);
        mySerial.println("020:200");
        LED_TEST();
        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_OFF) {
      
        mySerial.println("010:0");
        delay(10);
        mySerial.println("020:0");
        LED_TEST();
        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
}
void miotColor(int32_t color)
{
    short int colorR,colorG,colorB;
    colorR = color >> 16 & 0xFF;
    colorG = color >>  8 & 0xFF;
    colorB = color       & 0xFF;
    
    mySerial.print("022:");
    mySerial.println(colorR);
    delay(10);
    mySerial.print("023:");
    mySerial.println(colorG);
    delay(10);
    mySerial.print("024:");
    mySerial.println(colorB);
    LED_TEST();
    BlinkerMIOT.color(color);
    BlinkerMIOT.print();
}
void miotBright(const String & bright)
{
    short int light;
    short int colorW;
    colorW = bright.toInt();
    Serial.println(bright);
    mySerial.print("020:");
    light=colorW*2.5;
    delay(10);
    mySerial.println(light);
    LED_TEST();
    BlinkerMIOT.brightness(colorW);
    BlinkerMIOT.print();
}
////////////////////////////////////////////////////////以上为APP组件初始化及回调函数////////////////////////////////////////////////
void setup()
{
    // 初始化串口
    Serial.begin(115200);
    mySerial.begin(115200,SERIAL_8N1,16,17);  //串口2初始化
    //变量初始化
    button1_state=0;button2_state=0;button3_state=0;button4_state=0;button5_state=0;button6_state=0;button7_state=0;button8_state=0;
    Slider1_state=0;Slider2_state=0;Slider3_state=0;Slider4_state=0;Slider5_state=0;

    // 初始化有LED的IO
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    //疯狂调用callback
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);
    Button3.attach(button3_callback);
    Button4.attach(button4_callback);
    Button5.attach(button5_callback);
    Button6.attach(button6_callback);
    Button7.attach(button7_callback);
    Button8.attach(button8_callback);
    
    Slider1.attach(slider1_callback);
    Slider2.attach(slider2_callback);
    Slider3.attach(slider3_callback);
    Slider4.attach(slider4_callback);
    Slider5.attach(slider5_callback);

    BlinkerMIOT.attachPowerState(miotPowerState);
    BlinkerMIOT.attachColor(miotColor);
}

void loop() {
    Blinker.run();
}
