// jindan.c
#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIY"金膽"NOR, ({ "jin dan", "dan" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "袋");
                set("value", 0);
                set("base_unit", "顆");
                set("base_weight", 300);
                set("base_value", 0);
                set("material", "gold");
                set("long", HIW"黃澄澄的金膽，比之鐵膽固重了一倍有余，而且大顯華貴之氣。\n"NOR);
                set("wield_msg", HIC"$N迅速地從暗器袋中掏出一些金膽，捏在手中就待發出！\n"NOR);
                set("unwield_msg",HIC"$N將手裡剩下的金膽盡數放回暗器袋中。\n"NOR);
        }
        set_amount(50);
        init_throwing(25);
        setup();
}