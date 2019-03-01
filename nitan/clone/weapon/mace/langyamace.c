//langyamace.c
// Last Modified by winder on May. 25 2001

#include <weapon.h>
#include <ansi.h>
inherit MACE;

void create()
{
        set_name("狼牙棒", ({"langya bang", "mace", "langyabang", "langya"}));
        set_weight(8000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 18000);
                set("material", "iron");
                set("long", "烏黑的狼牙棒上生滿了倒刺，讓人不由得凜然生畏。\n");
                set("wield_msg", "$N“呼”的一聲抽出一柄$n，惡狠狠地盯著周圍的人！\n");
                set("unwield_msg", "$N小心翼翼地收起$n，差點被倒刺傷著自己。\n");
        }
        
        init_mace(35);
        setup();
}
