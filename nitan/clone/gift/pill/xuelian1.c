#include <ansi.h>
inherit __DIR__"pill";

void create()
{//1. 天山雪蓮        WHT        20000                10000        3                產于大雪山之上的珍貴藥材，服用後可提升輕功等級。

        set_name(WHT "天山雪蓮" NOR, ({ "tianshan xuelian",  "xuelian", "lian" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", WHT "產于大雪山之上的珍貴藥材，服用後可提升輕功等級。\n" NOR);
                                                                set("unit", "株");
                set("value", 10000);
                set("weight", 300);
                set("pill_skill", "dodge");
                set("pill_point", 20000);
                set("force_point", 3);
                set("pill_msg1", HIW "你只感到清涼之意散布全身，說不出的舒服受用。\n" NOR);
                set("pill_msg2", HIC "你只覺靈台處清欣無比，精力得到了完全的補充。\n" NOR);
        }
        setup();
}