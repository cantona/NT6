#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "綴錦閣");
        set("long", @LONG
這是日常梳粧打扮的地方，放着一張紅木梳粧枱，正對着你的是
一面光潤的銅鏡，梳粧枱上散落着一些胭脂花粉。台旁擺着斗大的一
個汝瓷花囊，插着滿滿的水晶球兒般的白菊。
LONG );
        set("exits", ([
                "west" : __DIR__"changl14",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}