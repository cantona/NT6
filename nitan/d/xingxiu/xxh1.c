// Room: /d/xingxiu/xxh1.c
// Last Modified by winder on Apr. 25 2001

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "星宿海");
        set("long", @LONG
這裏是星宿海。因方圓幾百裏都是一望無際的湖泊和沼澤，當地
牧羊人稱之為“海”。也因陰暗潮濕，毒蟲繁殖甚富。星宿弟子常來此
捕捉毒蟲，以備練毒之用。這裏通向星宿海的深處。
LONG
        );
        set("objects", ([
                __DIR__"npc/xxdizi"  : 1,
        ]) );
        set("exits", ([
                "south" : __DIR__"xxh",
                "north" : __DIR__"xxh2",
        ]));
        set("outdoors", "xingxiu");
        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", 20200);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);

}
//#include "/d/xingxiu/xxh.h";
