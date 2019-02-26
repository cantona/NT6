#include <ansi.h>
inherit __DIR__"pill";

void create()
{//6. 千年靈芝丸        HIY        49000                25000        150                由千年靈芝混合數種珍貴藥材所煉製的靈藥。

        set_name(HIY "千年靈芝丸" NOR, ({ "qiannian lingzhiwan", "lingzhi" ,"wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", HIY "由千年靈芝混合數種珍貴藥材所煉製的靈藥。\n" NOR);
                                                                set("unit", "粒");
                set("value", 25000);
                set("weight", 300);
                set("pill_skill", "force");
                set("skill_mapped", 1);
                set("pill_point", 49000);
                set("force_point", 150);
                set("pill_msg1", HIR "你只覺一股暖氣散佈全身，説不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}