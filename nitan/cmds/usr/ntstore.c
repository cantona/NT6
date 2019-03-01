#include <ansi.h>

#ifndef GOODS_D
#define GOODS_D          "/adm/daemons/goodsd"
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

        case "look":
                return GOODS_D->do_look(me, str2);

        case "buy":
                if( !GOODS_D->buy_goods(me, str2))
                {
                        write("購買失敗！\n");
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
        int money, buyvalue;

        money = MEMBER_D->db_query_member(me, "money");
        buyvalue = MEMBER_D->db_query_member(me, "buyvalue");

        write(HIY "□ 您目前的王者幣為 " + money + " (NT)
" WHT "──────────────────────────────────

" HIM "輸入指令：    ntstore show all                  查看所有商城的貨物
輸入指令：    ntstore show object               顯示所有商城物品類
輸入指令：    ntstore show pill                 顯示所有商城丹藥類
輸入指令：    ntstore show special              顯示所有商城特技類
輸入指令：    ntstore show story                顯示所有商城故事類
輸入指令：    ntstore show symbol               顯示所有商城的符類
輸入指令：    ntstore show enchase              顯示所有商城鑲嵌類
輸入指令：    ntstore show prop                 顯示所有商城裝備類
輸入指令：    ntstore show other                顯示所有商城其他類
輸入指令：    ntstore show srv                  顯示所有商城服務類
輸入指令：    ntstore buy <代號>                購買指定代號的商品
輸入指令：    ntstore look <代號>               查看指定物品的屬性

" WHT "<代號>  ：    可用物品的 name 或 id 或 編號
" WHT "──────────────────────────────────
" HIC "淘寶沖值鏈接地址: " HIR "http://shop61698067.taobao.com\n
" HIY "您總共在遊戲商城消費 " + buyvalue + " (NT)。

" HIG "相關參考文件：help member\n\n" NOR);

        return 1;
}