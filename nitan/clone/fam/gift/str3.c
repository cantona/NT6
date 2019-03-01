#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(HIY "蚩尤誅元仙丹" NOR, ({ "zhuyuan xiandan", "zhuyuan",
                                            "xiandan", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "傳說此丹乃是天宮中的神品，凡人吃了可以平增臂力。增加先天屬性至六點\n" NOR);
                set("base_unit", "顆");
                set("base_value", 100000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("gift_type", "str");
                set("gift_name", "先天膂力");
                set("gift_point", 85);
                set("gift_msg", HIY "突然間你只覺雙臂幾乎爆裂，充滿了力量。\n" NOR);
        }
        setup();
}
