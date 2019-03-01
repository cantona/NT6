
#include <ansi.h>

#ifndef GOODS_D
#define GOODS_D          "/adm/daemons/goods_honord"
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
                if( !GOODS_D->exchange_goods(me, str2))
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

        money = query("honors", me);

        write(HIY "□ 您目前的榮譽為 " + money + " (NT)
" WHT "──────────────────────────────────

" HIM "輸入指令：    rystore show all                  查看所有商城的貨物
輸入指令：    rystore exchange <代號>           兌換指定代號的商品

" WHT "<代號>  ：    可用物品的 name 或 編號
" WHT "──────────────────────────────────\n" NOR);

        return 1;
}

