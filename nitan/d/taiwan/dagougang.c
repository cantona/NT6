// Room: /d/taiwan/dagougang.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "打狗港");
        set("long", @LONG
打狗港也稱“西港”，港域口小腹大，外有島鏈環抱，內具曲折峽
灣，誠全台第一良港。明朝都督俞大猷曾屯兵于此抗擊倭寇。大清收台
後，打狗港的漁業日趨發達，貿易日益昌盛，與大陸間的往來頻繁，逐
漸成為台灣西部海岸的最佳停泊港。
LONG );
        set("exits", ([
                "east"  : __DIR__"yahoushe",
                "north" : __DIR__"ningnanfang",
        ]));
        set("objects", ([
                __DIR__"npc/yufu": 1,
                __DIR__"npc/shangren": 1,
//                __DIR__"npc/pingpuren": 1,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2510);
        set("coor/y", -7070);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
