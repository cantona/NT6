// Room: /lingzhou/yipindating.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "一品堂大廳");
        set("long", @LONG
這裡是西夏一品堂的大廳，廳內闊大，顯得有點陰晦。數十根合抱
大柱撐著看不清頂的飛檐，廳裡氣氛很是森森煞人。北面正中一副楠木
匾額(bian)高懸，金字藍底，隱隱生威。紅木公案後虎皮交椅上，正襟
威坐著的，就是征東大將軍赫連總管。周圍立著幾個一品堂衛士，紋風
不動。
LONG );
        set("item_desc", ([
                "bian"  : "一品堂\n",
        ]));
        set("exits", ([
                "south" : __DIR__"yipindayuan",
                "west"  : __DIR__"mishi",
        ]));
        set("objects", ([
                "/quest/helian" :1,
                __DIR__"npc/yipinwushi" :4,
        ]));
        set("no_fight",1);
        create_door("west","木門","east",DOOR_CLOSED);
        set("coor/x", -6295);
        set("coor/y", 2965);
        set("coor/z", 0);
        setup();
}
int valid_leave(object me, string dir)
{
        if (dir =="west" )
        {
                if (present("wu shi", environment(me)))
                return notify_fail("一品堂武士一言不發地擋在你前面。\n"); 
                return 1;
        }
        return ::valid_leave(me, dir);
}