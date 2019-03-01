#include <ansi.h> 
inherit ITEM;

void create()
{
        set_name(NOR + WHT "「毒經下篇」" NOR, ({ "du jing3", "jing3", "book3" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", WHT "這是一本薄薄的小冊，上面記滿了五毒教特"
                            "有的用毒的法門。\n" NOR);
                set("value", 100);
                set("no_sell", "我…我的天…連五毒教的東西你都敢拿來賣？");
                set("material", "silk");
                set("skill", ([
                        "name"         : "wudu-qishu",
                        "exp_required" : 150000,
                        "jing_cost"    : 50,
                        "difficulty"   : 50,
                        "min_skill"    : 50,
                        "max_skill"    : 149,
                ]));
        }
}