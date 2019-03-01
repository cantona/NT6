#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(HIC "「祁連五絕指」" NOR, ({ "qilian zhi", "qilian", "zhi", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", YEL "這是一本薄薄的書冊，書皮已然發黃，封"
                            "面上寫着「祁連五絕指」五個字。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("material", "paper");
                set("skill", ([
                        "name":       "qilian-zhi",
                        "exp_required" : 140000,
                        "jing_cost":  60,
                        "difficulty": 52,
                        "max_skill":  1,
                        "min_skill":  0
                ]));
        }
}