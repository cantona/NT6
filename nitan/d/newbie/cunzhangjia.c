#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "村長家" NOR);
        set("long", @LONG
這裏是古村村長的家，屋內卻是頗為樸素，牆邊靠着幾個農具，
牆角一張竹牀，與普通村民家沒什麼區別。
LONG);

        set("exits", ([
                "north"  :  __DIR__"woshi",
                "west" :  __DIR__"chufang",
                "south"  :  __DIR__"road2",
        ]));
        set("xinshoucun", 1);
        set("outdoors", "newbie");
        
        set("no_fight", 1);
        setup();

        replace_program(ROOM); 
}
