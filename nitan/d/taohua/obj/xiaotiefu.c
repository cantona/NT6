//Cracked by Kafei
#include <ansi.h>
#include <weapon.h>
inherit AXE;

void create()
{
        set_name("小鐵斧", ({ "xiao tiefu", "axe" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", 
"這是一柄精鋼打造的小斧頭，似乎不太適合戰鬥，木匠和樵夫很喜歡用的工具。\n");
                set("value", 200);
                set("material", "steel");
                set("wield_msg", 
"$N「唰」的一聲拔出一柄精光閃閃的小斧頭握在手裏。\n");
                set("unwield_msg", "$N將手中的$n插回腰間。\n");
        }
        init_axe(10);
        setup();
}
