#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(YEL "「苗家劍譜」上冊" NOR, ({ "miaojia jianpu", "miaojia", "jianpu", "pu", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", YEL "這是一本薄薄的書冊，書皮已然發黃，封"
                            "面上寫著「苗家劍譜」四個字。\n" NOR);
                set("value", 1);
                set("no_sell", "…苗…苗家…金面佛他老人家我可得罪不起。");
                set("material", "paper");
                set("skill", ([
                        "name":       "suqin-beijian",
                        "exp_required" : 10000,
                        "jing_cost":  100,
                        "difficulty": 40,
                        "max_skill":  119,
                        "min_skill":  0
                ]));
        }
}