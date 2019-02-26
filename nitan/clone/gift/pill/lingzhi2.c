#include <ansi.h>
inherit __DIR__"pill";

void create()
{//2.  百年靈芝        HIG        30000                15000        5                產於高山上的珍貴藥材，服用後可提升內功等級。

        set_name(HIG "百年靈芝" NOR, ({ "bainian lingzhi", "lingzhi" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", HIG "產於高山上的珍貴藥材，服用後可提升內功等級。\n" NOR);
                                                                set("unit", "株");
                set("value", 15000);
                set("weight", 300);
                set("pill_skill", "force");
                set("skill_mapped", 1);
                set("pill_point", 30000);
                set("force_point", 5);
                set("pill_msg1", HIR "你只覺一股暖氣散佈全身，説不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}