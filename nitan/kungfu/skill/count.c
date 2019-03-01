// count.c 陰陽八卦
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

int is_fmsk() { return 1; } 
string type() { return "knowledge"; }
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

void skill_improved(object me) {}

int valid_learn(object me)
{
        int gift, mat;

        gift = 35;
        mat = 300;

        if( query("family/family_name", me) == "桃花島" )
        {
                gift = 30;
                mat = 200;
        }

        if( !query("family/family_name", me) || 
            query("family/family_name", me) != "桃花島" )
                return notify_fail("你不是桃花島弟子，難以領會陰陽八卦的奧妙。\n");

        if( query("int", me)<gift )
                return notify_fail("你的先天悟性不足，難以領會陰陽八卦的奧妙。\n");

        if ((int)me->query_skill("mathematics", 1) < mat)
                return notify_fail("你的算術知識太差，無法理解陰陽八卦的奧妙。\n");

        if ((int)me->query_skill("mathematics", 1) < (int)me->query_skill("count", 1))
                return notify_fail("你的算術知識有限，無法理解更深奧的陰陽八卦。\n");

        if( me->query_skill("zuoyou-hubo",1) && !query("special_skill/capture", me) )
                return notify_fail("你的受到左右互博分心之術影響，難以領會陰陽八卦的奧妙。\n");

        return 1;
}


int practice_skill(object me)
{
        return notify_fail("陰陽八卦只能用學(learn)的來增加熟練度。\n");
}
int help(object me)
{
        write(HIC"\n陰陽八卦："NOR"\n");
        write(@HELP

    桃花島弟子可以憑此技能查知玩家目前所在的位置。可以通過
閱讀《河圖》、《洛書》提高。
    請help location。

        學習要求：
                讀書寫字50級
                身為黃藥師嫡傳弟子
HELP
        );
        return 1;
}
