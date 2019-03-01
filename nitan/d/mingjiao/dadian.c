//room: /d/mingjiao/dadian.c
inherit ROOM;

void init();

void create()
{
        set("short","明教大殿");
        set("long", @LONG
走進這裏，突感一陣肅穆之意，大殿中十分空曠，殿頂高懸八盞
金燈，兩旁是精壯佩劍武士劍氣森嚴逼人。正中設一寶座，前有一雕
花檀木案，案頭供明教聖火令(ling)六枚。寶座後立有一扇玉屏，屏
中所畫正是明教聖火圖，烈焰直逼日月。寶座上端坐一人，着布衣而
顯高貴，含笑不怒而自威，正是明教教主張無忌。
LONG );
        set("exits",([
            "south" : __DIR__"qiandian",
            "enter" : __DIR__"neishi",
        ]));
        set_temp("tieling",8);
        set("objects",([
            CLASS_D("mingjiao")+"/zhangwuji":1,
            CLASS_D("mingjiao")+"/yangxiao":1,
            CLASS_D("mingjiao")+"/fanyao":1,
            CLASS_D("mingjiao")+"/yintianzheng":1,
            // CLASS_D("mingjiao")+"/xiexun":1,
            CLASS_D("mingjiao")+"/weiyixiao":1,
        ]));
        setup();
        replace_program(ROOM);
}
