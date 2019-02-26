//Edited by fandog, 02/15/2000

inherit ITEM;
#include <ansi.h>


void create()
{
        set_name(HIY"虎撐"NOR, ({"hu cheng", "cheng"}));
        set("unit", "把");
//      set("no_get", 1);

        set("long", "這是一把郎中走街串巷搖着的虎撐。\n");
        setup();
}
