#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(NOR + HIW "神恩通慧仙丹Ⅱ型" NOR, ({ "tonghui xiandan2" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "此丹乃是天宮中的神品，凡人吃了可以平增悟性。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 200000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("gift_type", "int");
                set("gift_name", "先天悟性");
                set("gift_point", 100);
                set("gift_msg", HIG "突然間你只覺靈台處一片空明，舒泰無比。\n" NOR);
        }
        setup();
}