#define BLINKER_WIFI
#define BLINKER_ALIGENIE_LIGHT //天猫精灵
#include <Blinker.h>
 
char auth[] = "d2398502b79d";   //换成APP获取到的密匙
char ssid[] = "sun";          //WiFi账号
char pswd[] = "84582796";   //WIFI密码
int pinRelay =0; 
 
// 新建组件对象
BlinkerButton Button1("btn-abc");
BlinkerNumber Number1("num-abc"); 

// 按下按键即会执行该函数
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    if (state=="on") {
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(pinRelay,LOW);
        // 反馈开关状态
        Button1.print("on");
    } else if(state=="off"){
        digitalWrite(LED_BUILTIN, HIGH);
        // 反馈开关状态
        digitalWrite(pinRelay, HIGH);
        Button1.print("off");
    }
}

void heartbeat()  //心跳包
{
      Button1.icon("fas fa-lightbulb");
      Button1.color("#fddb00");
      Button1.text("关灯","打开啦");
      Number1.print(WiFi.RSSI());  //信号强度

}

//天猫精灵
void aligeniePowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(pinRelay, LOW);
        BlinkerAliGenie.powerState("off");
        BlinkerAliGenie.print();
    }
    else if (state == BLINKER_CMD_OFF) {
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(pinRelay, HIGH);
        BlinkerAliGenie.powerState("on");
        BlinkerAliGenie.print();
    }
}

void setup() {
    // 初始化串口
    Serial.begin(115200);
    // 初始化有LED的IO
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(0, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);
     digitalWrite(pinRelay, HIGH);
    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Button1.attach(button1_callback);
    BlinkerAliGenie.attachPowerState(aligeniePowerState);
    Blinker.attachHeartbeat(heartbeat);
}
 
void loop() {
    Blinker.run();
    //Blinker.run()语句负责处理Blinker收到的数据，每次运行都会将设备收到的数据进行一次解析。
//在使用WiFi接入时，该语句也负责保持网络连接
}
