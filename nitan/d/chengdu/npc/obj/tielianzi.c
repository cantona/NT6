// tielianzi.c
 
#include <weapon.h>
#include <ansi.h>
inherit THROWING;
 
void create()
{
        set_name("鐵蓮子", ({ "tie lianzi", "lianzi", "zi" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "精鐵打制的蓮子狀暗器。\n");
                set("unit", "把");
                set("value", 0);
                set("base_unit", "粒");
                set("base_weight", 1);
                set("base_value", 0);
                set("material", "iron");
                set("damage", 5);        //Here the damage=int_throwing, added by King
                set("wield_msg", HIC"$N迅速地從暗器袋中掏出一些鐵蓮子，捏在手中就待發出！\n"NOR);
                set("unwield_msg",HIC"$N將手裡剩下的鐵蓮子盡數放回暗器袋中。\n"NOR);
        }
        set_amount(30);
        init_throwing(15);
        setup();
}