#include <ansi.h>
inherit __DIR__"pill";

void create()
{
        set_name(HIW "天山雪蓮" NOR, ({ "tianshan xuelian", "tianshan",
                                        "xuelian", "lian" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "產於大雪山之上的珍貴藥材，服用後可提升輕功等級。\n" NOR);
                set("base_unit", "株");
                set("base_value", 10000);
                set("base_weight", 300);
                set("only_do_effect", 1);
                set("pill_skill", "dodge");
                set("pill_point", 20000);
                set("force_point", 3);
                set("pill_msg1", HIW "你只感到清涼之意散佈全身，説不出的舒服受用。\n" NOR);
                set("pill_msg2", HIC "你只覺靈台處清欣無比，精力得到了完全的補充。\n" NOR);
        }
        setup();
}
