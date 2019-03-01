// examine.c
// created by doing

#include <ansi.h>

inherit F_CLEAN_UP;

// 檢查方式（手工檢查則設置成為 EXAMINE_ALL）
#define        EXAMINE_ALL        0
#define        EXAMINE_LOGINED        1

protected string fname(object ob);
protected string examine_player(string name, int copy_user, int type, int last_touched);
protected string is_illegal(object ob, int update);

nosave int total_gold = 0;

void create() { seteuid(getuid()); }

public void search_dir(object me, int type);

int main(object me, string arg)
{
        int i;
        int copy_user;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (! arg)
                return notify_fail("指令格式：examine [-u] <玩家ID> | -all\n");

        if (! sscanf(arg, "-u %s", arg))
                copy_user = 0;
        else
                copy_user = 1;

        if (arg != "-all")
        {
                string r;
                r = examine_player(arg, copy_user, EXAMINE_ALL, 0);
                if (! r) r = sprintf("這位玩家(%s)的數據沒有異常。\n", arg);
                write("檢查結果：" + r);
                return 1;
        }

        message_system("系統進行數據處理中，請耐心等候...\n");
        write(HIG "現在系統將檢查所有玩家，稍後匯報。\n"
              HIG "進度：" + process_bar(0) + "\n");
        if (me)
        {
                me->attach_system();
                me->write_prompt();
        }
        search_dir(me, 0);
        return 1;
}

void search_dir(object me, int type)
{
        string *dir;
        string *result;
        string name;
        string info;
        mixed *ppls;
        int count;
        int total;
        int i;
        int j;

        if (! is_root(previous_object()))
                return 0;

        // Reset total gold counter
        total_gold =0;

        // Start examine all players
        log_file("examine", "SYSTEM start examine all player on " +
                 ctime(time()) + ".\n");
        dir = get_dir(DATA_DIR + "login/");
        result = ({ });
        count = 0;
        total = 0;
        for (i = 0; i < sizeof(dir); i++)
        {
                ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/", -1);
                for (j = 0; j < sizeof(ppls); j++)
                {
                        reset_eval_cost();
                        if (sscanf(ppls[j][0], "%s.o", name) == 1)
                        {
                                info = examine_player(name, 0, type, ppls[j][2]);
                                if (! info) continue;
                                result += ({ info });
                                count++;
                        
                        }
                }
                total += j;
                message("system", ESC + "[1A" + ESC + "[256D"
                                  HIG "進度：" + process_bar((i + 1) * 100 / sizeof(dir)) +
                                  "\n" + (me ? HIR "執行中" NOR "> " : ""),
                                  me ? me : filter_array(all_interactive(), (: wizardp :)));
        }

        info = HIC "\n檢查所有 " HIY + total +
               HIC " 玩家的結果如下：\n" NOR WHT;
        for (i = 0; i < sizeof(result); i++)
        {
                info += result[i];
                if (i % 20)
                {
                        log_file("examine", filter_color(info));
                        if (me) message("system", info, me);
                        info = "";
                }
        }

        if (! count)
                info += HIC "沒有任何的玩家數據可能異樣。\n" NOR;
        else
                info += HIG "共有 " + to_chinese(count) +
                        " 位玩家數據可能異常。\n\n" NOR;
        info += HIY "There are total " + total_gold + " golds.\n\n" NOR;

        log_file("examine", filter_color(info));

        if (me)
        {
                message("system", info, me);
                me->detach_system();
        }
}

protected string fname(object ob)
{
        string s1, s2;

        s1=query("surname", ob);
        s2=query("purename", ob);
        if (! s1) s1= "";
        if (s2) s1 += s2;
        if (s1 == "") s1 = "無名";
        return s1;
}

