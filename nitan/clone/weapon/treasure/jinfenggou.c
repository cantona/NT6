// jinfenggou.c 金鳳鈎
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
#include <ansi.h>;
inherit HOOK;
inherit F_UNIQUE;

void create()
{
        set_name(HIY"金鳳鈎"NOR, ({ "jinfeng gou", "gou" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "這是一柄餵了劇毒的金鈎，鈎端好似一隻蛇頭。\n");
                set("value", 10000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一聲抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n插回鞘中。\n");
        }
        init_hook(130);
        setup();
}