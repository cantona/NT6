#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "qianzhu_wandushou"; }

string chinese_name() { return "穿心劇毒"; }

string update_msg_others()
{
       return HIB "只見$N" HIB "毒氣上湧，臉浮現出一層黑氣，不住的顫抖。\n" NOR;
}

string update_msg_self()
{
        return HIB "你只覺毒氣攻心，頭暈目眩，一陣說不出的惡心。\n" NOR;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 5;
}

int dispel(object me, object ob, int duration)
{
        if (me != ob)
        {
                tell_object(ob, "你發覺" + me->name() + "的內力源源湧進，使丹"
                            "田處燃燒得更為厲害，便如身陷洪爐，眼前登時一黑。\n");
                tell_object(me, "你試圖幫助" + ob->name() + "化解異種真氣，卻"
                            "發現對方真氣便似洪爐爆裂，不由大驚，連忙住手。\n");

                if (living(ob))
                        ob->unconcious();

                return -1;
        }


        tell_object(me, "你覺得全身真氣猶如洪爐爆裂，內息"
                        "根本無法凝聚。\n");
        return -1;
}
