// mktitle.c

#include <ansi.h>

inherit F_CLEAN_UP;

protected int   create_title(string arg);
protected int   delete_title(string arg);
protected int   grant_title(string arg);
protected int   replace_title(string arg);
protected int   set_title(string arg);
protected int   list_title();
protected mixed check_title(string arg);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;
        string sw;

        if (! arg)
        {
                if( !query("title", me) )
                        write("你現在並沒有任何稱號。\n");
                else
                        write("你現在的江湖稱號："+query("title", me)+"\n");
                        if( stringp(query_temp("title", me)) )
                                write("遊戲賦予你的特殊稱號："+query_temp("title", me)+"\n");
                return 1;
        }

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (arg == "-l")
                return list_title();

        if (sscanf(arg, "%s %s", sw, arg) != 2)
                return notify_fail("請參見 help title 獲得該命令的使用方法。\n");

        switch (sw)
        {
        case "-c": return create_title(arg);  break;
        case "-d": return delete_title(arg);  break;
        case "-g": return grant_title(arg);   break;
        case "-r": return replace_title(arg); break;
        case "-s": return set_title(arg);     break;
        case "-l": return list_title();       break;
        default:   return notify_fail("參數錯誤。\n");
        }
}

// 創建稱號
protected int create_title(string arg)
{
        int n = 1;
        mixed ts;

        sscanf(arg, "%s %d", arg, n);
        ts = UPDATE_D->query_title_base();
        if (! arrayp(ts)) ts = ({ });
        if (n + sizeof(ts) >= 100)
                return notify_fail("系統中最多隻能有一百個稱號，所以請你考慮先取消一些。\n");

        if (! stringp(arg = check_title(arg)))
                return 0;

        write("創建了" + chinese_number(n) + "個稱號：" + arg + "\n");
        while (n--)
                ts += ({ ({ arg, 0 }) });
        UPDATE_D->set_title_base(ts);
        UPDATE_D->save();
        return 1;
}

// 刪除稱號
protected int delete_title(string arg)
{
        mixed ts;
        mixed item;
        mixed ds;
        object ob;
        int n;

        ts = UPDATE_D->query_title_base();
        if (! arrayp(ts))
                return notify_fail("目前遊戲中並沒有任何特殊稱號。\n");

        if (sscanf(arg, "%d", n))
        {
                if (n < 1 || n > sizeof(ts))
                        return notify_fail("稱號的代號是從 1 到 " +
                                           sizeof(ts) + " ，請輸入有效的代號。\n");

                n--;
                if (stringp(ts[n][1]) && wiz_level(ts[n][1]) > wiz_level(this_player()))
                        return notify_fail("你沒有權限刪除 " + ts[n][1] +
                                           " 擁有的稱號。\n");

                if (stringp(ts[n][1]) && objectp(ob = find_player(ts[n][1])))
                {
                        delete_temp("title", ob);
                        delete("granted_title", ob);
                }

                ds = ts[0..n - 1] + ts[n + 1..<1];
                UPDATE_D->set_title_base(ds);
                UPDATE_D->save();
                write("去掉了第 " + (n + 1) + " 個稱號。\n");
                return 1;
        }

        if (! stringp(arg = check_title(arg)))
                return notify_fail("目前遊戲中並沒有這個稱號。\n");;

        arg = filter_color(arg);

        ds = allocate(sizeof(ts));
        n = 0;
        foreach (item in ts)
        {
                if (! arrayp(item) || sizeof(item) != 2)
                        continue;

                if (filter_color(item[0]) == arg &&
                    (! stringp(item[1]) || wiz_level(item[1]) < wiz_level(this_player())))
                {
                        if (stringp(item[1]) && objectp(ob = find_player(item[1])))
                        {
                                delete_temp("title", ob);
                                delete("granted_title", ob);
                        }
                        continue;
                }

                ds[n++] = item;
        }
        ds = ds[0..n - 1];
        UPDATE_D->set_title_base(ds);
        UPDATE_D->save();
        write("去掉了稱號：" + arg + "。\n");

        return 1;
}

