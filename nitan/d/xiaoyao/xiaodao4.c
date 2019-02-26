// xiaodao4.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "林間小道");
        set("long", @LONG
這是一條長長的林間小道，從東邊一直通到西邊，一眼望去，看不
到路的盡頭。兩旁百花爭豔。令人留連忘返。
LONG );
        set("exits", ([
                "east" : __DIR__"shulin1",
                "west" : __DIR__"qingcaop",
                "north" : __DIR__"liangong",
                "south" : __DIR__"mubanlu",
        ]));
         set("objects", ([
                CLASS_D("xiaoyao")+"/wulingjun": 1,
                __DIR__"npc/mengmianr": 2,
        ]));
        set("outdoors", "xiaoyao");
        set("coor/x", 90);
        set("coor/y", -500);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}