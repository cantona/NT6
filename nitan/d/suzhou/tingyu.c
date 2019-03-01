// Room: /d/suzhou/tingyu.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "聽雨軒");
        set("long", @LONG
聽雨軒是蘇州城內的一處唯一的一家書店了。這裡有著各種各樣的
書籍，什麼小說啦、風光旅遊啦、手藝制作啦、基本武功啦，等等等等。
只須花幾兩銀子就可買到你想要的書。
LONG );
//        set("outdoors", "suzhou");
        set("exits", ([
                "west"  : __DIR__"nandajie2",
        ]));
        set("objects", ([
                __DIR__"npc/bookboss" : 1,
        ]));
	set("coor/x", 1120);
	set("coor/y", -1080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}