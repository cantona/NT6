// Room: /d/gaibang/dlandao2.c
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
                "southwest" : __DIR__"underdl",
                "northeast" : __DIR__"dlandao1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -20000);
        set("coor/y", -30000);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}