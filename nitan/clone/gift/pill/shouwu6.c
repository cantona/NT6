#include <ansi.h>
inherit __DIR__"pill";

void create()
{//6. 千年首烏丹        WHT        49000                25000        150                由千年何首烏混合數種珍貴藥材所煉制的靈藥。

        set_name(WHT "千年首烏丹" NOR, ({ "qiannian shouwudan","shouwu", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", WHT "由千年何首烏混合數種珍貴藥材所煉制的靈藥。\n" NOR);
                                                                set("unit", "顆");
                set("value", 25000);
                set("weight", 300);
                set("pill_skill", "parry");
                set("pill_point", 49000);
                set("force_point", 150);
                set("pill_msg1", HIR "你只覺一股暖氣散布全身，說不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}