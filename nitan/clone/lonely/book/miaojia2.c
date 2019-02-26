#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(YEL "「苗家劍譜」下冊" NOR, ({ "miaojia jianpu", "miaojia", "jianpu", "pu", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", YEL "這是一本薄薄的書冊，書皮已然發黃，封"
                            "面上寫着「苗家劍譜」四個字。\n" NOR);
                set("value", 1);
                set("no_sell", "…苗…苗家…金面佛他老人家我可得罪不起。");
                set("material", "paper");
                set("skill", ([
                        "name" : "sword",
                        "exp_required" : 300000,
                        "jing_cost"  : 120,
                        "difficulty" : 80,
                        "max_skill"  : 199,
                        "min_skill"  : 150
                ]));
        }
}