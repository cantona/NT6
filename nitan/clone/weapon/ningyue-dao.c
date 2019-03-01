#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
        set_name(NOR + WHT "凝月刀" NOR, ({ "ningyue dao", "ningyue", "dao", "blade" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", NOR + WHT "這是一柄亮晃晃的寶刀，在月光下顯得格外耀眼。\n" NOR);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回刀鞘。\n");
                set("value", 100000);
        }
        init_blade(300);
        setup();
}

int query_autoload()
{
        return 1;
}