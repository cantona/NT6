// Room: /d/gaibang/qzandao1.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "暗道");
        set("long", @LONG
這是丐幫極其祕密的地下通道，乃用丐幫幾輩人之心血掘成。 
LONG );
        set("exits", ([
                "southeast" : __DIR__"qzandao2",
                "northwest" : __DIR__"undertre",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 500);
        set("coor/y", -100);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}