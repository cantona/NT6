// Room: /d/shaolin/guangchang2.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "廣場");
        set("long", @LONG
過了天王殿，又有三道平行的青石台階引正前方的一個大廣場。
台階上刻的是諸天眾佛，五百羅漢以及三千伽藍的坐像。上了平台，
正中方也有個丈許高的大香爐，香爐前的香台上，紅燭高燒，香煙飄
繞，幾位香客正對大殿虔誠叩拜。左右各通向一個小院，兩座高塔高
聳天際。正前方就是大雄寶殿。
LONG );
        set("exits", ([
                "south" : __DIR__"twdian",
                "north" : __DIR__"guangchang3",
                "northup" : __DIR__"dxbdian",
                "east" : __DIR__"zhonglou",
                "west" : __DIR__"gulou",
        ]));
        set("outdoors", "shaolin");
        set("objects",([
                __DIR__"npc/xiang-ke" : 1,
                __DIR__"npc/seng-bing3" : 2,
                CLASS_D("shaolin") + "/qing-shan" : 1,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
