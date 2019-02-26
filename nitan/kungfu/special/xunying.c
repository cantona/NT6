// xunying.c 遁影擒蹤
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "遁影擒蹤" NOR; }

int perform(object me, string skill)
{        
        
        if (me->query("special2/xunying") && ! me->query("thborn/ok"))
        {
                // 2轉後可使用一次
                if (me->query("special2/thborn_xunying"))        
                        return notify_fail("對不起，你在今生已經使用過該絕技，無法再次使用了。\n");
        }
        
                if (me->query("combat_exp") < 2700000)
                        return notify_fail("您的實戰經驗小於270萬，無法施展該技能。\n");
                
        if (me->query_temp("special2/xunying"))
        {
                me->set_skill("count", 300);
                me->set_skill("mathematics", 300);
                me->set("special2/xunying", 1);
                if (me->query("thborn/ok"))
                        me->set("special2/thborn_xunying", 1);
                me->save();
                return notify_fail("你獲得了陰陽八卦及算術三百級。\n");
        }
        else
        {
                me->set_temp("special2/xunying", 1);
        
                      return notify_fail("你在轉生過程中縱觀天象，察覺到了人世\n"
                                                "間的諸多奧祕，眾生百態盡收眼底。此後\n"
                                             "不再受到架力卸招之技的迷惑。轉生後使\n"
                                             "用該絕技可獲得陰陽八卦及算術等級三百\n"
                                             "級，但一生僅能使用一次，如果你決定現\n"
                                             "在使用請再輸入一次 " HIY "special xunying" NOR " 。\n");
       }
}