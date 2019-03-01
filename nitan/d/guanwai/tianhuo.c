// /guanwai/tianhuo.c

inherit ROOM;

void create()
{
        set("short", "天豁峰");
        set("long", @LONG
乘槎河東岸，與龍門峰對峙。峰頂如鷹嘴般的峻峭山峰破石而出，伸向
天池，故又名鷹嘴峰。古書載：“峰起雙尖，中辟一線，有豁然開朗、令人
不可思議之趣”，相傳為大禹治水所劈，石多赤色，猶如二龍蟠踞，妙趣橫
生。
LONG );
        set("exits", ([
                "south" : __DIR__"huagai",
                "west"  : __DIR__"longmen",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "changbai");
        setup();
        replace_program(ROOM);
}