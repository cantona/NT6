// Room: /d/gaibang/wxandao2.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "暗道");
        set("long", @LONG
這是丐幫極其祕密的地下通道，乃用丐幫幾輩人之心血掘成。 
LONG );
        set("exits", ([
                "south" : __DIR__"underwx",
                "north" : __DIR__"wxandao1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 200);
        set("coor/y", 1000);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}