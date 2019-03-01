#include <ansi.h>
inherit __DIR__"pill";

void create()
{//4. 首烏丹        YEL        29000                15000        50                由何首烏混合數種珍貴藥材所煉制的靈藥。

        set_name(YEL "首烏丹" NOR, ({ "shouwu dan", "shouwu","dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", YEL "由何首烏混合數種珍貴藥材所煉制的靈藥。\n" NOR);
                                                                set("unit", "顆");
                set("value", 15000);
                set("weight", 300);
                set("pill_skill", "parry");
                set("pill_point", 29000);
                set("force_point", 50);
                set("pill_msg1", HIR "你只覺一股暖氣散布全身，說不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}