// Room: /d/taiwan/zhuluo.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "諸羅");
        set("long", @LONG
諸羅，位於阿里山山麓原為平埔族土隴社聚居之地，於清代初年始
逐漸發展成都會區。是阿里山林業的木材集散地與製材加工中心。 
LONG );
        set("exits", ([
                "northwest" : __DIR__"pingye",
                "southwest" : __DIR__"zhenbeifang",
        ]));
        set("objects", ([
                __DIR__"npc/qiaofu": 1,
                __DIR__"npc/shangren": 1,
                __DIR__"npc/pingpuren": 1,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2520);
        set("coor/y", -7030);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
