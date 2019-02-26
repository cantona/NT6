// db.c
// created by jjgod

inherit F_CLEAN_UP;

#include "/adm/etc/database.h"
#include <ansi.h>
#include <mudlib.h>

int help(object me);
protected void done_edit(object me, string sql);

int main(object me, string arg)
{
        string sql;
        string msg;
        mixed  ret, res, *arr;
        string db, tb, expr, col;
        int    i, j, n;
        int    cnum, lnum;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        // 無參數則列出服務器中所有數據庫
        if (! arg)
        {
                i = 1;
                msg = sprintf(HIC "%s(" HIW "%s" HIC ")的數據庫列表：\n" NOR
                              HIW "──數據庫名──────表數───\n" NOR,
                              LOCAL_MUD_NAME(), upper_case(INTERMUD_MUD_NAME));

                while (sizeof(ret = DATABASE_D->db_fetch_row("SHOW DATABASES", i)))
                {
                        sql = sprintf("SHOW TABLES FROM %s", ret[0]);
                        msg += sprintf(CYN "   %-18s [ " WHT "%3d" CYN " ]\n" NOR, ret[0], 
                                       DATABASE_D->db_query(sql));
                        i++;
                }
                msg += sprintf(HIW "─────────────────\n" NOR 
                               HIC "本機共有 " HIW "%d" HIC " 個數據庫。" NOR, i - 1);
        }
        // 列出指定遊戲數據庫的數據表(顯示列數量)
        else
        if (arg == "-d" || sscanf(arg, "-d %s", db) && db == DATABASE)
        {
                i = 1;
                db = DATABASE;
                sql = sprintf("SHOW TABLES FROM %s", db);

                if (! intp(DATABASE_D->db_query(sql)))
                        return notify_fail(CYN "沒有 " WHT + db + CYN " 這個數據庫。\n" NOR);

                msg = sprintf(HIC "數據庫(" HIW "%s" HIC ")的數據表：\n" NOR
                              HIW "──數據表名────────────列───行──\n" NOR, db);

                while (sizeof(ret = DATABASE_D->db_fetch_row(sql, i)))
                {
                        res = DATABASE_D->db_query(sprintf("SHOW COLUMNS FROM %s FROM %s", ret[0], db));
                        if (intp(res)) cnum = res;

                        arr = DATABASE_D->db_fetch_row(sprintf("SELECT COUNT(*) FROM %s", ret[0]));
                        if (sizeof(arr)) lnum = arr[0];

                        msg += sprintf(CYN "   %-30s [ " WHT "%2d" CYN " / " WHT "%4d" CYN " ]\n" NOR,
                                       ret[0], cnum, lnum);
                        i++;
                }
                msg += sprintf(HIW "─────────────────────────\n" NOR 
                               HIC "此數據庫共有 " HIW "%d" HIC " 張數據表。" NOR, i - 1);
        }
        // 列出其他數據庫中指定數據表的字段信息
        else
        if (sscanf(arg, "-d %s", db))
        {
                i = 1;
                db = stringp(db) ? db : DATABASE;
                sql = sprintf("SHOW TABLES FROM %s", db);

                if (! intp(DATABASE_D->db_query(sql)))
                        return notify_fail(CYN "沒有 " WHT + db + CYN " 這個數據庫。\n" NOR);

                msg = sprintf(HIC "數據庫(" HIW "%s" HIC ")的數據表：\n" NOR
                              HIW "──數據表名────────────列──\n" NOR, db);

                while (sizeof(ret = DATABASE_D->db_fetch_row(sql, i)))
                {
                        res = DATABASE_D->db_query(sprintf("SHOW COLUMNS FROM %s FROM %s", ret[0], db));
                        if (intp(res)) cnum = res;

                        msg += sprintf(CYN "   %-30s [ " WHT "%2d" CYN " ]\n" NOR,
                                       ret[0], cnum);
                        i++;
                }
                msg += sprintf(HIW "─────────────────────\n" NOR 
                               HIC "此數據庫共有 " HIW "%d" HIC " 張數據表。" NOR, i - 1);
        }
        // 列出遊戲數據庫中指定數據表的字段信息
        else
        if (sscanf(arg, "-t %s", tb))
        {
                i = 1;
                sql = sprintf("SHOW COLUMNS FROM %s", tb);

                if (! intp(DATABASE_D->db_query(sql)))
                        return notify_fail(CYN "沒有 " WHT + tb + CYN " 這個數據表。\n" NOR);

                msg = sprintf(HIC "數據表(" HIW "%s" HIC ")的結構：\n" NOR
                              HIW "──字段名──────────────附加信息──────\n" NOR, tb);

                while (sizeof(ret = DATABASE_D->db_fetch_row(sql, i)))
                {
                        res = DATABASE_D->db_fetch_row(sprintf("DESC %s %s", tb, ret[0]));
                        res -= ({ ret[0] });
                        res = filter_array(res, (: $1 != "" :));

                        msg += sprintf(CYN "   %-24s [ " WHT "%s" CYN " ]\n" NOR, ret[0],
                                       implode(res, CYN " | " WHT));
                        i++;
                }
                msg += sprintf(HIW "─────────────────────────────\n" NOR 
                               HIC "此數據表共有 " HIW "%d" HIC " 個字段。" NOR, i - 1);
        }
        // 按照表達式查詢制定數據表中制定字段的內容
        else
        if (sscanf(arg, "-s %s %s", tb, arg) == 2)
        {
                sql = sprintf("SHOW COLUMNS FROM %s", tb);

                if (! intp(DATABASE_D->db_query(sql)))
                        return notify_fail(CYN "沒有 " WHT + tb + CYN " 這個數據表。\n" NOR);

                // 指定表達式
                if (sscanf(arg, "%s where %s", col, expr) == 2)
                {
                        i = 1;
                        sql = sprintf("SELECT %s FROM %s WHERE %s", col, tb, expr);

                        msg = sprintf(HIC "查詢(" HIW "%s" HIC ")的結果：\n" NOR
                              HIW "──字段名────────────────────────\n" NOR
                              HIC "   %s\n" NOR
                              HIW "───────────────────────查詢結果──\n" NOR,
                              sql, col);

                        while (sizeof(ret = DATABASE_D->db_fetch_row(sql, i)))
                        {
                                msg += sprintf(CYN "   %" + (stringp(ret[0]) ? "s" : "O") + 
                                               "\n" NOR, ret[0]);
                                i++;
                        }
                        msg += sprintf(HIW "─────────────────────────────\n" NOR 
                                       HIC "此次查詢共有 " HIW "%d" HIC " 個符合結果。" NOR, i - 1);
                        if (! (i - 1))
                                return notify_fail(sprintf(CYN "查詢：" WHT "%s" CYN "\n沒有得到任何結果，請檢"
                                                           "查是否無此字段或表達式輸入錯誤。\n" NOR, sql));
                }
                // 不指定表達式
                else
                {
                        col = arg;
                        i = 1;
                        sql = sprintf("SELECT %s FROM %s", col, tb);

                        msg = sprintf(HIC "查詢(" HIW "%s" HIC ")的結果：\n" NOR
                              HIW "──字段名────────────────────────\n" NOR
                              HIC "   %s\n" NOR
                              HIW "───────────────────────查詢結果──\n" NOR,
                              sql, col);

                        while (sizeof(ret = DATABASE_D->db_fetch_row(sql, i)))
                        {
                                msg += sprintf(CYN "   %" + (stringp(ret[0]) ? "s" : "O") + 
                                               "\n" NOR, ret[0]);
                                i++;
                        }
                        msg += sprintf(HIW "─────────────────────────────\n" NOR 
                                       HIC "此次查詢共有 " HIW "%d" HIC " 個符合結果。" NOR, i - 1);
                        if (! (i - 1))
                                return notify_fail(sprintf(CYN "查詢：" WHT "%s" CYN "\n沒有得到任何結果，請檢"
                                                           "查是否無此字段或者數據表為空。\n" NOR, sql));
                }
        }
        // 查詢指定一個列的所有信息
        // 向後查詢
        else
        if (sscanf(arg, "-n %s where %s", tb, expr) == 2)
        {
                i = 1;

                // 準備要查詢的列號
                n=query("db_last_query/"+tb, me)+1;

                // 準備列信息
                sql = sprintf("SHOW COLUMNS FROM %s", tb);
                if (! intp(DATABASE_D->db_query(sql)))
                        return notify_fail(CYN "沒有 " WHT + tb + CYN " 這個數據表。\n" NOR);

                arr = ({ });
                while (sizeof(res = DATABASE_D->db_fetch_row(sql, i)))
                {
                        arr += ({ res[0] });
                        i++;
                }
                // 準備行信息
                sql = sprintf("SELECT * FROM %s WHERE %s", tb, expr);
                j = DATABASE_D->db_query(sql);
                n = j < n ? j : n;
                ret = DATABASE_D->db_fetch_row(sql, n);

                // 顯示信息
                msg = sprintf(HIC "查詢(" HIW "%s" HIC ")的第 " HIW "%d" HIC " 行結果：\n" NOR
                              HIW "──字段名────────────字段內容────────\n" NOR,
                              sql, n);
                cnum = sizeof(arr);

                if (! cnum || ! sizeof(ret))
                        return notify_fail(sprintf(CYN "查詢：" WHT "%s" CYN "\n沒有得到任何結果，請檢"
                                                   "查是否無此字段或表達式輸入錯誤。\n" NOR, sql));
                for (i = 0; i < cnum; i++)
                        msg += sprintf(CYN "  %-30s " WHT "%O\n" NOR, arr[i], ret[i]);

                msg += sprintf(HIW "─────────────────────────────\n" NOR 
                               HIC "此列共有 " HIW "%d" HIC " 個字段。" NOR, cnum);

                // 準備下一次查詢
                set("db_last_query/"+tb, n, me);
        }
        // 向前查詢
        else
        if (sscanf(arg, "-f %s where %s", tb, expr) == 2)
        {
                i = 1;
                n=query("db_last_query/"+tb, me)-1;

                // 準備列信息
                sql = sprintf("SHOW COLUMNS FROM %s", tb);
                if (! intp(DATABASE_D->db_query(sql)))
                        return notify_fail(CYN "沒有 " WHT + tb + CYN " 這個數據表。\n" NOR);

                arr = ({ });
                while (sizeof(res = DATABASE_D->db_fetch_row(sql, i)))
                {
                        arr += ({ res[0] });
                        i++;
                }
                // 準備行信息
                sql = sprintf("SELECT * FROM %s WHERE %s", tb, expr);
                n = n < 1 ? 1 : n;
                ret = DATABASE_D->db_fetch_row(sql, n);

                // 顯示信息
                msg = sprintf(HIC "查詢(" HIW "%s" HIC ")的第 " HIW "%d" HIC " 行結果：\n" NOR
                              HIW "──字段名────────────字段內容────────\n" NOR,
                              sql, n);
                cnum = sizeof(arr);

                if (! cnum || ! sizeof(ret))
                        return notify_fail(sprintf(CYN "查詢：" WHT "%s" CYN "\n沒有得到任何結果，請檢"
                                                   "查是否無此字段或表達式輸入錯誤。\n" NOR, sql));
                for (i = 0; i < cnum; i++)
                        msg += sprintf(CYN "  %-30s " WHT "%O\n" NOR, arr[i], ret[i]);

                msg += sprintf(HIW "─────────────────────────────\n" NOR 
                               HIC "此列共有 " HIW "%d" HIC " 個字段。" NOR, cnum);

                // 準備下一次查詢
                set("db_last_query/"+tb, n, me);
        }
        // 執行 SQL 語句
        else
        if (arg == "-e" || sscanf(arg, "-e %s", sql))
        {
                if (! stringp(sql) || sql == "")
                {
                        write(HIC "請輸入你要執行的語句：\n" NOR);
                        me->edit((: call_other, __FILE__, "done_edit", me :));
                } else
                done_edit(me, sql);
        }

        else return help(me);
        if (stringp(msg) && msg != "") me->start_more(msg);
        return 1;
}

