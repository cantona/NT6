#include <ansi.h>
inherit ROOM;

void home(object ob);

void create()
{
        set("short", "海灘");
        set("long", @LONG
你被一陣風吹得頭暈目眩，似乎又回到了海灘。
LONG);


        setup();
}

void init()
{

	this_player()->move("/d/shenlong/haitan");
}
