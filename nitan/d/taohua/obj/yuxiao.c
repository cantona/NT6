#include <ansi.h>
#include <weapon.h>

inherit XSWORD;

void create()
{
        set_name(HIW "玉蕭" NOR, ({"yu xiao", "xiao"}));
        set_weight(500);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("long", "一支白玉做成的長蕭，看上去晶瑩温潤。武林中人經常以蕭代劍。\n");
                set("value", 10000);
                set("material", "stone");
                set("wield_msg", "$N大袖一揮，手中已多了一支晶瑩温潤的玉蕭。\n");
                set("unwield_msg", "$N手中玉蕭一轉，眨眼間玉蕭已然不見影蹤。\n");
        }
        init_xsword(45);
        setup();
}