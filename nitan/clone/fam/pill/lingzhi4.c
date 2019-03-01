#include <ansi.h>
inherit __DIR__"pill";

void create()
{
        set_name(HIG "千年靈芝丸" NOR, ({ "lingzhi wan", "lingzhi", "wan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "由千年靈芝混合數種珍貴藥材所煉制的靈藥。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 30000);
                set("base_weight", 100);
                set("only_do_effect", 1);
                set("pill_skill", "force");
                set("skill_mapped", 1);
                set("pill_point", 40000);
                set("force_point", 100);
                set("pill_msg1", HIR "你只覺一股暖氣散布全身，說不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}