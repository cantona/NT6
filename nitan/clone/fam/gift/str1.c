#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(HIG "神力丸" NOR, ({ "shenli wan", "shenli", "wan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "這是一顆通體渾圓的藥丸，據說吃了可以增強膂力。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 10000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("gift_type", "str");
                set("gift_name", "先天膂力");
                set("gift_point", 40);
                set("gift_msg", HIY "突然間你只覺雙臂幾乎爆裂，充滿了力量。\n" NOR);
        }
        setup();
}
