#include <ansi.h>
inherit __DIR__"pill";

void create()
{
        set_name(HIG "碧魄" HIR "血" HIG "精" NOR, ({ "bipo xuejing", "bipo", "xuejing" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "晶瑩剔透的血精，乃大雪山玄冰赤蟒的鮮血結"
                                "凍而成。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 10000);
                set("base_weight", 300);
                set("only_do_effect", 1);
                set("pill_skill", "force");
                set("pill_point", 5000);
                set("force_point", 20);
                set("pill_msg1", HIG "你只覺一股熱線從咽喉直通到腹中，全"
                                 "身經脈舒泰無比。\n" NOR);
                set("pill_msg2", HIY "你只覺一股熱線從咽喉直通到腹中，內"
                                 "息得到完全補充。\n" NOR);
        }
        setup();
}