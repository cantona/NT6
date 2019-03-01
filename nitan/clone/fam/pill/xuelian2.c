#include <ansi.h>
inherit __DIR__"pill";

void create()
{
        set_name(HIC "千年雪蓮" NOR, ({ "qiannian xuelian", "qiannian",
                                        "xuelian", "lian" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "產于大雪山之上的珍貴藥材，服用後可提升輕功等級。\n" NOR);
                set("base_unit", "株");
                set("base_value", 15000);
                set("base_weight", 300);
                set("only_do_effect", 1);
                set("pill_skill", "dodge");
                set("pill_point", 38000);
                set("force_point", 5);
                set("pill_msg1", HIW "你只感到清涼之意散布全身，說不出的舒服受用。\n" NOR);
                set("pill_msg2", HIC "你只覺靈台處清欣無比，精力得到了完全的補充。\n" NOR);
        }
        setup();
}