// Examine the player, if the player is illegal, I will return
// a detial string, or I will return 0
// If the flag copy_user has been set, I will login the user if
// he is offline
protected string examine_player(string name, int copy_user, int type, int last_touched)
{
        object me;
        object login_ob;
        object user_ob;
        string result;
        int day;
        int age;
        int online;
        mixed *st;
        int remove_flag;

        remove_flag = 0;
        if (type == EXAMINE_LOGINED)
        {
                if (! last_touched)
                {
                        st = stat(DATA_DIR + "login/" + name[0..0] + "/" +
                                  name + __SAVE_EXTENSION__);
        
                        if (! arrayp(st) || sizeof(st) < 3)
                                // 可能沒有這個文件
                                return sprintf(WHT "無法查閱玩家(%s)的的登錄信息。\n" NOR, name);
        
                        // 取最後訪問 login_ob 的時間
                        last_touched = st[1];
                }

                // 計算沒有上線的時間
                day = (time() - last_touched) / 86400;

                if (day >= 90 && ! objectp(find_player(name)))
                        //remove_flag = 1;
                        remove_flag = 0;
                else
                if (day >= 1)
                        // 這個文件最近沒有訪問過
                        return 0;
        }

        login_ob = new(LOGIN_OB);
        set("id", name, login_ob);

        if (! login_ob->restore())
        {
                destruct(login_ob);
                return sprintf(WHT "沒有玩家(%s)。\n" NOR, name);
        }

        if( query("id", login_ob) != name )
        {
                string id;
                id=query("id", login_ob);
                destruct(login_ob);
                return sprintf(HIR "玩家(%s)的ID(%s)不正確。\n" NOR, name, id);
        }

        if (! objectp(user_ob = find_player(name)))
        {
                online = 0;
                user_ob = LOGIN_D->make_body(login_ob);
                if (! user_ob)
                {
                        destruct(login_ob);
                        return sprintf(HIR "無法生成玩家(%s)。\n" NOR, name);
                }

                if (! user_ob->restore())
                {
                        destruct(login_ob);
                        destruct(user_ob);
                        return sprintf(HIR "無法讀取玩家檔案(%s)。\n" NOR, name);
                }
        } else
                online = 1;

        if (remove_flag && ! online)
        {
                if( ultrap(user_ob) || query("immortal", user_ob) )
                {
                        // 永久保留的玩家：從新保存 login_ob，
                        // 刷新該人物的最後訪問時間。
                        login_ob->save();
                        destruct(login_ob);
                        destruct(user_ob);
                        return 0;
                }

                // 刪除該玩家
                destruct(login_ob);
                destruct(user_ob);
                log_file("static/purge",
                         sprintf("%s %s was purged by BACKUP_D\n",
                                 log_time(), name));
                UPDATE_D->remove_user(name);
                return 0;
        }

        result = is_illegal(user_ob, type == EXAMINE_LOGINED);
        if (result)
        {
                if (online)
                        result = sprintf("%s%-14s%-10s%s%-17s%s%s\n",
                                 WHT,
                                 name,
                                 query("name", user_ob),
                                 (interactive(user_ob) ? HIC : HIR),
                                 (interactive(user_ob) ? query_ip_number(user_ob) : "斷線中"),
                                 NOR,
                                 result);
                else
                        result = sprintf("%s%-14s%-10s%s%-11s%-6s%s%s%s\n",
                                 WHT,
                                 name,
                                 query("name", user_ob),
                                 HIG,
                                 ctime(query("last_on", login_ob))[0..10],
                                 ctime(query("last_on", login_ob))[20..24],
                                 NOR,
                                 result,
                                 (user_ob->is_in_prison() ? HIR "(獄中)" NOR : ""));
        }

        destruct(login_ob);
        if (! online)
        {
                // the user is offline
                if (copy_user)
                {
                        me = this_player();
                        // I should login it
                        message_vision("$N口中念念有詞，將$n變了出來。\n",
                                       me, user_ob);
                        catch(user_ob->setup());
                        catch(user_ob->restore_autoload());
                        catch(user_ob->move(environment(me)));
                } else
                {
                        // ok. logout the user
                        destruct(user_ob);
                }
        } else
        {
                if (copy_user)
                {
                        // login user? oh, I needn't do it because the
                        // user is online now.
                        write("玩家目前正在線上。\n");
                }
        }

        return result;
}

