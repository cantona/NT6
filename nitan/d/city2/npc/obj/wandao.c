// gangdao.c
#include <weapon.h>
inherit BLADE;
#include <ansi.h>
void create()
{
        set_name(HIW"迴風刀"NOR, ({ "wan dao","dao","blade" }));   
        set_weight(12000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄鋒利的迴風刀，是宮中侍衞的常備武器。\n");
                set("value", 10000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回刀鞘。\n");
        }
        init_blade(200);
        setup();                   
}
