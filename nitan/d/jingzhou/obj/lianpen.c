//Edited by fandog, 02/15/2000

inherit ITEM;
#include <ansi.h>

void create()
{
        set_name("臉盆", ({"lian pen", "pen"}));
        set("unit", "只");
        set("no_get", 1);

        set("long", "這是一只普通之極的臉盤，盆中裝滿了水。\n");
        setup();
}