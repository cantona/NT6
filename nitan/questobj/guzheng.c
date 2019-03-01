// guzheng.c 古箏

#include <ansi.h>;

inherit ITEM;

void create()
{
        set_name(HIG"古箏"NOR, ({ "gu zheng", "zheng", "qin" }));
        set_weight(2000);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long",
                HIG"這是一張做工十分考究的古箏，古香古色，音質極好。\n"NOR);
                set("value", 0);
                set("material", "steel");
        }
}
