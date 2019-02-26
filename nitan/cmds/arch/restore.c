// restore.c
// updated by Lonely for mysql

#include <ansi.h>
#include <localtime.h>
#include <command.h>

inherit F_CLEAN_UP;

protected string get_backup_data_dir(string user, int day);
protected void clear_user_data(object ob);
int     help(object me);

int main(object me, string arg)
{
        int day;
        string user;
        string dir;
        string flogin, fuser;
        string dump_apply;
        string msg;
        object ob, link_ob, temp_ob;
        object item;
        int clear_flag;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (BACKUP_D->is_backuping())
        {
                write("注意：自動備份馬上就要開始工作，現在不能執行恢復操作。\n");
                return 1;
        }

        if (! arg)
                return help(me);

        if (sscanf(arg, "-c %s", arg) || sscanf(arg, "%s -c", arg))
                // 調入該玩家以後清除必要的數據
                clear_flag = 1;
        else
                clear_flag = 0;

        if (sscanf(arg, "%s from %d", user, day) != 2)
        {
                if (sscanf(arg, "%s from last", user) == 1)
                        day = 1;
                else
                if (sscanf(arg, "%s from temp", user) == 1)
                        day = 0;
                else
                if (sscanf(arg, "%s from dump/%s", user, dump_apply) == 2)
                        day = -1;
                else
                {
                        user = arg;
                        day = 1;
                }
        }

        if (day < -1 || day > 7)
        {
                write("沒有這個備份數據區。\n");
                return 1;
        }

        seteuid(getuid());
        if (day == -1)
        {
                // restore from dump
                dir = DUMP_DIR + dump_apply;
                if (dir[strlen(dir) - 1] != '/')
                        dir += "/";
        } else
        if (day == 0)
                // restore from temp
                dir = TEMP_DIR;
        else
                // restore from backup
                dir = get_backup_data_dir(user, day);

        flogin = "login/" + user[0..0] + "/" + user + __SAVE_EXTENSION__;
        fuser  = "user/"  + user[0..0] + "/" + user + __SAVE_EXTENSION__;

        msg = HIM "開始恢復玩家(" + user + ")的備份數據。\n\n" NOR;
        // check the backup data
        if (file_size(dir + flogin) < 0)
        {
                write(sprintf("%s缺少文件：%s，無法恢復。\n", msg, dir + flogin));
                return 1;
        }

        if (file_size(dir + fuser) < 0)
        {
                write(sprintf("%s缺少文件：%s，無法恢復。\n", msg, dir + fuser));
                return 1;
        }

        // remove current user's data
        if (file_size(DATA_DIR + flogin) >= 0 ||
            file_size(DATA_DIR + fuser) >= 0)
        {
                if (dir == TEMP_DIR)
                {
                        msg += "恢復保存在暫存區中的數據。\n";
                } else
                if (file_size(TEMP_DIR + flogin) >= 0 ||
                    file_size(TEMP_DIR + fuser) >= 0)
                {
                        msg += "由於暫存區(/temp/)下面已經存放了玩家"
                               "的數據，因此本次不作暫存。\n";
                } else
                {
                        // move current user's data to /temp/
                        assure_file(TEMP_DIR + flogin);
                        assure_file(TEMP_DIR + fuser);
                        cp(DATA_DIR + flogin, TEMP_DIR + flogin);
                        cp(DATA_DIR + fuser,  TEMP_DIR + fuser);
                        msg += "玩家目前的數據暫時保存到暫存區(/temp/)下。\n";
                }
                rm(DATA_DIR + flogin);
                rm(DATA_DIR + fuser);
                msg += "刪除玩家目前的檔案。\n";
        }

        // after remove, if the data existed ?
        if (file_size(DATA_DIR + flogin) >= 0 ||
            file_size(DATA_DIR + fuser) >= 0)
        {
                write(sprintf("%s沒有能夠成功的刪除玩家現在的檔案(%s)和(%s)。\n"
                       "請先查證然後再執行備份操作。\n",
                       msg, DATA_DIR + flogin, DATA_DIR + fuser));
                return 1;
        }

        // ok. copy the backup data to /data/
        assure_file(DATA_DIR + flogin);
        assure_file(DATA_DIR + fuser);
        cp(dir + flogin, DATA_DIR + flogin);
        cp(dir + fuser,  DATA_DIR + fuser);
        msg += sprintf("從(%s)中複製玩家的檔案數據。\n", dir);

        // success ?
        if (file_size(DATA_DIR + flogin) < 0 ||
            file_size(DATA_DIR + fuser) < 0)
        {
                write(sprintf("%s沒有能夠成功的從(%s)中複製玩家的檔案。\n",
                       msg, dir));
                return 1;
        }
        msg += sprintf("檔案複製成功。\n");
        log_file("backup", sprintf("user %s has been restore by %s from %s.\n",
                                   user, geteuid(me), dir));

        // the player online?
        if (! (ob = find_player(user)))
        {
                write(msg);
                EXAMINE_CMD->main(me, "-u " + user);
                if (objectp(ob = find_player(user)))
                {
                        if (clear_flag)
                        {
                                tell_object(me, HIG "清除了玩家" + ob->name(1) + "的某些相關數據。\n" NOR);
                                clear_user_data(ob);
                        }
                } else
                        tell_object(me, HIG "無法載入該玩家。\n" NOR);
                return 1;
        }

        // restore the object
        tell_object(ob, HIM "\n從磁盤中載入你的數據，並重新設置。\n" NOR);
        set_temp("restore_mysql", 1, ob);
        if (! ob->restore())
        {
                write(sprintf("%s該用户無法讀取備份的數據。\n", msg));
                return 1;
        }

        if( objectp(link_ob=query_temp("link_ob", ob)) )
        {
                set_temp("restore_mysql", 1, link_ob);
                link_ob->restore();
        }

#ifdef DB_SAVE
        if (! DATABASE_D->db_find_user("id", user))
        {
                temp_ob = new(LOGIN_OB);
                set("id", user, temp_ob);
                set_temp("restore_mysql", 1, temp_ob);
                temp_ob->restore();

                DATABASE_D->db_new_player(temp_ob, ob);
        
                if (objectp(ob)) ob->save();
                if (objectp(temp_ob)) 
                {
                        temp_ob->save();
                        destruct(temp_ob);
                }
        }
#endif

        write(msg);

        // re-setup the user
        foreach (item in all_inventory(ob))
        {
                if (item->is_character())
                {
                        tell_object(me, item->name(1) + "從玩家" +
                                        ob->name(1) + "身上脱離。\n");
                        item->move(environment(me), 1);
                } else
                        destruct(item);
        }

        delete_temp("user_setup", ob);
        ob->setup();
        if (! environment(ob))
        {
                tell_object(ob, HIC "\n由於你現在所處的環境不正常，需"
                                "要移動到巫師會客室。\n" NOR);
                ob->move("/d/wizard/guest_room");
                set("startroom", "/d/wizard/guest_room", ob);
        }

        // force look
        tell_object(ob, HIY  "> l\n" NOR);
        catch(ob->force_me("look"));

        // force hp
        tell_object(ob, HIY  "> hp\n" NOR);
        catch(ob->force_me("hp"));

        // force show
        ob->write_prompt();
        tell_object(ob, HIY "check backup data now\n" +
                        HIC "請檢查你目前的狀況是否正確。\n" NOR);
        if (ob != me)
                tell_object(me, HIC "\n玩家已經重新設置。\n\n" NOR);

        if (clear_flag)
        {
                write(HIG "清除了玩家" + ob->name(1) + "的某些相關數據。\n" NOR);
                clear_user_data(ob);
        }
        return 1;
}

