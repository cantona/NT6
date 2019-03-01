// silverjian.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
#include <ansi.h>
inherit MACE;

void create()
{
        set_name(HIW "銀裝□" NOR, ({"silver mace", "mace", "silvermace", "yinjian", "jian"}));
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 8000);
                set("material", "silver");
                set("long", "一柄閃閃發光的銀裝□，顯然是被人擦了又擦。\n");
                set("wield_msg", "只見一道銀光閃過，$N手裡已經多了一柄$n！\n");
                set("unwield_msg", "$N收起了$n，四周光芒為之一暗！\n");
        }
        
        init_mace(65);
        setup();
}
