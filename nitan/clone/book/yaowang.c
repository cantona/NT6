// yaowang.c

#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
        set_name(HIM "藥王神篇" NOR, ({ "yaowang shenpian", "shu" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本薄薄的小冊子，上面工工整整"
                            "寫著“藥王神篇”幾個字。\n",

                );
                set("material", "paper");
                set("skill", ([
                        "name": "yaowang-miaoshu",
                        "jing_cost": 60,
                        "difficulty": 40,
                        "max_skill": 200,
                        "min_skill": 30,
                ]));

                set("can_make", ([
                        "liuhe" : 80,           // 六合返精散
                        "qingxin" : 100,        // 清心定神散
                        "zhending": 150,        // 固元鎮定散
                        "dieda" : 80,           // 跌打傷癒膏
                        "huojin" : 100,         // 活筋舒血丸
                        "tongmai" : 150,        // 貫氣通脈丹
                        "jiedu" : 100,          // 牛黃解毒丸
                        "tianxin" : 100,        // 天心解毒丹
                        "shengsheng" : 200,     // 生生造化丹
                ]));
        }
        setup();
}
