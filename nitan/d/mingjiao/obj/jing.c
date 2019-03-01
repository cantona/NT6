#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "「楞伽經」" NOR, ({ "lengjia jing", "jing", "book" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", YEL "這是一本薄薄的經書，只因油布包得緊密，雖長期\n"
                            "藏在猿腹之中，書頁仍然完好無損。書面上寫著幾\n"
                            "個彎彎曲曲的文字，你卻是一個也不識得。\n" NOR);
                set("value", 10);
                set("material", "silk");
                set("skill", ([
                        "name":         "buddhism",
                        "exp_required": 1000,
                        "jing_cost":    10,
                        "difficulty":   10,
                        "max_skill":    50,
                        "min_skill":    0,
                        "need" : ([ "sanscrit" : 500 ]),
                ]) );

        }
}