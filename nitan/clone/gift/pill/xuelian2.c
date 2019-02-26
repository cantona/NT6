#include <ansi.h>
inherit __DIR__"pill";

void create()
{//2. 百年雪蓮        CYN        30000                15000        5                產於大雪山之上的珍貴藥材，服用後可提升輕功等級。

        set_name(CYN "百年雪蓮" NOR, ({ "bainian xuelian",  "xuelian", "lian" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", CYN "產於大雪山之上的珍貴藥材，服用後可提升輕功等級。\n" NOR);
                                                                set("unit", "株");
                set("value", 15000);
                set("weight", 300);
                set("pill_skill", "dodge");
                set("pill_point", 30000);
                set("force_point", 5);
                set("pill_msg1", HIW "你只感到清涼之意散佈全身，説不出的舒服受用。\n" NOR);
                set("pill_msg2", HIC "你只覺靈台處清欣無比，精力得到了完全的補充。\n" NOR);
        }
        setup();
}