// 更換稱號
protected int replace_title(string arg)
{
        string new_title;
        mixed ts;
        mixed item;
        object ob;
        int n;

        if (sscanf(arg, "%s %s", arg, new_title) != 2)
                return notify_fail("你打算把這些稱號修改成什麼？\n");

        if (! stringp(new_title = check_title(new_title)))
                return 0;

        ts = UPDATE_D->query_title_base();
        if (! arrayp(ts))
                return notify_fail("目前遊戲中並沒有任何特殊稱號。\n");

        if (sscanf(arg, "%d", n))
        {
                if (n < 1 || n > sizeof(ts))
                        return notify_fail("稱號的代號是從 1 到 " +
                                           sizeof(ts) + " ，請輸入有效的代號。\n");

                n--;
                if (! stringp(ts[n][1]) || wiz_level(ts[n][1]) <= wiz_level(this_player()))
                {
                        // 可以修改這個稱號
                        ts[n][0] = new_title;
                        if (stringp(ts[n][1]) &&
                            objectp(ob = find_player(ts[n][1])))
                                set_temp("title", new_title, ob);
                } else
                        return notify_fail("你沒有權限修改 " + ts[n][1] + " 所擁有的稱號。\n");

                UPDATE_D->set_title_base(ts);
                UPDATE_D->save();
                write("修改了第 " + (n + 1) + " 個稱號。\n");
                return 1;
        }

        if (! stringp(arg = check_title(arg)))
                return notify_fail("目前遊戲中並沒有這個稱號。\n");;

        n = 0;
        arg = filter_color(arg);
        foreach (item in ts)
        {
                if (! arrayp(item) || sizeof(item) != 2)
                        continue;

                if (filter_color(item[0]) == arg)
                {
                        if (! stringp(item[1]) || wiz_level(item[1]) <= wiz_level(this_player()))
                        {
                                // 可以修改這個稱號
                                n++;
                                item[0] = new_title;
                                if (stringp(item[1]) && objectp(ob = find_player(item[1])))
                                        set_temp("title", new_title, ob);
                        }
                        continue;
                }
        }

        if (! n)
                return notify_fail("目前遊戲中並沒有可以讓你修改的稱號。\n");

        UPDATE_D->set_title_base(ts);
        UPDATE_D->save();
        write("修改稱號“" + arg + "”為”" + new_title + "”。\n");

        return 1;
}

// 設置稱號
protected int set_title(string arg)
{
        string user;
        object ob;

        if (sscanf(arg, "%s %s", user, arg) != 2)
                return notify_fail("你要為誰設置什麼稱號？\n");

        if (! objectp(ob = find_player(user)))
                return notify_fail("這個玩家不在遊戲中，不能設定稱號。\n");

        if (! stringp(arg = check_title(arg)))
                return 0;

        if (wiz_level(this_player()) < wiz_level(ob))
                return notify_fail("你不能為" + ob->name(1) + "設定稱號。\n");

        set("title", arg, ob);
        write("為" + ob->name(1) + "設定了稱號。\n");
        return 1;
}

// 授予稱號
protected int grant_title(string arg)
{
        string user;
        mixed ts;
        mixed item;
        object nob;
        object ob;
        int i;

        if (sscanf(arg, "%s none", user) == 1)
        {
                // 清除他原先的 title
                write(UPDATE_D->clear_user_data(user, "title"));
                return 1;
        }

        if (sscanf(arg, "%s %d", user, i) != 2)
                return notify_fail("授予稱號你必須指定玩家和稱號的代號。\n");

        ts = UPDATE_D->query_title_base();
        if (i < 1 || i > sizeof(ts))
                return notify_fail("稱號的代號是從 1 到 " +
                                   sizeof(ts) + " ，請輸入有效的代號。\n");
        i--;
        item = ts[i];

        if (! objectp(nob = UPDATE_D->global_find_player(user)))
                return notify_fail("你只能授予稱號給已經註冊的玩家。\n");

        if (item[1] == user)
        {
                notify_fail(nob->name(1) + "的稱號目前正是這個。\n");
                UPDATE_D->global_destruct_player(nob);
                return 0;
        }

        if (wiz_level(this_player()) < wiz_level(nob))
        {
                notify_fail("你不能為" + nob->name(1) + "設定稱號。\n");
                UPDATE_D->global_destruct_player(nob);
                return 0;
        }

        // 清除他原先的 title
        UPDATE_D->remove_title(nob);

        if (stringp(item[1]) && objectp(ob = find_player(item[1])))
        {
                // 恢復這個玩家的原先稱號
                delete_temp("title", ob);
                delete("granted_title", ob);
        }

        // 重新設置系統的 title 記錄
        item[1] = user;
        ts[i] = item;

        // 重新設置玩家得 title
        set_temp("title", item[0], nob);
        set("granted_title", 1, nob);
        nob->save();

        UPDATE_D->set_title_base(ts);
        UPDATE_D->save();
        write("為" + nob->name(1) + "授予了“" + item[0] + "”的稱號。\n");
        UPDATE_D->global_destruct_player(nob);

        return 1;
}

