#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(WHT "「胡家刀譜」" NOR, ({ "hujia daopu", "hujia", "daopu", "pu", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", WHT "這是一本薄薄的書冊，書皮已然發黃，封"
                            "面上寫著「胡家刀譜」四個字。\n" NOR);
                set("value", 1);
                set("no_sell", "奶奶的，這本破書也能賣錢？");
                set("material", "paper");
                set("skill", ([
                        "name" : "blade",
                        "exp_required" : 30000,
                        "jing_cost"  : 120,
                        "difficulty" : 70,
                        "max_skill"  : 179,
                        "min_skill"  : 0
                ]));
        }
}