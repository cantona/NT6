#include <weapon.h>
#include <ansi.h>

inherit WHIP;

void create()
{
        set_name(NOR + WHT "黑索" NOR, ({  "hei suo", "hei", "suo", "whip" }));
        set_weight(1000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", NOR + WHT "這是一根漆黑的長鞭，毫不起眼，但是入手"
                            "沉重，且\n不失柔韌，實在是千錘百煉之物。\n" NOR);
                set("long", WHT "一支通體漆黑的長鞭，看上去倒是很堅韌。\n" NOR);
                set("unit", "根");
                set("value", 800000);
                set("no_sell", "這是啥破玩藝，上吊用的？");
                set("material", "steel");
                set("wield_msg", WHT "$N" WHT "一伸手，悄無聲息的將黑索握在手中。\n" NOR);
                set("unwield_msg", WHT "$N" WHT "將手中的黑索卷起，放回腰間。\n" NOR);
                set("stable", 100);
        }
        init_whip(120);
        setup();
}