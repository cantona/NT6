#include <room.h>
inherit ROOM;

void create()
{
        set("short", "林間小徑");
        set("long", @LONG
你走在一條小徑上，兩旁種滿了竹子，修篁森森，綠蔭滿地，除
了竹葉聲和鳥鳴聲，聽不到別的動靜。南面似乎有一座簡陋的小院。
LONG );
        set("exits", ([
                "south" : __DIR__"xiaoyuan.c",
                "north" : __DIR__"xiaolu1",
        ]));
        set("objects", ([
                CLASS_D("wudang") + "/qingfeng": 1,
                CLASS_D("wudang") + "/mingyue": 1,
        ]));
        create_door("south", "竹門", "north", DOOR_CLOSED);
        set("outdoors", "wudang");
        set("coor/x", -370);
        set("coor/y", -330);
        set("coor/z", 90);
        setup();
}
