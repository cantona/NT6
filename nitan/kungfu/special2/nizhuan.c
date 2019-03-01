
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "逆轉乾坤" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你天生受到上天的青睞，擁有逆轉乾坤之神力，具備以下特殊能力：\n"
                           "命中提升：+10%\n"
                           "研究次數：+10 次\n"
                           "內力上限：+500\n"
                           "精力上限：+500\n"
                           "其他特效：如有[仙風道骨]技能可再額外提升研究次數10次\n"
                           "不需要運用。\n");
}

