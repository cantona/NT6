#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
        set_name(WHT "「武當藥理」" NOR, ({ "wudang yaoli", "yaoli", "book", "shu" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", WHT "一本陳舊的書冊，封面用草書寫有「武當藥理」四字。\n\n" NOR);
                set("material", "paper");
                set("value", 1);
                set("no_sell", "嘿，這本破書也能賣錢？");
                set("skill", ([
                        "name" : "wudang-yaoli",
                        "jing_cost" : 40,
                        "difficulty" : 50,
                        "max_skill" : 149,
                        "min_skill" : 50,
                ]));

                set("can_make", ([
                        "liuhe"    : 80,         // 六合返精散
                        "qingxin"  : 100,        // 清心定神散
                        "zhending" : 150,        // 固元鎮定散
                        "dieda"    : 80,         // 跌打傷愈膏
                        "huojin"   : 100,        // 活筋舒血丸
                        "tongmai"  : 150,        // 貫氣通脈丹
                        "jiedu"    : 100,        // 牛黃解毒丸
                        "baihu"    : 200,        // 白虎奪命丹
                        "baola"    : 220,        // 三黃寶臘丹
                ]));
        }
        setup();
}