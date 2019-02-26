//ROOM: /d/yanziwu/shijian.c

inherit ROOM;

void create()
{
        set("short", "試劍台");
        set("long", @LONG
玉石欄杆圍成的一座石台，慕容世家的弟子經常在此練習武技，
台角放着刀槍劍戟等十八般兵器。 場中立着一些製作極為精妙的木人。
東邊則是慕容家弟子苦心修行的地方。
LONG );
        set("outdoors", "yanziwu");
        set("exits", ([
                "south"  : __DIR__"changlang",
                "east"   : __DIR__"kuxiu",
        ]));

        set("objects", ([
                "/clone/weapon/zhubang.c" : 1,
                "/clone/weapon/mudao.c"   : 1,
                "/clone/weapon/zhujian.c" : 1,
                "/clone/weapon/bian.c"    : 1,
        ]));
        set("for_family", "慕容世家");

        setup();
}