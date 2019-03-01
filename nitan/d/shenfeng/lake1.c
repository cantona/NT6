inherit ROOM;

void create()
{
        set("short", "小溪");
        set("long", @LONG
沙丘間忽然出現了稀稀落落的鐵草，再奔一陣，地下青草
漸多。轉眼之間，面前出現一條小溪，俯身溪邊，掬了一口水
喝下，只覺一陣清涼，直透心肺。那水甘美之中還帶有微微香
氣，想必出自一處絕佳的泉水。溪水中無數小塊碎冰互相撞擊
發出清脆聲音，叮叮咚咚，宛如仙樂。
LONG);
        set("outdoors", "gaochang");
        set("resource/water", 1);
        set("exits", ([ 
                "north" : __DIR__"lake2",
                "south" : __DIR__"lvzhou",
        ]));
        setup();
}