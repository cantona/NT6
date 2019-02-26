#include <ansi.h>
inherit __DIR__"pill";

void create()
{
        set_name(HIC "千年雪蓮膏" NOR, ({ "xuelian gao", "gao", "xuelian", "lian" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "由千年雪蓮混合數種珍貴藥材所煉製的靈藥。\n" NOR);
                set("base_unit", "盒");
                set("base_value", 30000);
                set("base_weight", 100);
                set("only_do_effect", 1);
                set("pill_skill", "dodge");
                set("pill_point", 50000);
                set("force_point", 100);
                set("pill_msg1", HIW "你只感到清涼之意散佈全身，説不出的舒服受用。\n" NOR);
                set("pill_msg2", HIC "你只覺靈台處清欣無比，精力得到了完全的補充。\n" NOR);
        }
        setup();
}