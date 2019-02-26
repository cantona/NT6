// blade.c 基本刀法
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 30; }
int power_point(object me) { return 1; }

int help(object me)
{
        write(HIC"\n基本刀法："NOR"\n");
        write(@HELP

    刀類武技的基本功。
    刀是歷代重要兵器之一，其中大刀被譽為「百兵之帥」。「刀
如猛虎，槍似蛟龍」。刀術的演練一招一式都要有威武、凜烈的氣
慨。刀的使用特點是纏頭裹腦、翻轉劈掃、撩掛雲刺、托架抹挑等，
並有單刀看手、雙刀看走、大刀看頂手，劈、撩、斬、刺似猛虎之
説。 

        學習要求：
                無
HELP
        );
        return 1;
}
