#include <ansi.h>
#include <weapon.h>

inherit XSWORD;

void create()
{
        set_name(NOR + GRN "綠玉洞簫" NOR, ({"lvyu dongxiao", "lvyu", "dongxiao", "xiao"}));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "支");
                set("long", GRN "一支綠玉做成的洞簫，看上去晶瑩温潤。武林"
                            "中人經常以蕭代劍。\n" NOR);
                set("value", 800000);
                set("no_sell", 1);
                set("material", "stone");
                set("wield_msg", GRN "$N" GRN "大袖一揮，手中已多了一支晶瑩温潤的綠玉洞蕭。\n" NOR);
                set("unwield_msg", GRN "$N" GRN "手中綠玉洞簫一轉，眨眼間已然不見影蹤。\n" NOR);
                set("stable", 100);
        }
        init_xsword(100);
        setup();
}