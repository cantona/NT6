// wudang.c

#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
        set_name(HIG "煉丹祕本" NOR, ({ "liandan miben", "miben" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本泛黃的書籍，上面用小篆書"
                            "寫着“煉丹祕本”幾個字。\n",

                );
                set("material", "paper");
                set("skill", ([
                        "name": "liandan-shu",
                        "jing_cost": 60,
                        "difficulty": 40,
                        "max_skill": 155,
                        "min_skill": 30,
                ]));

                set("can_make", ([
                        "shujing"  : 80,        // 舒筋活絡丹
                        "dieda"    : 80,        // 跌打傷愈膏
                        "jiedu"    : 100,       // 牛黃解毒丸
                        "yuzhen"   : 150,       // 玉真散
                        "yuling"   : 150,       // 玉靈散
                        "yuqing"   : 200,       // 玉清散
                        "sanhuang" : 250,       // 三黃寶臘丹
                ]));
        }
        setup();
}
