#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "shenzhao"; }

string chinese_name() { return "神照經內勁"; }

string update_msg_others()
{
       return HIR "只見$N" HIR "嗆嗆退了數步，身子搖晃，雙"
              "腿漸漸彎曲，似乎喝醉了一般。\n" NOR;
}

string update_msg_self()
{
        return HIW "你只感內息頓滯，真氣不暢，一張臉漲得通"
               "紅，便要跌倒。\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] / 8;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 4;
}
