// tiedan.c
#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIW"鐵膽"NOR, ({ "tiedan", "dan" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "些");
                set("value", 0);
                set("base_unit", "枚");
                set("base_weight", 300);
                set("base_value", 0);
                set("material", "iron");
                set("long", HIG"一些溜圓的鐵膽，是一種兇猛的暗器。\n"NOR);
                set("wield_msg", HIC"$N迅速地從身上摸出一些鐵膽，捏在手中就待發出！\n"NOR);
                set("unwield_msg",HIC"$N將手裡剩下的鐵膽一抖就不見了。\n"NOR);
        }
        set_amount(50);
        init_throwing(50);
        setup();
}