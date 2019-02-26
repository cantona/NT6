#include <weapon.h>
inherit SWORD;
#include <ansi.h>
void create()
{
        set_name(HIY "金蜈鈎" NOR, ({ "jinwu gou", "gou", "jinwu" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "一柄金光閃閃的鈎子，頂端好似一隻蛇頭。\n");
                set("value", 10000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回鞘中。\n");
        }
        init_sword(200);
        setup();
}