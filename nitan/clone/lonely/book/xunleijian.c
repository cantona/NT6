#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(WHT "「迅雷劍經」" NOR, ({ "xunlei jianjing", "jianjing", "xunlei", "jing", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", WHT "這是一本薄薄的書冊，書皮已然發"
                            "黃，看樣子已經有一段歷史了。\n" NOR);
                set("value", 1);
                set("no_sell", "這本破書你自己留着吧。");
                set("material", "paper");
                set("skill", ([
                        "name":       "xunlei-jian",
                        "jing_cost":  100,
                        "difficulty": 30,
                        "max_skill":  119,
                        "min_skill":  0
                ]));
        }
}