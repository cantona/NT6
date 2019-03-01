// league.c

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int sort_hatred(string id1, string id2, mapping hatred);
int sort_member(string id1, string id2);
int show_league_info(object me, string arg);
int show_league_member(object me, string arg);
int show_league_hatred(object me, string arg);
int dismiss_league(object me, string arg);

int main(object me, string arg)
{
        object *obs;
        string fname;
        array args;

        if (! arg) arg = "info";
        args = explode(arg, " ");
        if (sizeof(args) > 1)
                arg = implode(args[1..<1], " ");
        else
                arg = 0;

        switch (args[0])
        {
        case "info":
                // 顯示同盟的信息
                return show_league_info(me, arg);

        case "member":
                return show_league_member(me, arg);

        case "dismiss":
                return dismiss_league(me, arg);

        case "top":
                return "/cmds/usr/top"->main(me, "league");

        case "hatred":
                // 顯示同盟的仇人
                return show_league_hatred(me, arg);

        case "out":
                if( !stringp(fname=query("league/league_name", me)) )
                        return notify_fail("你現在還沒有和任何人結義成盟呢。\n");

                if( query_temp("pending/out_league", me) )
                {
                        // 同盟的聲望下降
                        LEAGUE_D->add_league_fame(fname, -LEAGUE_D->query_league_fame(fname) / 10);
                        CHANNEL_D->do_channel(this_object(), "rumor",
                                "聽說"+me->name(1)+"("+query("id", me)+
                                ")義無反顧，已經背離" + fname + "而去。");
                        delete_temp("pending/out_league", me);

                        // 清除該用戶在同盟中的信息
                        UPDATE_D->clear_user_data(query("id", me),"league");
                        return 1;
                }

                write("你真的想要背棄當初的結義好友嗎？這樣做會降低" + fname + "的聲望。\n"
                      YEL "如果你確定了，就再輸入一次 league out 命令。\n" NOR);
                set_temp("pending/out_league", 1, me);
                return 1;
        }

        write("無效的參數。\n");
        return 1;
}

// 根據玩家和參數選擇同盟的名字
mixed select_league(object me, string arg)
{
        string fam;
        object ob;

        if (! wizardp(me))
                // only wizard can show every league's list
                fam = 0;
        else
        if (stringp(arg) && arg != "")
        {
                if( !arrayp(query(arg+"/member", get_object(LEAGUE_D))) )
                        fam = 0;
                else
                        fam = arg;

                if (! stringp(fam) && objectp(ob = UPDATE_D->global_find_player(arg)))
                {
                        // 沒有 arg 這個同盟，查看是否有該玩家
                        fam=query("league/league_name", ob);
                        UPDATE_D->global_destruct_player(ob);
                        if (! stringp(fam))
                                return notify_fail("這人現在沒有和別人結成同盟。\n");
                }

                if (! stringp(fam))
                        return notify_fail("沒有這個玩家，不能查閱相關的同盟。\n");
        }

        if (! fam)
        {
                // select my league
                if( !stringp(fam=query("league/league_name", me)) )
                        return notify_fail("你現在還沒有和別人結義成盟呢。\n");
        }

        return fam;
}

// 顯示同盟的仇人
int show_league_hatred(object me, string arg)
{
        mapping hatred;
        string fam;
        array ids;
        mixed *data;
        string msg;
        string st;
        int count;
        int i;

        if (! stringp(fam = select_league(me, arg)))
                return 0;

        hatred = LEAGUE_D->query_league_hatred(fam);
        if (! mapp(hatred) || ! sizeof(hatred))
        {
                write(fam + "現在沒有什麼仇人。\n");
                return 1;
        }

        ids = keys(hatred) - ({ 0 });
        ids = sort_array(ids, (: sort_hatred :), hatred);

        count = 0;
        msg = WHT "目前" + fam + "在江湖上的仇敵都有\n" NOR
              HIY "────────────────\n" NOR;
        for (i = 0; i < sizeof(ids) && count < 30; i++)
        {
                data = hatred[ids[i]];
                if (! arrayp(data) || sizeof(data) < 2 ||
                    ! stringp(data[0]) || ! intp(data[1]))
                        continue;

                st = sprintf("%s(%s%s%s)", data[0], YEL, ids[i], NOR);
                msg += sprintf("%2d. %-34s  %s%-9d%s\n",
                               ++count, st, HIR, data[1], NOR);
        }

        msg += HIY "────────────────\n" NOR;
        if (i < sizeof(ids))
                msg += WHT "江湖上的敵人太多，難以盡數。\n" NOR;
        else
                msg += WHT "目前一共是" + chinese_number(i) +
                       "人。\n" NOR;
        write(msg);
        return 1;
}

