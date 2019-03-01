// Room: /d/huashan/pingdi.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "山間平地");
        set("long", @LONG
你走在中條山山間平地上。靠東山壁上有一小屋。傳聞當年華山
玉女峰劍氣兩宗大對決，中計敗北的劍宗弟子大多隱匿中條山。難道
就是這裡？林中冷風輕吹門響。很失意的感覺。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "north" : __DIR__"shangu",
            "east"  : __DIR__"xiaowu",
        ]));
        set("outdoors", "huashan");
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
