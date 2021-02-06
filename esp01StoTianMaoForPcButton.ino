#define BLINKER_WIFI
#define BLINKER_ALIGENIE_OUTLET   // 天猫精灵
#include <Blinker.h>

# 个人公众号：wangyanglinux宝典
# 个人博客：svcloudt.com


char auth[] = "key"; // 改成自己在点灯 app 中生成的 key 码
char ssid[] = "wangyanghome"; //caiyq52-改成自己的WIFI名称
char pswd[] = "wangyang";  //caiyq52-改成自己的WIFI密码



BlinkerButton Button1("btn-abc");     // 此组件未点灯 app 中自己设置的按键，改名 "btn-abc" 必须与自己 APP 中设定的名称一致
bool oState = false;
int Pin = 0;    // 定义控制引脚
void AliGeniePowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {     // 天猫精灵控制开命令
        digitalWrite(0, LOW);
        delay(200);
        digitalWrite(0, HIGH);
        BlinkerAliGenie.powerState("on");

        BlinkerAliGenie.print();

        oState = true;
    }
    else if (state == BLINKER_CMD_OFF) {   // 天猫精灵控制关命令
        digitalWrite(0,LOW);
        delay(200);
        digitalWrite(0, HIGH);
        BlinkerAliGenie.powerState("off");

        BlinkerAliGenie.print();

        oState = false;
    }
}

void AliGenieQuery(int32_t queryCode)      // 天猫精灵控制
{
    BLINKER_LOG("AliGenie Query codes: ", queryCode);

    switch (queryCode)
    {
        case BLINKER_CMD_QUERY_ALL_NUMBER :
            BLINKER_LOG("AliGenie Query All");
            BlinkerAliGenie.powerState(oState ? "on" : "off");
            BlinkerAliGenie.print();
            break;
        case BLINKER_CMD_QUERY_POWERSTATE_NUMBER :
            BLINKER_LOG("AliGenie Query Power State");
            BlinkerAliGenie.powerState(oState ? "on" : "off");
            BlinkerAliGenie.print();
            break;
        default :
            BlinkerAliGenie.powerState(oState ? "on" : "off");
            BlinkerAliGenie.print();
            break;
    }
}

void dataRead(const String & data)      // 如果未绑定的组件被触发，则会执行其中内容
{
    BLINKER_LOG("Blinker readString: ", data);

    Blinker.vibrate();
   
    uint32_t BlinkerTime = millis();
   
    Blinker.print("millis", BlinkerTime);
}

void button1_callback(const String & state)     // 点灯 app 内控制按键触发
{
     BLINKER_LOG("get button state: ", state);
    digitalWrite(0,LOW);
    delay(200);
    digitalWrite(0, HIGH);
}

void setup()
{
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);

    pinMode(Pin, OUTPUT);              // 定义 io 口为输出
    digitalWrite(Pin, LOW);           // 定义 io 默认电平

    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
   
    BlinkerAliGenie.attachPowerState(AliGeniePowerState);
    BlinkerAliGenie.attachQuery(AliGenieQuery);
    Button1.attach(button1_callback);      
}

void loop()
{
    Blinker.run();
}
