// biandan.c

#include <weapon.h>;
#include <ansi.h>;
inherit STAFF;

void create()
{
        set_name(GRN"扁擔"NOR, ({ "bian dan", "dan" }) );
        set_weight(1000);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("long", "這是一條挑擔的扁擔。\n");
                set("value", 0);
                set("material", "wood");
                set("wield_msg", "$N拿出一條$n，握在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }

        setup();
}