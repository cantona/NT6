
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "唇槍舌劍" NOR; }

int perform(object me, string skill)
{
        return notify_fail("你擁有異人之口才，能夠混淆是非，顛倒黑白。于炎黃黑店、普通NPC商店購買\n"
                           "物品可獲得市價9折的優惠。同時，具備八面玲瓏的相關特效。不需要運用。\n");
}

