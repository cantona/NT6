// Room: /d/gaibang/cdandao2.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "暗道");
        set("long", @LONG
這是丐幫極其祕密的地下通道，乃用丐幫幾輩人之心血掘成。 
LONG );
        set("exits", ([
                "southwest" : __DIR__"undercd",
                "northeast" : __DIR__"cdandao1",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -6000);
        set("coor/y", -2000);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}