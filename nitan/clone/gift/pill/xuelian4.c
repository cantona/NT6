#include <ansi.h>
inherit __DIR__"pill";

void create()
{//4. 天山雪蓮膏        HIW        29000                15000        50                由天山雪蓮混合數種珍貴藥材所煉制的靈藥。

        set_name(HIW "天山雪蓮膏" NOR, ({ "tianshan xueliangao", "xuelian", "gao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                                                                set("long", HIW "由天山雪蓮混合數種珍貴藥材所煉制的靈藥。\n" NOR);
                                                                set("unit", "盒");
                set("value", 15000);
                set("weight", 300);
                set("pill_skill", "dodge");
                set("pill_point", 29000);
                set("force_point", 50);
                set("pill_msg1", HIW "你只感到清涼之意散布全身，說不出的舒服受用。\n" NOR);
                set("pill_msg2", HIC "你只覺靈台處清欣無比，精力得到了完全的補充。\n" NOR);
        }
        setup();
}