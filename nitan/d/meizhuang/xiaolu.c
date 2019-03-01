#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "蜿蜒小徑");
        set("long", @LONG
這條小路的兩旁種著無數的梅花，雖然還沒到梅花盛開的季節，
但透過這密密的梅林，你似乎已經聞到了陣陣的梅花的幽香，這時你
已經發現你快走到莊園的門口，你暗地裡加快了腳步。
LONG );
        set("exits", ([
            "south" : __DIR__"shijie",
            "north" : __DIR__"gate",
        ]));
        set("outdoors", "meizhuang");
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}