#include <ansi.h>
inherit __DIR__"pill";

void create()
{
        set_name(NOR + RED "百年參心丹" NOR, ({ "shenxin dan", "shenxin", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", RED "由百年人蔘混合數種珍貴藥材所煉製的靈藥。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 20000);
                set("base_weight", 100);
                set("only_do_effect", 1);
                set("pill_skill", "force");
                set("pill_point", 30000);
                set("force_point", 50);
                set("pill_msg1", HIR "你只覺一股暖氣散佈全身，説不出的舒服受用。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱流湧上，內息得到了完全的補充。\n" NOR);
        }
        setup();
}