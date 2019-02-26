// Room: /d/gaibang/yyandao1.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "暗道");
        set("long", @LONG
這是丐幫極其祕密的地下通道，乃用丐幫幾輩人之心血掘成。 
LONG );
        set("exits", ([
                "north" : __DIR__"undertre",
                "south" : __DIR__"yyandao2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -500);
        set("coor/y", -500);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}