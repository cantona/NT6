// blade.c
// Last Modified by winder on May. 25 2001
#include <ansi.h>
#include <weapon.h>
inherit BLADE;

void create()
{
         set_name(HIG"小樓一夜聽春雨"NOR, ({ "springrain blade", "blade" }) );
         set_weight(4000);
         if( clonep() )
                 set_default_object(__FILE__);
         else {
                 set("unit", "柄");
                 set("value", 500);
                 set("material", "iron");
                 set("long",
                        "〝小樓一夜聽春雨〝又名〝小樓聽雨〝。是西方神教兩大掌門信物之一。\n"
                        "此刀極邪，又削鐵如泥。\n");
                 set("wield_msg", "$N抽出一把明晃晃的$n握在手中。\n");
                 set("unequip_msg", "$N將手中的$n插入腰間的刀鞘。\n");
         }
         init_blade(300);
         setup();
}
