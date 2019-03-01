// tea_leaf.c
 
#include <weapon.h>
#include <ansi.h>
inherit THROWING;
 
void create()
{
        set_name(HIG"茶葉"NOR, ({ "tea_leaf", "tea" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "才採的新茶，發出一股淡淡的香氣。\n");
                set("unit", "把");
                set("value", 0);
                set("base_unit", "片");
                set("base_weight", 1);
                set("base_value", 0);
                set("damage", 1);        //Here the damage=int_throwing, added by King
                set("material", "wood");
                set("wield_msg", HIC"$N迅速地從暗器袋中掏出一些茶葉，捏在手中就待發出！\n"NOR);
                set("unwield_msg",HIC"$N將手裡剩下的茶葉盡數放回暗器袋中。\n"NOR);
        }
        set_amount(50);
        init_throwing(1);
        setup();
}