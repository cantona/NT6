// dian.c 點石成金
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIC "點石成金" NOR; }

void remove_effect(object me, int amount);

int perform(object me, string skill)
{
        int i;

        if (time() - me->query("special2/dian") < 86400)
                return notify_fail("點石成金一天只能施展一次！\n");

        message_vision(HIY "$N" HIY "施展出點石成金只術，凌空虛點幾下，剎那間金光閃閃，\n"
                       "無數黃金從天而下 ……！\n" NOR, me);
 
        i = 1600 + random(801);

        tell_object(me, HIG "你施展點石成金之術獲得了 " + chinese_number(i) + " 黃金，已存入銀庫。\n" NOR);
 
        me->add("stocks/balance", i);

        me->set("special2/dian", time());

        log_file("static/special2", sprintf("%s(%s) 施展點石成金 at %s\n", 
                                    me->name(),
                                    me->query("id"),
                                    ctime(time())));
        me->save();

        return 1;
}
