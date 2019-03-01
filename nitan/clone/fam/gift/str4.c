#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(HIY "蚩尤誅元仙丹Ⅱ型" NOR, ({ "zhuyuan xiandan2" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "此丹乃是天宮中的神品，凡人吃了可以平增膂力。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 200000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("gift_type", "str");
                set("gift_name", "先天膂力");
                set("gift_point", 100);
                set("gift_msg", HIY "突然間你只覺雙臂幾乎爆裂，充滿了力量。\n" NOR);
        }
        setup();
}