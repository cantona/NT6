#include <ansi.h>
inherit __DIR__"pill";

void create()
{
        set_name(HIG "菩提子" NOR, ({ "puti zi", "zi", "puti" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "此萬年菩提樹之實，採自靈山佛祖座前，珍稀無比。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 15000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("pill_skill", "force");
                set("force_point", 40);
                set("pill_msg3", HIM "你感到內力又雄厚了一些。\n" NOR);
                set("pill_msg4", HIR "你感到內息澎湃，難以吸收藥力。\n" NOR);
        }
        setup();
}