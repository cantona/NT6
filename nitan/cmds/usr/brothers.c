// brothers

#include <ansi.h>
#include <getconfig.h>

inherit F_CLEAN_UP;

int sort_brothers(string id1, string id2);

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object  who;
        object  ob;
        string  msg;
        string  pro;
        mapping bro;
        string *ids;
        string  id;
        string  nid;

        if (arg && sscanf(arg, "out %s", arg) == 1)
        {
                if (! me->is_brother(arg))
                        return notify_fail("你現在沒有這個結拜兄弟啊。\n");

                if( query_temp("pending/brother_out", me) != arg )
                {
                        write("你確定要和這位朋友(" + arg + ")割袍斷義嗎？\n"
                              YEL "如果你確定，請再輸入一次這條命令。\n" NOR);
                        set_temp("pending/brother_out", arg, me);
                        return 1;
                }

                delete_temp("pending/brother_out", me);
                if (objectp(ob = find_player(arg)) &&
                    environment(ob) == environment(me))
                {
                        // is the brother at present now?
                        message_vision("$N一聲歎息，看着$n，絕決道：“" + ob->name(1) +
                                       "不必多説，從今往後，你和我再也沒有半點關係了！”\n",
                                       me, ob);
                }

                nid=query("brothers/"+arg, me)+"("+arg+")";
                write("你和" + nid + "斷絕了關係。\n");
                id=query("id", me);
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "聽説" + me->name(1) + "(" + id + ")"
                        "和" + nid + "割袍斷義，斷絕了來往。");

                // remove the brother's association
                UPDATE_D->clear_user_data(id, "brothers:" + arg);
                UPDATE_D->clear_user_data(arg, "brothers:" + id);
                return 1;
        }

        if (! arg || ! wizardp(me))
        {
                who = me;
                pro = "你";
        } else
        {
                if (! objectp(who = find_player(arg)))
                        return notify_fail("沒有找到這個玩家。\n");
                else
                        pro = who->name(1);
        }

        if( !mapp(bro=query("brothers", who)) || sizeof(bro)<1 )
                return notify_fail(pro + "現在還沒有結義的兄弟們。\n");

        msg = pro + "現在" + LOCAL_MUD_NAME() + "的結義兄弟都有：\n\n";
        ids = keys(bro);
        ids = sort_array(ids, (: sort_brothers :));
        foreach (id in ids)
        {
                nid = (string) bro[id] + "(" + id + ")";
                msg += sprintf(WHT "%-14s  ", nid);
                if (objectp(ob = find_player(id)))
                        msg += sprintf(HIY "在線   "
                                       NOR WHT "經驗：" HIC "%-9d "
                                       NOR WHT "閲歷：" HIW "%-8d "
                                       NOR WHT "威望：" HIY "%-8d\n" NOR,
                                       query("combat_exp", ob),
                                       query("score", ob),
                                       query("weiwang", ob));
                else
                        msg += HIR "不在線\n" NOR;
        }
        write(msg);

        return 1;
}

int sort_brothers(string id1, string id2)
{
        object ob1, ob2;

        ob1 = find_player(id1);
        ob2 = find_player(id2);
        if (! objectp(ob1) && ! objectp(ob2))
                return strcmp(id2, id1);

        if (objectp(ob1) && objectp(ob2))
                return query("combat_exp", ob2) - query("combat_exp", ob1);

        if (objectp(ob1))
                return -1;

        return 1;
}

int help(object me)
{
           write( @HELP
指令格式: brothers 無參數 | out <sb>

查看自己現在的結義兄弟們。如果使用 brothers out <sb> 可以解
除結義關係。

see also：swear
HELP );
           return 1;
}
