// wudang.c

#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
        set_name(HIG "玉女心經" NOR, ({ "yunv xinjing", "xinjing" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本泛黃的書籍，上面用小篆書"
                            "寫著“玉女心經”幾個字。\n",

                );
                set("material", "paper");
                set("skill", ([
                        "name": "yunv-xinjing",
					    "family_name" : "古墓派",
                        "jing_cost": 60,
                        "difficulty": 40,
                        "max_skill": 60,
                ]));

                set("can_make", ([
                        "jinmisan" : 80,        // 金蜜散
                ]));
        }
        setup();
}
