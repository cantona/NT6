// mojiao.c

#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
        set_name(HIG "魔教醫術" NOR, ({ "mojiao medical", "medical" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本泛黃的書籍，上面用古篆書"
                            "寫著“魔教醫術”幾個字。\n",

                );
                set("material", "paper");
                set("skill", ([
                        "name": "mojiao-medical",
                        "jing_cost": 60,
                        "difficulty": 40,
                        "max_skill": 160,
                        "min_skill": 30,
                ]));

                set("can_make", ([
                        "tianmo" : 280,           // 天魔聖血膏
                ]));
        }
        setup();
}