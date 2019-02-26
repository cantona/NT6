// Room: /d/taiwan/yahoushe.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "雅猴社");
        set("long", @LONG
雅猴社又稱阿猴社，乃得名自西拉雅平埔族馬卡道支族阿侯社之社
名音譯。馬卡道族原生活於打狗社，明未清初時，因漢人入墾，只得棄
地東遷，另行建社，是為雅猴社。
LONG );
        set("exits", ([
                "west" : __DIR__"dagougang",
        ]));
        set("objects", ([
                __DIR__"npc/makadaoman": 1,
                __DIR__"npc/makadaowoman": 1,
                __DIR__"npc/makadaokid": 1,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2520);
        set("coor/y", -7070);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