protected int list_title()
{
        mixed ts;
        string str;
        mixed item;
        int i;

        ts = UPDATE_D->query_title_base();
        if (! arrayp(ts) || sizeof(ts) < 1)
                return notify_fail("目前遊戲中沒有任何特殊稱號。\n");

        i = 1;
        str = "目前系統中的特殊稱號有 " CYN + sizeof(ts) + NOR " 個：\n";
        foreach (item in ts)
        {
                str += sprintf("%3d. %-" + (30 + color_len(item[0])) + "s%s\n",
                               i, item[0], item[1] ? item[1] : "");
                i++;
        }
        this_player()->start_more(str);

        return 1;
}

protected mixed check_title(string arg)
{
        arg = replace_string(arg, "$BLK$", BLK);
        arg = replace_string(arg, "$RED$", RED);
        arg = replace_string(arg, "$GRN$", GRN);
        arg = replace_string(arg, "$YEL$", YEL);
        arg = replace_string(arg, "$BLU$", BLU);
        arg = replace_string(arg, "$MAG$", MAG);
        arg = replace_string(arg, "$CYN$", CYN);
        arg = replace_string(arg, "$WHT$", WHT);
        arg = replace_string(arg, "$HIR$", HIR);
        arg = replace_string(arg, "$HIG$", HIG);
        arg = replace_string(arg, "$HIY$", HIY);
        arg = replace_string(arg, "$HIB$", HIB);
        arg = replace_string(arg, "$HIM$", HIM);
        arg = replace_string(arg, "$HIC$", HIC);
        arg = replace_string(arg, "$HIW$", HIW);
        arg = replace_string(arg, "$NOR$", NOR);

        if (strlen(filter_color(arg)) > 30 || strlen(arg) > 100)
                return notify_fail("這個外號太長了，為了節約資源，請你重新設定。\n");

        return arg + NOR;
}

int help(object me)
{
        write(@HELP
指令格式 : title -c <稱號> [<數量>]
           title -d <稱號代碼> | <稱號>
           title -g <sb> <稱號代碼> | <none>
           title -r <稱號代碼> | <稱號> <新稱號>
           title -s <玩家> <新稱號>
           title -l
 
這個指令可以讓你為某人取一個響亮的頭銜，但是隻有巫
師才可以使用，你如果希望在外號中使用 ANSI 的控制字
元改變顏色，可以用以下的控制字串：

$BLK$ - 黑色                $NOR$ - 恢復正常顏色
$RED$ - 紅色                $HIR$ - 亮紅色
$GRN$ - 綠色                $HIG$ - 亮綠色
$YEL$ - 土黃色                $HIY$ - 黃色
$BLU$ - 深藍色                $HIB$ - 藍色
$MAG$ - 淺紫色                $HIM$ - 粉紅色
$CYN$ - 藍綠色                $HIC$ - 天青色
$WHT$ - 淺灰色                $HIW$ - 白色
 
其中系統自動會在字串尾端加一個 $NOR$。

授予稱號可以使用 -g 參數。授予前首先需要創建稱號：使用 -c 參
數可以在遊戲中創建一個或多個稱號。使用 -d 可以去掉這些稱號。
而 -l 參數則能夠列出所有這些稱號和目前的授予情況。使用 -r 參
數可以將目前的某些稱號更換描述，而 -s 參數則可以設置玩家的原
始稱號：注意，這個稱號在拜師或者是某些場合下可能會被修改。

比如想授予某個玩家“東邪”這個稱號可以：
title -c $HIY$東邪
title -l 查看到“東邪”這個稱號的代號是2。
title -g player 2
倘若對“東邪”這個稱號不滿意，可以：
title -r 東邪 西毒
將這個稱號的名字更換。
如果需要剝奪這個稱號可以：
title -g player none

只有需要永久保留的 title 才使用 title -c 創建然後授予玩家，
一般修改 title 應該使用 title -s <玩家> <稱號> 以節約資源。

HELP );
        return 1;
}