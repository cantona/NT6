// by snowcat
// sameip

#include <ansi.h>

inherit F_CLEAN_UP;

string fname(object ob);

nosave object run_user = 0;

int main(object me, string arg)
{
        object who, ob;
        int    i, j, count;
        string *dir, *ppls;
        string name, address;
        string *result;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg)
                return notify_fail("指令格式：sameip <使用者姓名> | <IP 地址>\n");

        if (find_call_out("search_dir") != -1)
        {
                if (run_user && run_user != me)
                        return notify_fail("當前"+query("name", run_user)+
                                           "("+query("id", run_user)+")"+
                                           "正在使用該指令進行查找，請稍候再使用。\n");
                remove_call_out("search_dir");
        }

        seteuid(getuid());
        if (member_array('.', arg) != -1)
        {                
                address = arg;
        } else
        {
                name = arg;
                if (file_size(DATA_DIR + "login/" + name[0..0] + "/"  + name + __SAVE_EXTENSION__) < 0)
                        return notify_fail("沒有這位使用者。\n");

                who = new(LOGIN_OB);
                set("id", name, who);
                if (! who->restore())
                        return notify_fail("沒有這位使用者。\n");

                write(fname(who)+"上次從"+query("last_from", who)+"上線。\n");
                if( !query("last_from", who) )
                        return notify_fail("無法查知該玩家上次上線地點。\n");
                address=query("last_from", who);
                destruct(who);
        }

        write("尋找從 " + address + " 上線的使用者：\n");
        count = 0;
        dir = get_dir(DATA_DIR + "login/");
        i = 0;
        result = ({ });
        call_out("search_dir", 0, count, dir, i, address, me, result);
        write(HIG "現在系統將統計數據，稍後匯報。\n"
              HIG "進度：" + process_bar(0) + "\n");
        me->attach_system();
        run_user = me;
        return 1;
}

void search_dir(int count, string *dir, int i, string address, object me, string *result)
{
        object ob;
        int j;
        string *ppls;
        string name, str, adr, s1, s2, s3, s4;
        string info;

        if (! objectp(me))
        {
                result = 0;
                return;
        }

        if (! me->is_attach_system())
        {
                run_user = 0;
                result = 0;
                return;
        }

        if (i == sizeof(dir))
        {
                info = ESC + "[256D" + ESC + "[K"
                       HIC "\n查找所有玩家的結果如下：\n" NOR WHT;
                for (i = 0; i < sizeof(result); i++)
                {
                        info += result[i];
                        if (i % 20)
                        {
                                message("system", info, me);
                                info = "";
                        }
                }
                info += HIG "共有 " + to_chinese(count) + " 位使用者從這個地址上線。\n\n" NOR;
                message("system", info, me);
                run_user = 0;
                me->detach_system();
                me->write_prompt();
                result = 0;
                return;
        } else
        {
                ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/");
                for(j = 0; j < sizeof(ppls); j++)
                {
                        reset_eval_cost();
                        if (sscanf(ppls[j], "%s.o", str)==1)
                        {
                                ob = new(LOGIN_OB);
                                set("id", str, ob);
                                if (! ob->restore() ||
                                    !(adr=query("last_from", ob)) || 
                                    strsrch(adr, address) == -1)
                                {
                                        destruct(ob);
                                        continue;
                                }

                                info = sprintf("%-14s%-14s%-11s%-6s%s\n",
                                              query("id", ob),
                                              fname(ob),
                                              ctime(query("last_on", ob))[0..10],
                                              ctime(query("last_on", ob))[20..24],
                                              query("last_from", ob));
                                result += ({ info });
                                destruct(ob);
                                count++;
                        }
                }
                i++;
                message("system", ESC + "[1A" + ESC + "[256D"
                                  HIG "進度：" + process_bar(i * 100 / sizeof(dir)) +
                                  "\n" HIR "執行中" NOR "> ", me);
                call_out("search_dir", 0, count, dir, i, address, me, result);
    }
}

string fname(object ob)
{
        string s1, s2;

        s1=query("surname", ob);
        s2=query("purename", ob);
        if (! s1) s1= "";
        if (s2) s1 += s2;
        if (s1 == "") s1 = "無名";
        return s1;
}

int  help(object  me)
{
write(@HELP
指令格式：sameip <使用者姓名> | <IP 地址>

查找所有與使用者用同一地址上線的使用者。
HELP
    );
        return  1;
}