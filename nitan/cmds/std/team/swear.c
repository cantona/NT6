// team command: swear

#include <ansi.h>

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object *t;
        object env;
        object tob;
        string msg;

        string pure_name;

        // 查驗隊伍的合法性
        t = me->query_team();
        if (! arrayp(t))
                return notify_fail("你現在並不在隊伍中啊。\n");

        if (! me->is_team_leader())
                return notify_fail("只有隊伍的領袖才能發話，你先閉嘴。\n");

        if (! arg)
                return notify_fail("結義前先想好一個名字吧！\n");

        t -= ({ 0 });

        if (sizeof(t) < 1)
                return notify_fail("你這個隊伍中現在沒有別人，結什麼義？\n");

        if( query_temp("pending/team_doing", me) && 
            query_temp("pending/team_doing", me) != "swear" )
                return notify_fail("你還是等目前隊伍中的提議結束了再說吧。\n");

        // 判斷命令的合法性
        if (arg == "cancel")
        {
                if( arrayp(t=query_temp("pending/team_swear/member", me)) )
                {
                        delete_temp("pending/team_swear", me);
                        write("你取消和大家結義的念頭。\n");
                        t -= ({ 0 });
                        message("vision", YEL + me->name(1) +
                                "取消了大家一同結義的倡議。\n", t, me);
                } else
                        write("你現在並沒有倡議大家結義啊！\n");

                delete_temp("pending/team_doing", me);
                return 1;
        }

        if( mapp(query_temp("pending/team_swear", me)) )
        {
                write("你正倡議大家結義呢！還是等大家回應吧。\n");
                return 1;
        }

        if( query("weiwang", me)<1000 )
        {
                write("你在江湖上無籍籍之名，也來附這風雅？\n");
                return 1;
        } else
        if( query("weiwang", me)<10000 )
        {
                write("你這點名望還不夠振臂一呼，聚幫結眾，還是以後再說吧。\n");
                return 1;
        } else
        if( query("weiwang", me)<20000 )
        {
                write("你現在在江湖上也算是有些名頭了，可惜還是不夠。\n");
                return 1;
        } else
        if( query("weiwang", me)<50000 )
        {
                write("你再努力努力提升自己的威望，能"
                      "夠聚義結盟的日子也不遠了。\n");
                return 1;
        }

        // 判斷名字的合法性
        pure_name = arg;
        if (strlen(pure_name) > 10)
                return notify_fail("你這個名字太長了。\n");

        if (strlen(pure_name) < 4)
                return notify_fail("你這個名字太短了。\n");

        if (! is_chinese(pure_name))
                return notify_fail("請你用中文起名字。\n");

        if (stringp(msg = LEAGUE_D->valid_new_league(pure_name)))
                return notify_fail(msg);

        if (strlen(pure_name) != strlen(arg))
                arg += NOR;

        // 判斷隊伍中所有人的合法性
        env = environment(me);
        foreach (tob in t)
        {
                if (environment(tob) != env)
                        return notify_fail("現在你隊伍中的人還沒有到齊呢。\n");

                if (! living(tob))
                        return notify_fail("現在你隊伍中還有人昏迷不醒呢。\n");

                if (! playerp(tob))
                        return notify_fail("你想結義，只怕" + tob->name(1) + "不答應。\n");

                if (tob->is_fighting())
                        return notify_fail("現在你隊伍中有人正忙著打架呢。\n");

                if( mapp(query("league", tob)) )
                        return notify_fail("現在你隊伍中有人已經加入別的同盟了。\n");
        }

        set_temp("pending/team_swear/member", t, me);

        message_vision("$N大聲提議道：“我們眾兄弟情"
                       "投意合，今日為何不結拜，共創" +
                       "『" + arg + "』”？\n", me);
        set_temp("pending/team_swear/name", pure_name, me);
        set_temp("pending/team_swear/accept", ({me}), me);
        set_temp("pending/team_doing", "swear", me);
        set_temp("pending/league_master", 1, me);
        foreach (tob in t)
        {
                if (tob == me)
                        continue;

                tell_object(tob, YEL + me->name(1) + "(" +
                            query("id", me)+")想讓大家一"
                            "同結義，創立『" + arg + "』，"
                            "你是否同意(right/refuse)？\n" + NOR);
                tob->set_temp("pending/answer/"+query("id", me)+"/right",
                              bind((: call_other, __FILE__, "do_right", tob, me :), tob));
                tob->set_temp("pending/answer/"+query("id", me)+"/refuse",
                              bind((: call_other, __FILE__, "do_refuse", tob, me :), tob));
        }

        return 1;
}

