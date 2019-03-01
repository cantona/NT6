
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "怒氣沖霄" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你前世乃是憤怒非常的饕餮神獸，轉世後擁有常人無法比擬的怒氣。該項技能可以使"
                           "你的加怒上限提高200%，且擁有該技能後加怒(jianu)特效不再受到天性的影響。不需要運用。\n");
}

