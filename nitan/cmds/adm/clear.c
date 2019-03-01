// clear.c

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        string target;
        object obj;
        object *obs;
        string ob_name;
        int remove_flag;

        if (! SECURITY_D->valid_grant(me, "(admin)"))
                return 0;

        seteuid(getuid(me));

        if (! arg) return notify_fail("指令格式 : clear [-u] <物件之名"
                                      "稱或檔名> | <玩家ID> <分項>\n" );

        if (sscanf(arg, "-u %s", arg) == 1)
        {
                if (sscanf(arg, "%s %s", target, arg) != 2)
                {
                        write("你必須指明清除用戶的什麼數據。\n");
                        return 1;
                }

                // clear the user data
                write ("清除用戶(" + target + ")的數據：" +
                       UPDATE_D->clear_user_data(target, arg));
                return 1;
        }

        if (arg == "-u")
        {
                help(me);
                return 1;
        }

        // check the remove flag
        remove_flag = sscanf(arg, "-remove %s", arg);

        target = arg;
        obj = find_object(target);
        if ((! obj  || userp(obj)) && file_size(target + ".c") >0 )
                catch(obj = load_object(target));
        if (! obj || userp(obj)) obj = present(target, me);
        if (! obj || userp(obj)) obj = present(target, environment(me));
        if (! obj || userp(obj)) obj = find_object(resolve_path(query("cwd", me), target));
        if (! obj || userp(obj)) catch(obj = load_object(resolve_path(query("cwd", me), target)));
        if (obj && ! userp(obj))
        {
                message_vision(sprintf("$N將物件<%O>連同存盤記錄一起"
                                       "徹底的摧毀了。\n", obj), me);
                if (! clonep(obj))
                {
                        obs = filter_array(all_inventory(obj), (: userp :));
                        obs->move(VOID_OB, 1);
                } else
                        obs = 0;

                target = base_name(obj);

                if (! DBASE_D->clear_object(obj))
                        write ("你沒有能夠成功的摧毀物件和記錄。\n");
                else
                {
                        if (remove_flag)
                        {
                                seteuid(getuid());
                                if (rm(target + ".c") == 1)
                                        write("文件 " + target + ".c 已經成功刪除。\n");
                                else
                                        write("刪除文件 " + target + ".c 失敗。\n");
                        } else
                        if (arrayp(obs) && sizeof(obs))
                                obs->move(target, 1);
                        write("Ok.\n");
                }
        } else
        {
                write("你試圖從數據庫中清除條目(" + target + ")的記錄。\n");
                if (! DBASE_D->clear_object(target))
                        write ("你沒有能夠成功的清除記錄。\n");
                else
                        write("Ok.\n");
        }

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : clear -u <玩家ID> <分項>
                 [-remove] <物件之名稱或檔名>

利用此一指令可將一個物件(object)連同它的存盤記錄一起清除，注
意：這裡的存盤記錄指的是數據保存在 DBASE_D 中的那些對象， 如
果記錄是保存成單獨的文件，則它們的存盤記錄不會受到任何影響，
這個命令是提供給巫師對受到損傷的對象進行數據修復時使用的。

如果使用參數 -u，則表示是要清除一個玩家對 MUD 中的對象數據，
比如說住房的信息就可以通過該命令清除。即將指定的玩家的住房拆
毀。

分項包括：all      所有數據
          board    留言版
          couple   婚配
          item     道具
          name     姓名
          room     房屋
          brothers 結義
          league   聯盟
          title    稱號

如果使用了 -remove 參數， 表示清除物件的存盤記錄以後刪除這個
文件。這個參數需要謹慎使用。

參考資料： dest，query
HELP );
        return 1;
}
