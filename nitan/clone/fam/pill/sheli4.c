#include <ansi.h>
inherit __DIR__"pill";

void create()
{
        set_name(HIY "聖舍利" NOR, ({ "sheng sheli", "sheli", "sheng" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "佛門高僧在圓寂前通常都將畢生功力注入舍利子中。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 15000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("pill_skill", "etc");
                set("force_point", 40);
                set("pill_msg3", HIM "你感到精力又增加了一些。\n" NOR);
                set("pill_msg4", HIR "你感到內息澎湃，難以吸收藥力。\n" NOR);
        }
        setup();
}