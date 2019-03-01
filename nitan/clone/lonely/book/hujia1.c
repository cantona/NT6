#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(WHT "「胡家拳經」" NOR, ({ "hujia quanjing", "hujia", "quanjing", "jing", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", WHT "這是一本薄薄的書冊，書皮已然發黃，看"
                            "樣子已經有一段歷史了。\n" NOR);
                set("value", 1);
                set("no_sell", "奶奶的，這本破書也能賣錢？");
                set("material", "paper");
                set("skill", ([
                        "name" : "hujia-quan",
                        "exp_required" : 10000,
                        "jing_cost"  : 100,
                        "difficulty" : 40,
                        "max_skill"  : 119,
                        "min_skill"  : 0
                ]));
        }
}