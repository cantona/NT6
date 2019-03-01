#include <ansi.h>
#include <medical.h>

inherit MEDICAL_BOOK;

void create()
{
        set_name(HIM "「桃花藥理」" NOR, ({ "taohua yaoli", "yaoli", "book", "shu" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", HIM "一本陳舊的書冊，封面用篆書寫有「桃花藥理」四字。\n\n" NOR);
                set("material", "paper");
                set("value", 1);
                set("no_sell", "嘿，這本破書也能賣錢？");
                set("skill", ([
                        "name" : "taohua-yaoli",
                        "jing_cost" : 60,
                        "difficulty" : 40,
                        "max_skill" : 159,
                        "min_skill" : 30,
                ]));

                set("can_make", ([
                        "liuhe"    : 80,        // 六合返精散
                        "qingxin"  : 100,       // 清心定神散
                        "zhending" : 150,       // 固元鎮定散
                        "dieda"    : 80,        // 跌打傷癒膏
                        "huojin"   : 100,       // 活筋舒血丸
                        "tongmai"  : 150,       // 貫氣通脈丹
                        "jiedu"    : 100,       // 牛黃解毒丸
                        "shadan"   : 160,       // 田七鯊膽丸
                        "jiuhua"   : 200,       // 九花玉露丸
                        "wuchang"  : 250,       // 無常丹
                ]));
        }
        setup();
}