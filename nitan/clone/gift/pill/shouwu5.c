#include <ansi.h>
inherit __DIR__"pill";

void create()
{//5. 百年首烏丹        CYN        39000                20000        100                由百年何首烏混合數種珍貴藥材所煉製的靈藥。

        set_name(CYN "百年首烏丹" NOR, ({ "bainian shouwudan","shouwu", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", CYN "由百年何首烏混合數種珍貴藥材所煉製的靈藥。\n" NOR);
                                                                set("unit", "顆");
                set("value", 20000);
                set("weight", 300);
                set("pill_skill", "parry");
                set("pill_point", 39000);
                set("force_point", 100);
                set("pill_msg1", HIR "你只覺一股暖氣散佈全身，説不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}