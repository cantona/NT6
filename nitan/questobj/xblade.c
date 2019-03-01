// xue-dao.c

#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name( HIR "血刀" NOR , ({ "blood_blade", "blade" }));
        set_weight(1000);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", HIR "這是一把纏在腰間的寶刀，刀鋒帶著淡淡的血影。\n" NOR );
                set("value", 0);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回刀鞘。\n");
        }
        setup();
}