protected void done_edit(object me, string sql)
{
        mixed ret, *res;
        string msg;

        if (! sql || sql == "")
        {
                tell_object(me, HIC "你取消了輸入。\n" NOR);
                return;
        }
        if (sql[<1..<0] == "\n") sql = sql[0..<2];
        msg = sprintf(HIC "語句(" HIW "%s" HIC ")的執行結果：\n" 
                      HIW "────────────────────────────────"
                      "───────\n" NOR, sql);
        if (! ret = DATABASE_D->db_query(sql))
        {
                msg += CYN "沒有得到任何可用信息。\n" HIW "────────────────"
                       "───────────────────────\n" NOR;
        } else
        if (stringp(ret))
        {
                msg += sprintf(HIR "錯誤信息：" NOR WHT "%s\n" NOR
                               HIW "────────────────────────────"
                               "───────────\n" NOR, ret);
        } else
        {
                res = DATABASE_D->db_all_query(sql);
                msg += sprintf(WHT "%O\n" NOR
                               HIW "────────────────────────────"
                               "───────────\n" NOR, res);
        }
        tell_object(me, msg);
        return;
}

int help(object me)
{
        write(@HELP
指令格式: db [ -d [ 數據庫名 ] ] |
             [ -t <數據表名> ] |
             [ -s <數據表名> <字段名> [ where <表達式> ] ] |
             [ -n <數據表名> where <表達式> ] |
             [ -f <數據表名> where <表達式> ]
             [ -e [ <SQL 語句> ] ]

此指令用於遊戲數據庫的管理。你可以使用 -d 參數列出數據庫的
內容，-t 列出本遊戲數據庫的數據表的內容。-s 參數用於在數據
庫裏符合指定表達式的行，若不指定表達式，則顯示此表中所有的
列。 考慮到 mud 中顯示的問題，這裏必須指定字段名，也就是隻
能同時顯示所有結果一個字段的信息。如果你想獲得一個結果所有
字段的信息，可以使用 -n 參數向後查詢或者 -f 參數向前查詢。

由於遊戲的數據庫連接的效率問題，本指令不提供對非遊戲數據庫
的操作。
HELP);
        return 1;
}