int do_right(object me, object ob)
{
        object *t;
        object *r;
        string msg;
        object tob;
        int base;
        string league_name;

        if (! ob || environment(ob) != environment(me))
                return notify_fail("可惜啊，人家已經不在這兒了。\n");

        if (! living(ob))
                return notify_fail("人家現在聽不到你說的話，還是算了吧。\n");

        t=query_temp("pending/team_swear/member", ob);
        if (! arrayp(t))
                return notify_fail("人家現在已經不打算結義了。\n");

        if (member_array(me, t) == -1)
                return notify_fail("你現在已經不在人家的結義考慮范圍之內了。\n");

        switch (random(8))
        {
        case 0:
                msg = "$N點點頭，看了看大家，鄭重道：“我沒有意見，我同意！”\n";
                break;
        case 1:
                msg = "$N大喜，拍掌大笑道：“正合我意！來！來來！”\n";
                break;
        case 2:
                msg = "$N哈哈大笑，大聲道：“很好！很好！真是不錯！”\n";
                break;
        case 3:
                msg = "$N只是熱淚盈眶，道：“甚好！他日行走江湖，那是何等的威風？”\n";
                break;
        case 4:
                msg = "$N點頭頷首，伸出一指點點大家，道：“天下豪傑，盡皆于此，可喜啊！”\n";
                break;
        case 5:
                msg = "$N一聲長嘆，道：“$l此言極是，道出我心中多年之願！”\n";
                break;
        case 6:
                msg = "$N環顧四方，豪氣頓發，道：“$l之言我謹隨無異！”\n";
                break;
        case 7:
                msg = "$N喝道：“早有今日之事，江湖怎會忒多爭端？此舉甚妙！”\n";
                break;
        default:
                msg = "$N連道：“妙！妙！妙不可言！今日良辰，更待合適？”\n";
                break;
        }
        msg = replace_string(msg, "$l", ob->name(1));
        message_vision(msg, me, ob);

        r=query_temp("pending/team_swear/accept", ob);
        if (! arrayp(r) || sizeof(r) < 1)
                r = ({ me });
        else
                r += ({ me });

        if (sizeof(t) == sizeof(r) && ! sizeof(t - r) && ! sizeof(r - t))
        {
                string fail = 0;

                // 全部同意，檢查是否能夠完成的條件，同時計算
                // 結義的名望。
                base = 10000;
                foreach (tob in t)
                {
                        if (! objectp(tob) || environment(tob) != environment(me))
                        {
                                fail = "雖然大家都同意"
                                       "了，可惜現在有人不在，$N";
                                       "的提議只好作罷。\n";
                                break;
                        }

                        if (! living(tob) || tob->is_fighting())
                        {
                                fail = "雖然大家都同意"
                                       "了，可惜現在有人沒法和大"
                                       "家一同結義，$N的提議只好作罷。\n";
                                break;
                        }

                        if( mapp(query("league", tob)) )
                        {
                                fail = "雖然大家都同意"
                                       "了，可惜" + tob->name() +
                                       "已經加入了別的同盟了，$N的提議只好作罷。\n";
                                break;
                        }

                        base+=query("weiwang", tob);
                }

                // 失敗了，無法結義
                if (stringp(fail))
                {
                        delete_temp("pending/team_swear", ob);
                        message_vision(fail, ob);
                        return 1;
                }

                // 完成結義
                league_name=query_temp("pending/team_swear/name", ob);
                LEAGUE_D->create_league(league_name, base, t);
                switch (random(3))
                {
                case 0:
                        msg = "聽說" + implode(t->name(1), "、") + "結成" +
                              league_name + "，縱橫江湖。";
                        break;
                case 1:
                        msg = "據聞" + implode(t->name(1), "、") + "近日聚義，" +
                              "組成了" + league_name + "，震動江湖。";
                        break;
                default:
                        msg = "傳說" + implode(t->name(1), "、") + "情投意合，" +
                              "結義成盟，共創" + league_name + "。";
                        break;
                }

                msg = sort_string(msg, 64, strlen("【江湖傳聞】某人："))[0..<2];
                CHANNEL_D->do_channel(this_object(), "rumor", msg);
                delete_temp("pending/team_swear", ob);
        } else
                set_temp("pending/team_swear/accept", r, ob);

        return 1;
}

int do_refuse(object me, object ob)
{
        object *t;
        string msg;

        if (! ob || environment(ob) != environment(me))
                return notify_fail("可惜啊，人家已經不在這兒了。\n");

        if (! living(ob))
                return notify_fail("人家現在聽不到你說的話，還是算了吧。\n");

        t=query_temp("pending/team_swear/member", ob);
        if (! arrayp(t))
                return notify_fail("人家現在已經不打算結義了。\n");

        if (member_array(me, t) == -1)
                return notify_fail("你現在已經不在人家的結義考慮范圍之內了。\n");

        delete_temp("pending/team_swear", ob);
        message_vision("$N搖了搖頭，對$n道：“你們的事情我不管，但是我沒有興趣。”\n",
                       me, ob);
        t -= ({ 0 });
        message("vision", YEL + me->name(1) + "拒絕了" + ob->name(1) +
                "的結義提議。\n" NOR, t, me);
        return 1;
}
