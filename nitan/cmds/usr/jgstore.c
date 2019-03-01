#include <ansi.h>

#ifndef GOODS_D
#define GOODS_D          "/adm/daemons/goods_jungongd"
#endif

int help(object me);
int main(object me, string arg)
{
        string str1, str2;
        object tar;
        string me_id, tar_id;
        int amount;

        if( !arg || arg == "") return help(me);
        if( time()-query_temp("last_member", me)<3 )
                return notify_fail("系統忙，請稍後再試！\n");

        if( !wizardp(me) )
                set_temp("last_member", time(), me);

        if( sscanf(arg, "%s %s", str1, str2) != 2 )
                return help(me);

        switch(str1)
        {
        case "show":
                return GOODS_D->show_goods(me, str2);

        case "exchange":
                // 防止注冊id刷物品
                /*
                if( query("combat_exp", me) < 1000000 && !MEMBER_D->is_valid_member(me) )
                        return notify_fail("你暫時還沒有資格將軍功兌換為物品！\n");
                */ 
                if( sscanf(str2, "%s %d", str2, amount) != 2 )
                        amount = 1;
                
                if( amount > 100 ) amount = 100;
                if( amount < 1 ) amount = 1;        
                if( !GOODS_D->exchange_goods(me, str2, amount))
                {
                        write("兌換失敗！\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        default:
                return help(me);
        }

        return 1;
}

int help (object me)
{
        int money;

        money = query("jungong", me);

        write(HIY "□ 您目前的軍功為 " + money + " (NT)
" WHT "──────────────────────────────────

" HIM "輸入指令：    jgstore show all                  查看所有商城的貨物
輸入指令：    jgstore exchange <代號> <數量>    兌換指定代號的商品

" WHT "<代號>  ：    可用物品的 name 或 編號
" WHT "──────────────────────────────────\n" NOR);

        return 1;
}

