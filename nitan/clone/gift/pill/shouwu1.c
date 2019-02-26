#include <ansi.h>
inherit __DIR__"pill";

void create()
{//1. 何首烏        HIY        20000                10000        3                產於極北森林之中的珍貴藥材，服用後可提升招架等級。

        set_name(HIY "何首烏" NOR, ({ "heshouwu",  "shouwu" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", HIY "產於極北森林之中的珍貴藥材，服用後可提升招架等級。\n" NOR);
                                                                set("unit", "支");
                set("value", 10000);
                set("weight", 300);
                set("pill_skill", "parry");
                set("pill_point", 20000);
                set("force_point", 3);
                set("pill_msg1", HIR "你只覺一股暖氣散佈全身，説不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}