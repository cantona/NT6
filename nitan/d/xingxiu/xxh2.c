// Room: /d/xingxiu/xxh2.c
// Last Modified by winder on Apr. 25 2001

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "星宿海");
        set("long", @LONG
這裡是星宿海。因方圓幾百裡都是一望無際的湖泊和沼澤，當地牧
羊人稱之為“海”。也因陰暗潮濕，毒蟲繁殖甚富。星宿弟子常來此捕
捉毒蟲，以備練毒之用。這裡通向星宿海的深處。
LONG);
        set("objects", ([
                __DIR__"npc/xxdizi"  : 1,
        ]) );

        set("exits", ([
                "east" : __DIR__"xiaolu",
                "south" : __DIR__"xxh1",
                "west" : __DIR__"xiaojing",
                "north" : __DIR__"huangdi",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", 20200);
        set("coor/z", 0);
        set("outdoors", "xingxiu");
        setup();
//        replace_program(ROOM);

}
// #include "/d/xingxiu/xxh.h";
