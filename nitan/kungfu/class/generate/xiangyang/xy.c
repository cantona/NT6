#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        string poision;
        
        // 顯示襄陽戰狀態
        // 根據XYWAR_D->now_status()
        if (! arg)
        {
                return 1;
        }
        
        // 顯示襄陽士兵情況
        if (arg == "soldier")
        {
                if (me->is_busy())return notify_fail("你正忙呢。\n");
                
                if (XYWAR_D->now_status() != 2 && XYWAR_D->now_status() != 3 && ! wizardp(me))
                        return notify_fail("襄陽保衛戰目前還沒有開始，無法查看。\n");
                
                XYWAR_D->show_soldier(me);
                return 1;
        }
        
        // 調動襄陽守軍，只有玩家將領才可以調動
        if (sscanf(arg, "xmove %s", poision))
        {
                if (XYWAR_D->leader_player() != me->query("id") && ! wizardp(me))
                        return notify_fail("對不起，你沒有權利調動襄陽守軍。\n");
                
                XYWAR_D->move_xysoldier(me, poision);
                
                return 1;
        }
                
        // 增派蒙古軍
        // 只有巫師有權利
        if (arg == "add mgb" && wizardp(me))
        {
                
                // 增加蒙古兵時間間隔ADD_MGB_TIME
                /*
                if (time() - last_add_mgb_time < 120)
                {
                        return notify_fail("蒙古兵剛增援過，兵力還調配不過來。\n");
                }
                */
                XYWAR_D->combat_add_soldier();
                return 1;
        }
        
        me->start_busy(2);
        return 1;
}


int help (object me)
{
        write(@HELP


HELP);
        return 1;
}

