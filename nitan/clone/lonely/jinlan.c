#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(HIY "錦襴袈裟" NOR, ({ "jinlan jiasha", "jinlan", "jiasha" }));
        set_weight(1000);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "件");
                set("long", HIY "錦襴袈裟乃少林寺歷代相傳的聖物，是由冰蠶"
                            "造練抽絲，巧匠\n翻騰為線，仙娥織就，神女機成"
                            "。方方簇幅繡花縫，片片相幫\n堆錦簆。穿上滿身"
                            "紅霧繞，脱來一段彩雲飛。\n" NOR);
                set("wear_msg", HIY "只聽「譁」的一聲，$N展開一件金光閃閃"
                            "的袈裟披在身上。瞬\n時瑞氣千條，祥雲朵朵。遙"
                            "見$N氣象莊嚴，真可謂五嶽山前生\n寶氣，三天門"
                            "外透玄光。重重嵌就西番蓮，灼灼懸珠星斗象。\n"
                            NOR);
                set("remove_msg", HIY "$N將錦襴袈裟從身上脱下，摺疊成小小"
                            "的一團。\n" NOR);
                set("no_sell", "東西是好，可惜少林寺賊禿厲害，俺沒膽子收。");
                set("value", 100000);
                set("material", "silk");
                set("armor_prop/armor", 200);
                set("stable", 100);
        }
        setup();
}