// Room: /d/gaibang/cdandao1.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "暗道");
        set("long", @LONG
這是丐幫極其祕密的地下通道，乃用丐幫幾輩人之心血掘成。 
LONG );
        set("exits", ([
                "southwest" : __DIR__"cdandao2",
                "northeast" : __DIR__"undertre",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3000);
        set("coor/y", -1000);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}