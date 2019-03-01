#include <ansi.h>
inherit __DIR__"pill";

void create()
{//5.  百年靈芝丸        HIG        39000                20000        100                由百年靈芝混合數種珍貴藥材所煉制的靈藥。

        set_name(HIG "百年靈芝丸" NOR, ({ "bainian lingzhiwan", "lingzhi" ,"wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", HIG "由百年靈芝混合數種珍貴藥材所煉制的靈藥。\n" NOR);
                                                                set("unit", "粒");
                set("value", 20000);
                set("weight", 300);
                set("pill_skill", "force");
                set("skill_mapped", 1);
                set("pill_point", 39000);
                set("force_point", 100);
                set("pill_msg1", HIR "你只覺一股暖氣散布全身，說不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}