protected string is_illegal(object ob, int update)
{
        int gold;
        int age;
        int exp;
        int sp;
        int dt;
        int dexp, dpot, dmar, dage;
        mapping my, lex;

        if (wizhood(ob) != "(player)")
                return 0;

#if 0
        if( query("family/family_name", ob) != "華山派" && 
            ob->query_skill("hunyuan-zhang", 1))
                return "擁有混元掌技能";
        return 0;
#endif
        if( query_temp("user_setup", ob) )
                gold = MONEY_D->player_carry(ob);
        else
        {
                mapping list = ([
                        "/clone/money/thousand-cash"   : ({ 1000, 1, }),
                        "/clone/money/cash"   : ({ 10, 1, }),
                        "/clone/money/gold"   : ({ 1, 1, }),
                        "/clone/money/silver" : ({ 1, 100, }),
                        "/clone/money/coin"   : ({ 1, 10000, }),
                ]);

                int *val;
                string *autoload;
                string item;
                int amount;
                int i;

                // the user is load by another object but not logind,
                // or the user maybe failed to login, so I will check
                // the autoload of the user.
                autoload = ob->query_autoload_info();
                gold=query("balance", ob)/10000;

                if (autoload) i = sizeof(autoload); else i = 0;
                for (--i; i >= 0; i--)
                {
                        if (sscanf(autoload[i], "%s:%d", item, amount) != 2)
                                continue;

                        if (! arrayp(val = list[item])) continue;
                        gold += amount * val[0] / val[1];
                        if (gold < 0) break;    // Too much money
                }
        }

        // trans to gold
        my = ob->query_entire_dbase();
        lex = my["last_examine"];
        if (! mapp(lex))
                lex = ([ ]);

        if (! intp(my["mud_age"]) ||
            ! intp(my["combat_exp"]) ||
            ! intp(my["potential"]) ||
            ! intp(my["experience"]) ||
            ! intp(lex["mud_age"]) ||
            ! intp(lex["combat_exp"]) ||
            ! intp(lex["potential"]) ||
            ! intp(lex["experience"]) ||
            ! intp(lex["time"]))
                return HIR "數據類型錯誤" NOR;

        age = my["mud_age"] / 86400;
        exp = my["combat_exp"];
        dexp = exp - lex["combat_exp"];
        dpot = my["potential"] - lex["potential"];
        dmar = my["experience"] - lex["experience"];
        dage = my["mud_age"] - lex["mud_age"];
        dt = time() - lex["time"];
        lex = allocate_mapping(6);
        if (dt > 60 && update)
        {
                lex["combat_exp"] = exp;
                lex["potential"] = my["potential"];
                lex["experience"] = my["experience"];
                lex["mud_age"] = my["mud_age"];
                lex["all_quest"] = my["all_quest"];
                lex["time"] = time();
                set("last_examine", lex, ob);
                if( !query_temp("user_setup", ob) )
                        ob->save();
        }

        total_gold += gold;

        if (gold > 2000)
                return HIY "擁有 " + gold + " 兩黃金" NOR;

        if (exp < 1000000 && gold >= 1000)
                return HIC "經驗 1M 以內擁有 " + gold + " 兩黃金" NOR;

        if (exp > 10000 && dt > 60)
        {
                if ((sp = dexp * 60 / dt) > 90)
                        return HIR "平均經驗速度太快(" + sp + "/分鐘:" + dt / 60 + "分鐘)" NOR;

                if ((sp = dpot * 60 / dt) > 20)
                        return HIR "平均潛能速度太快(" + sp + "/分鐘:" + dt / 60 + "分鐘)" NOR;

                if ((sp = dmar * 60 / dt) > 10)
                        return HIR "平均體會速度太快(" + sp + "/分鐘:" + dt / 60 + "分鐘)" NOR;

                if (dage > dt + 60)
                        return HIR "連線時間超過系統間隔時間(" + ((dage - dt) / 60) + "分鐘)。" NOR;
        }

        if (gold >= 100 && age < 1)
                return HIC "14歲擁有 " + gold + " 兩黃金" NOR;

        return 0;
}

int  help(object  me)
{
write(@HELP
指令格式：examine [-u] <玩家ID> | -all

查找玩家，判斷數據是否正常。如果使用了[-u]參數，則除了檢查玩
家，還會將不在線上玩家復制出來，以供詳細查閱。

判斷依據：
1. 超過 20000 兩黃金。
2. 經驗 1M 以內超過 3000 兩黃金。
3. 平均經驗速度超過 (90/m)。
4. 平均潛能速度超過 (20/m)。
5. 平均體會速度超過 (10/m)。
6. 14歲金錢超過 100 兩黃金。

HELP
    );
        return  1;
}
