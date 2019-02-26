// throw.c

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object card;
        object ob;
        int can = 0;
        string tstr;
        string unit;
        int time;
        string because;
        string bmsg;

        can = SECURITY_D->valid_grant(me, "(arch)");

        if (! arg)
                return notify_fail("你要把誰送進地獄？\n");

        sscanf(arg, "%s because %s", arg, because);

        // default is 20 minute
        time = 20;
        if (sscanf(arg, "%s %s", arg, tstr) == 2)
        {
                if (sscanf(tstr, "%d%s", time, unit) != 2)
                {
                        sscanf(tstr, "%d", time);
                        unit = "";
                }

                switch (unit)
                {
                case "h": time *= 60;         break;
                case "d": time *= 60 * 24 ;   break;
                case "m": time *= 1440 * 30;  break;
                case "y": time *= 1440 * 365; break;
                }
        }

        if (! time)
                return notify_fail("你要禁閉別人多久？\n");

        ob = find_player(arg);
        if (wiz_level(me) < 1 && ! objectp(ob))
                return notify_fail("沒有這個玩家。\n");

        if (! objectp(ob))
        {
                ob = UPDATE_D->global_find_player(arg);
                if (! objectp(ob))
                        return notify_fail("沒有這個玩家。\n");

                if( stringp(query("startroom", ob)) )
                        ob->move(query("startroom", ob));
                else
                        ob->move(environment(me));
        }

        if (! ob || ! me->visible(ob))
                return notify_fail("沒有這個玩家。\n");

        if (ob == me || time < 0)
                return notify_fail("瘋了... 你真是瘋了！\n");

        /*
        if (wiz_level(ob) > 0)
                return notify_fail("你不能禁閉巫師！\n");
        */

        bmsg = "";
        if (! ob->is_in_prison())
        {
                if (! because)
                {
                        UPDATE_D->global_destruct_player(ob);
                        return notify_fail("送人進監獄你必須有一個理由才行。\n");
                }

                switch (because)
                {
                case "flood":
                case "copy":
                case "rude":
                case "rumor":
                case "bug":
                case "main":
                        break;

                default:
                        UPDATE_D->global_destruct_player(ob);
                        return notify_fail("你這個理由也太不充分了。\n");
                }
        }

        if (! can)
        {
                if (card = present("throw card", me))
                {
                        message("vision", me->name() + "掏出一張卡片，"
                                "滴嘀咕咕的不知道在説些什麼，好像"
                                "提到了"+query("name", ob)+"。\n",
                                environment(me), ({ me }));
                        tell_object(me, "你掏出" + card->name() + "，"
                                "口中唸唸有詞：天靈靈！地靈靈！快把" +
                                query("name", ob)+"送到地獄去！\n");
                        time=query("time_to_leave", card);
                        destruct(card);
                        can = 1;
                }
        }

        if (! can)
        {
                UPDATE_D->global_destruct_player(ob);
                return notify_fail("你無權把"+query("name", ob)+"送進地獄！\n");
        }

        if (! ob->is_in_prison())
                log_file("static/throw",
                         sprintf("%s %s send into prison by %s because %s.\n",
                                 log_time(), geteuid(ob), geteuid(this_player(1)), because));

        ob->get_into_prison(me, 0, time);
        UPDATE_D->global_destruct_player(ob, 1);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : throw <玩家ID> [ <時間> ] because <理由>
 
這個指令可以讓你把某個玩家禁閉一段時間。時間以分鐘為單位，可
以用 h 表示小時，d 表示天，m 表示月份，y 表示年。

禁閉他人理由主要如下：
1. 口出污言穢語(rude)
2. 發佈他人説的污言穢語(copy)
3. 造謠生事(rumor)
4. 散佈重複信息(flood)
5. 使用系統錯誤，檔案待查(bug)
6. 出於維護該玩家檔案的目的(main)

see also : free 
HELP );
        return 1;
}