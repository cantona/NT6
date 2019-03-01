#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "綴錦閣");
        set("long", @LONG
這是日常梳妝打扮的地方，放著一張紅木梳妝台，正對著你的是
一面光潤的銅鏡，梳妝台上散落著一些胭脂花粉。台旁擺著鬥大的一
個汝瓷花囊，插著滿滿的水晶球兒般的白菊。
LONG );
        set("exits", ([
                "west" : __DIR__"changl14",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}