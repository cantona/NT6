#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(NOR + HIY "增慧丹" NOR, ({ "zenghui dan", "zenghui", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "這是一顆通體金黃的藥丸，據説吃了可以增強悟性。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 10000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("gift_type", "int");
                set("gift_name", "先天悟性");
                set("gift_point", 40);
                set("gift_msg", HIG "突然間你只覺靈台處一片空明，舒泰無比。\n" NOR);
        }
        setup();
}
