//Edited by fandog, 02/15/2000

inherit ITEM;
#include <ansi.h>


void create()
{
        set_name(HIC"石獅子"NOR, ({"shi shizi", "stone lion"}));
        set("unit", "座");
        set("no_get", 1);

        set("long", "這是一座栩栩如生的石獅子，張牙舞爪的。\n");
        setup();
}