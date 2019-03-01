// persuading.c 渡世濟人
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;

string type() { return "knowledge"; }
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

void skill_improved(object me)
{}

int valid_learn(object me)
{
        return notify_fail("渡世濟人要在實踐中提高。\n");
}
int help(object me)
{
        write(HIC"\n渡世濟人："NOR"\n");
        write(@HELP

    峨嵋弟子崇信大乘佛教，悲天憫人，講究渡人渡己，不僅僅是
只顧自己修行，所以渡世濟人的功業乃是峨嵋派考量門人弟子的重
要標準。峨嵋弟子可用命令persuade勸服戰鬥中的玩家或者ＮＰＣ
罷鬥，在實用中增長修為，並取得實戰經驗和潛能。
    請help persuade。

        學習要求：
                實踐中獲得
HELP
        );
        return 1;
}