// 顯示某一個同盟中的人員
int show_league_member(object me, string arg)
{
        array member;
        string id;
        object user;
        string msg;
        int n;

        if (! arg)
        {
                if( !stringp(arg=query("league/league_name", me)) )
                        return notify_fail("你現在還沒有加入任何一個同盟呢。\n");
        }

        if (! arrayp(member = LEAGUE_D->query_members(arg)))
        {
                write("現在江湖上沒有(" + arg + ")這個字號。\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail(arg + "現在人丁稀落。\n");

        if (! wizardp(me))
        {
                if( query("jing", me)<50 )
                        return notify_fail("你現在精神不濟，無法打聽這些消息。\n");

                if (me->is_busy())
                        return notify_fail("你現在正忙，沒有時間打聽這些消息。\n");

                me->receive_damage("jing", 50);
                me->start_busy(3);
        }

        msg = "";
        n = 0;
        foreach (id in member)
        {
                user = UPDATE_D->global_find_player(id);
                if (! objectp(user))
                        continue;

                n++;
                msg += user->short(1) + "\n";
                UPDATE_D->global_destruct_player(user);
        }

        if (msg == "")
                return notify_fail(arg + "現在人丁稀落。\n");

        write(arg + "目前有以下" + chinese_number(n) + "人：\n" + msg);
        return 1;
}

// 顯示同盟中的信息
int show_league_info(object me, string arg)
{
        string fam;
        object  ob;
        string  msg;
        string pro;
        array member;
        string  id;

        if (! stringp(fam = select_league(me, arg)))
                return 0;

        if( fam == query("league/league_name", me) )
                pro = "你";
        else
                pro = fam;

        if (! arrayp(member = LEAGUE_D->query_members(fam)))
        {
                write("現在江湖上沒有(" + fam + ")這個字號。\n");
                return 1;
        }

        if (sizeof(member) < 1)
                return notify_fail(pro + "現在沒有一個兄弟。\n");

        msg = pro + "現在" + LOCAL_MUD_NAME() + "的結義兄弟都有：\n\n";
        member = sort_array(member, (: sort_member :));
        foreach (id in member)
        {
                msg += sprintf(WHT "%-10s  ", id);
                if (objectp(ob = find_player(id)))
                        msg += sprintf(HIY "在線   "
                                        NOR WHT "經驗：" HIC "%-9d "
                                       NOR WHT "閱歷：" HIW "%-8d "
                                       NOR WHT "威望：" HIY "%-8d\n" NOR,
                                       query("combat_exp", ob),
                                       query("score", ob),
                                       query("weiwang", ob));
                else
                        msg += HIR "不在線\n" NOR;
        }

        msg += sprintf("\n現在%s中一共有%s位好友，在江湖上具有 %s%d%s 點聲望。\n",
                       fam, chinese_number(sizeof(member)),
                       HIY, LEAGUE_D->query_league_fame(fam), NOR);
        write(msg);

        return 1;
}

// 顯示某一個同盟中的人員
int dismiss_league(object me, string arg)
{
        array member;
        string id;
        object user;
        string msg;
        int n;

        if (wiz_level(me) < wiz_level("(arch)"))
                return notify_fail("你的權限不夠，不能強行解散同盟。\n");

        if (! arg)
                return notify_fail("你要解散哪個同盟？\n");

        if (! arrayp(member = LEAGUE_D->query_members(arg)))
        {
                write("現在江湖上沒有(" + arg + ")這個字號。\n");
                return 1;
        }

        write("你強行解散了" + arg + "。\n");
        LEAGUE_D->dismiss_league(arg);
        return 1;
}


// 給所有的仇恨對象排序
int sort_hatred(string id1, string id2, mapping hatred)
{
        mixed *d1, *d2;

        if (! arrayp(d1 = hatred[id1]) || sizeof(d1) < 2 || ! intp(d1[1]))
                return 1;

        if (! arrayp(d2 = hatred[id2]) || sizeof(d2) < 2 || ! intp(d2[1]))
                return -1;

        return d2[1] - d1[1];
}

// 給同盟中的所有結義成員排序
int sort_member(string id1, string id2)
{
        object ob1, ob2;

        ob1 = find_player(id1);
        ob2 = find_player(id2);
        if (! objectp(ob1) && ! objectp(ob2))
                return strcmp(id2, id1);

        if (objectp(ob1) && objectp(ob2))
                return atoi(count_div(query("combat_exp", ob2),100))-atoi(count_div(query("combat_exp", ob1),100));

        if (objectp(ob1))
                return -1;

        return 1;
}

int help(object me)
{
           write(@HELP
指令格式: league info [玩家] | hatred [玩家] | member [同盟名字] | top

查看目前你結義的同盟的各種信息，其中：

info   ：查看同盟中的人物，成員狀態，聲望。
hatred ：查看同盟的仇恨對象。
member ：查看某個同盟的成員。
top    ：查看結義同盟的聲望排名。

巫師可以查看各個同盟的信息，只需要在命令後面加上同盟的名字或
是同盟中的玩家。另外巫師可以使用 league dismiss 命令強行解散
一個同盟。

see also: team (團體同盟)
HELP );
           return 1;
}
