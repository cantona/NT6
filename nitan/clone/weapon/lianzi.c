// tielianzi.c
#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIC"鐵蓮子"NOR, ({ "tie lianzi", "lianzi","tie" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "袋");
                set("value", 0);
                set("base_unit", "顆");
                set("base_weight", 300);
                set("base_value", 0);
                set("material", "iron");
                set("long", HIW"鐵蓮子是一種以量取勝的暗器，沉顛顛的。\n"NOR);
                set("wield_msg", HIC"$N迅速地從暗器袋中掏出一些鐵蓮子，捏在手中就待發出！\n"NOR);
                set("unwield_msg",HIC"$N將手裡剩下的鐵蓮子盡數放回暗器袋中。\n"NOR);
        }
        set_amount(50);
        init_throwing(25);
        setup();
}