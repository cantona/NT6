// auth.c

#include <ansi.h>

inherit F_CLEAN_UP;

#define SCAN_D  "/adm/daemons/broadcastd"

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        string title, info;
        int delay, times;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        if (! is_root(me) && ! SECURITY_D->valid_grant(me, "(admin)"))
                return notify_fail("你沒有權限訪問安全系統。\n");

        if (! arg)
                return notify_fail("指令：pushmsg + 參數：\n" +
                                   "add 標題 間隔時長(秒) 循環次數 內容 ： 添加PUSHMSG\n" +
                                   "list : 顯示當前廣播\n" +
                                   "del 標題: 刪除指定廣播\n");

        if (arg == "list")
                return SCAN_D->show_push_lish();

        if (sscanf(arg, "del %s", title) == 1)
                return SCAN_D->delete_push_msg(title);

        if (sscanf(arg, "add %s %d %d %s", title, delay, times, info) != 4)
                return notify_fail("指令：pushmsg + 參數：\n" +
                                   "add 標題 間隔時長(秒) 循環次數 內容 ： 添加PUSHMSG\n" +
                                   "list : 顯示當前廣播\n" +
                                   "del 標題: 刪除指定廣播\n");


        // 添加
        return SCAN_D->add_push_msg(title, info, delay, times);
}