// return the directory of the user
// dir/login/?/??? & dir/user/?/??? would be the user's data
protected string get_backup_data_dir(string user, int day)
{
        mixed lt;
        int now;

        lt = localtime(time());
        lt[LT_MON]++;   // the month is from 0..31 so I will adjust it
        now = lt[LT_HOUR] * 100 + lt[LT_MIN];
        if (now > BACKUP_D->query_backup_time())
        {
                // because the o'clock has pass through the backuping
                // time, so the most recently backup data is of today
                day--;
        }

        lt[LT_MDAY] -= day;
        if (lt[LT_MDAY] > 0)
                return sprintf("%s%d-%d-%d/", BACKUP_DIR,
                               lt[LT_YEAR], lt[LT_MON], lt[LT_MDAY]);

        lt[LT_MON]--;
        switch (lt[LT_MON])
        {
        case 2:
                if ((lt[LT_YEAR] % 4) == 0 && (lt[LT_YEAR] % 100) != 0)
                        lt[LT_MDAY] += 29;
                else
                        lt[LT_MDAY] += 28;
                break;

        case 1: case 3: case 5: case 7: case 8: case 10:
                lt[LT_MDAY] += 31;
                break;

        case 4: case 6: case 9: case 11:
                lt[LT_MDAY] += 30;
                break;

        case 0: // last year
                lt[LT_MDAY] += 31;
                lt[LT_MON] = 12;
                lt[LT_YEAR] --;
        }

        return sprintf("%s%d-%d-%d/", BACKUP_DIR,
                       lt[LT_YEAR], lt[LT_MON], lt[LT_MDAY]);
}

protected void clear_user_data(object ob)
{
        delete("private_room", ob);
        delete("can_summon", ob);
        delete("can_whistle", ob);
        delete("couple", ob);
        delete("brothers", ob);
        delete("league", ob);
        delete("bunch", ob);
        delete("invent", ob);
        delete("create", ob);
}

int help(object me)
{
        write(@HELP
指令格式：restore [-c] <玩家ID> from <last | 1..7 | temp | dump>

從備份區恢復一個玩家的數據。其中 last 等效於１，表示從最近一
次的備份中恢復。玩家數據恢復時，當前的數據將被保存到一個暫存
區(如果暫存區空)，如果對玩家恢復的備份不滿意，可以從 temp 中
恢復。玩家的數據恢復時，如果玩家在線上，將執行 restore 操作，
如果玩家此時數據不正常：包括沒有環境或是沒有 setup，將重新更
新玩家。如果玩家不在線上，該命令會自動將玩家調入遊戲。當你處
理完畢必要的數據以後可以將該玩家踢出(kickout)遊戲。

執行玩恢復操作以後應該將玩家的數據從暫存區中清除掉。

系統 SHUTDOWN 或者崩潰以後，所有的存盤數據包括玩家數據將被保
存到 dump 目錄中，這是為了防止系統重新啟動以後出現故障導致數
據受到損失，因此也可以從 dump 中恢復數據。

使用 -c 參數可以在恢復玩家數據以後清除玩家所有相關性的數據。
這是針對那些自殺以後恢復得玩家而言的，由於他們自殺所以所有的
相關性數據都會被清除，恢復以後應該清除他們自身的這些數據，避
免數據不一致。

注意：在備份系統第一次提出提示以後一直到備份完畢的過程中，不
能執行有關恢復玩家數據的操作。

相關指令：cleartemp, clear
HELP );
        return 1;
}