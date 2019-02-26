// Room: /yangzhou/yongdao.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","甬道");
        set("long",@LONG
從天王殿至大雄寶殿，正中甬道檜柏夾立，東通“文章奧區”，西
通“仙人舊館”。甬道中有兩座鐵製寶鼎，兩側高台，兩株銀杏參天，
東為雌株，西為雄株。
    大雄寶殿前平台，東有百年古柏，西有百年黃楊，寶殿更顯古樸莊
嚴。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "east"  : __DIR__"pingyuanlou",
                "west"  : __DIR__"pingshantang",
                "north" : __DIR__"daxiongbaodian",
                "south" : __DIR__"tianwangdian",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -30);
        set("coor/y", 160);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}