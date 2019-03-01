// feihuangshi.c
 
#include <weapon.h>
#include <ansi.h>
 
inherit THROWING;
 
void create()
{
        set_name("飛蝗石", ({ "feihuangshi", "shi" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "仔細挑選的鵝卵石，大小一致，個個都滴溜溜圓。\n");
                set("unit", "把");
                set("value", 0);
                set("base_unit", "個");
                set("base_weight", 1);
                set("base_value", 0);
                set("damage", 5);        //Here the damage=int_throwing, added by King
                set("material", "stone");
                set("wield_msg", HIC"$N迅速地從暗器袋中掏出一些飛蝗石，捏在手中就待發出！\n"NOR);
                set("unwield_msg",HIC"$N將手裡剩下的飛蝗石盡數放回暗器袋中。\n"NOR);
        }
        set_amount(20);
        init_throwing(25);
        setup();
}