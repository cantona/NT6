// tielianzi.c
#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
        set_name(HIG"煉心彈"NOR, ({ "lianxin dan", "dan" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "袋");
                set("value", 0);
                set("base_unit", "顆");
                set("base_weight", 300);
                set("base_value", 0);
                set("material", "iron");
                set("long", HIG"煉心彈是星宿派淬毒暗器，針長寸許，發出詭異的光。\n"NOR);
                set("wield_msg", HIC"$N迅速地從鹿皮袋中摸出一些煉心彈，捏在手中就待發出！\n"NOR);
                set("unwield_msg",HIC"$N將手裡剩下的煉心彈收回鹿皮袋中。\n"NOR);
        }
        set_amount(50);
        init_throwing(10);
        setup();
}