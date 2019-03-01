// Room: /d/gaibang/zlandao2.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "暗道");
        set("long", @LONG
這是丐幫極其秘密的地下通道，乃用丐幫幾輩人之心血掘成。 
LONG );
        set("exits", ([
                "northeast" : __DIR__"undergb",
                "southwest" : __DIR__"zlandao1",        
        ]));
        set("no_clean_up", 0);
        set("coor/x", 40);
        set("coor/y", 30);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}