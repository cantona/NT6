#include <ansi.h>

#ifndef GOODS_D
#define GOODS_D          "/adm/daemons/goodsd"
#endif

int paying;
int help(object me);

int main(object me, string arg)
{
        string str1, str2;
        string info;
        object tar;
        string me_id, tar_id;
        int amount;

        if( time()-query_temp("last_member", me)<3 && 
            arg != "?" && ! wizardp(me))
                return notify_fail("系統忙，請稍後再試！\n");

        if (arg != "?" && ! wizardp(me))
                set_temp("last_member", time(), me);

        // 僅允許非會員使用member ?, member ??, member stats, member show goods指令
        if( !MEMBER_D->is_member(query("id", me)) )
        {
                if (! arg)return help(me);
                if (arg == "?")return help(me);
                if (arg == "??")return help(me);
                if (arg == "stats")
                        return MEMBER_D->show_all_members(0);

                if (sscanf(arg, "%s %s", str1, str2) != 2)
                        return 0;

                if (str1 != "look" && (str1 != "show" || str2 != "goods"))
                        return 0;
        }

        if (! arg)
        {
                MEMBER_D->show_member_info(me, "info");
                return 1;
        }

        if (arg == "?") return help(me);
        if (arg == "??") return help(me);
        if (arg == "stats")
        {
                return MEMBER_D->show_all_members(0);
        }

        if (sscanf(arg, "%s %s", str1, str2) != 2)
                return help(me);

        switch(str1)
        {
        case "show":
                if (str2 == "info")
                {
                        MEMBER_D->show_member_info(me, "info");
                        return 1;
                }
                else if (str2 == "payinfo")
                {
                        MEMBER_D->show_member_info(me, "payinfo");
                        return 1;
                }
                else if (str2 == "buyinfo")
                {
                        MEMBER_D->show_member_info(me, "buyinfo");
                        return 1;
                }
                else if (str2 == "goods" || str2 == "all")
                {
                        MEMBER_D->show_member_info(me, "goods");
                        return 1;
                }
                else if (str2 == "zhuaninfo")
                {
                        MEMBER_D->show_member_info(me, "transferinfo");
                        return 1;
                }
                else return help(me);

        case "look":
                return GOODS_D->do_look(me, str2);

        case "buy":
                if (! GOODS_D->buy_goods(me, str2))
                {
                        write("購買失敗！\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        case "zhuan":
                if (sscanf(str2, "%d to %s", amount, tar_id) != 2)
                        return help(me);

                me_id=query("id", me);

                if (me_id == tar_id)
                        return notify_fail("你白痴啊，給自己轉帳！\n");

                if (amount < 1 || amount > 100000)
                        return notify_fail("每次轉帳的單位必須在 1 至 100000 之間！\n");

                if (! MEMBER_D->db_transfer_member(me_id, tar_id, amount))
                {
                        write("轉帳失敗！\n");
                        return 1;
                }
                write("Successful!\n");
                return 1;

        case "check":
                if (wiz_level(me) < 4)
                        return help(me);

                if (sscanf(str2, "%s %s", tar_id, info) != 2)
                        tar_id = str2;

                // 檢查對方是否為會員
                if (! MEMBER_D->is_member(tar_id))
                        return notify_fail("目標為非會員，無法查詢！\n");

                tar = UPDATE_D->global_find_player(tar_id);
                if (! objectp(tar))
                        return notify_fail("沒有這個玩家！\n");

                if( !info ) info = "info";
                MEMBER_D->show_member_info(tar, info);

                UPDATE_D->global_destruct_player(tar, 1);

                return 1;

        case "remove":
                if (wiz_level(me) < 5)
                        return help(me);

                if (! MEMBER_D->db_remove_member(str2))
                {
                        write("刪除會員失敗！\n");
                        return 1;
                }
                write("OK.\n");
                return 1;

        default:
                return help(me);
        }

        return 1;
}

int help (object me)
{
        write(WHT "──────────────────────────────────

" HIM "輸入指令： member show info                     顯示會員系統面板界面
輸入指令： member show payinfo                  顯示歷史充值交費信息
輸入指令： member show buyinfo                  顯示歷史購買物品信息
輸入指令： member show zhuaninfo                顯示歷史轉帳記錄信息
輸入指令： member show goods                    顯示王者商店出售物品
輸入指令： member check <id>                    巫師指令檢查會員信息
輸入指令： member stats                         列出所有會員名單信息
輸入指令： member zhuan <amount> to <id>        轉帳王者幣給其他的ID

" WHT "──────────────────────────────────
" HIC "淘寶沖值鏈接地址:
" HIR "http://shop33371514.taobao.com\n
" HIG "相關參考文件：help ntstore, help member\n" NOR);

        return 1;
}