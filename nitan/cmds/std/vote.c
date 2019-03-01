// vote command..
// Modified by Marz, 04/18/96

#include <net/dns.h>
#include <ansi.h>

inherit F_CLEAN_UP;

int valid_voters(object me);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object victim;
        string act_name, victim_name;
        string file;
        object file_ob;

        if( (query("age", me)<18) && !wizardp(me) )
                return notify_fail("民主不是兒戲！小孩子一邊玩去！\n");

        if( query("vote/deprived", me) )
        {
                // 是否被剝奪投票權？還沒有恢復呢？
                if( time()-query("vote/deprived", me) >= 86400 )
                        delete("vote/deprived", me);
                else
                        return notify_fail("你想起當初玩弄民主、被剝奪投票權的事，追悔莫及。\n");
        }

            if (! arg || sscanf(arg, "%s %s", act_name, victim_name) != 2)
                return notify_fail("這神聖的一票，要想清楚了才能投。\n");
    
        victim = find_player(victim_name);
        if (! objectp(victim))
        {
                string temp;
                temp = victim_name;
                victim_name = act_name;
                act_name = temp;
                victim = find_player(victim_name);
        }

        if (! victim) return notify_fail("你要投誰的票？\n");
        if (wizardp(victim)) return notify_fail("你要投巫師的票？\n");
                
        if (! stringp(file = (string)"/cmds/std/vote/" + act_name) ||
            file_size(file + ".c") <= 0)
                return notify_fail("你要投票幹什麼？\n");

        call_other(file, "???");
        file_ob = find_object(file);

        if ((int)file_ob->vote(me, victim) <= 0)
        {
                if( query("vote/abuse", me)>50 )
                {
                        write(HIG "你因為胡亂投票，投票權被暫時剝奪24小時！\n" NOR);
                        set("vote/deprived", time(), me);
                        delete("vote/abuse", me);
                }
                return 0;
        }

        log_file("static/vote", sprintf("%s %s vote: %s %s\n",
                                        log_time(), log_id(me),
                                        act_name, victim_name));

        return 1;
}

int valid_voters(object me)
{
        object *list;
        int d = 0;
        int j;

            list = users();
            j = sizeof(list);
            while (j--)
        {
                // Skip those users in login limbo.
                if (! environment(list[j])) continue;
                if (! me->visible(list[j])) continue;
                if( (query("age", list[j])<18) && !wizardp(list[j]))continue;
                if( query("vote/deprived", list[j]))continue;

                d++;
        }
        
        return d;
}


int help(object me)
{
        write(@HELP
指令格式 : vote <動議> <某人> 

此命令提議對某人採取行動，由大家投票決定。可是如果五分鐘內沒有人附議，
投票會自動取消。當前可以有如下<動議>：

chblk:   關閉某人頻道，需三票以上，十個人同意或是簡單多數同意，如果
                       被表決的玩家14歲，那麼只需要三人同意即可。
unchblk: 打開某人頻道，需三票以上，十五個人同意或是簡單多數同意。

注意：投票可以使用任何不同 IP 區域的合法 ID， 但是如果利用投票惡意騷
擾其它玩家，則將導致監禁或是 PURGE 的嚴厲懲戒，並且此懲戒將波及該 ID
的所有人物，務必小心使用投票權。對于任何沒有違反遊戲規則的玩家，請勿
使用投票，否則將視為濫用投票權。

HELP );
        return 1;
}