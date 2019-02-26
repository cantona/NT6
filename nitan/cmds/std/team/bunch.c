// team command: bunch

#include <ansi.h>

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object *t;
        object env;
        object tob;
        string msg;
        object bei;

        string pure_name, id;

        // 查驗隊伍的合法性
        t = me->query_team();
        if (! arrayp(t))
                return notify_fail("你現在並不在隊伍中啊。\n");

        if (! me->is_team_leader())
                return notify_fail("只有隊伍的領袖才能發話，你先閉嘴。\n");

        if (! arg || sscanf(arg, "%s %s", arg, id) != 2)
                return notify_fail("建幫前先想好一個名字以及代表這個名字的英文ID吧！\n");

        if (stringp(msg = BUNCH_D->valid_new_build(me, id, arg)))
                return notify_fail(msg);

        t -= ({ 0 });

        if (sizeof(t) < 5)
                return notify_fail("你這個隊伍中現在沒有多少人，創建什麼幫派？\n");

        if( query_temp("pending/team_doing", me) && 
            query_temp("pending/team_doing", me) != "bunch" )
                return notify_fail("你還是等目前隊伍中的提議結束了再説吧。\n");

        // 判斷命令的合法性
        if (arg == "cancel")
        {
                if( arrayp(t=query_temp("pending/team_bunch/member", me)) )
                {
                        delete_temp("pending/team_bunch", me);
                        write("你取消和大家創建幫派的念頭。\n");
                        t -= ({ 0 });
                        message("vision", YEL + me->name(1) +
                                "取消了大家一同創建幫派的倡議。\n", t, me);
                } else
                        write("你現在並沒有倡議大家創建幫派啊！\n");

                delete_temp("pending/team_doing", me);
                return 1;
        }

        if( mapp(query_temp("pending/team_bunch", me)) )
        {
                write("你正倡議大家創建幫派呢！還是等大家迴應吧。\n");
                return 1;
        }

        if( query("balance", me)<100000000 )
        {
                write("開幫立會需要很多錢的，你銀行中的這點積蓄可不夠啊！\n");
                return 1;
        }

        if( query("weiwang", me)<10000 )
        {
                write("你在江湖上無籍籍之名，也來附這風雅？\n");
                return 1;
        } else
        if( query("weiwang", me)<50000 )
        {
                write("你這點名望還不夠振臂一呼，聚幫結眾，還是以後再説吧。\n");
                return 1;
        } else
        if( query("weiwang", me)<80000 )
        {
                write("你現在在江湖上也算是有些名頭了，可惜還是不夠。\n");
                return 1;
        } else
        if( query("weiwang", me)<100000 )
        {
                write("你再努力努力提升自己的威望，能"
                      "夠創建幫派的日子也不遠了。\n");
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

        if (stringp(msg = BUNCH_D->valid_new_bunch(pure_name)))
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
                        return notify_fail("現在你隊伍中" + tob->name(1) + "昏迷不醒呢。\n");

                if (! playerp(tob))
                        return notify_fail("你想結義，只怕" + tob->name(1) + "不答應。\n");

                if (tob->is_fighting())
                        return notify_fail("現在你隊伍中" + tob->name(1) + "正忙着打架呢。\n");

                if( mapp(query("league", tob)) || mapp(query("bunch", tob)) )
                        return notify_fail("現在你隊伍中"+ tob->name(1) + "已經加入別的組織了。\n");

                if( query("weiwang", tob)<10000 )
                        return notify_fail("現在你隊伍中" + tob->name(1) + "的江湖威望不夠，光你們威望很難振臂一呼，聚幫結眾。\n");
        }

        set_temp("pending/team_bunch/member", t, me);

        message_vision("$N大聲提議道：“我們眾兄弟情"
                       "投意合，今日為何不創建幫派，共創" +
                       "『" + arg + "』”？\n", me);
        set_temp("pending/team_bunch/name", pure_name, me);
        set_temp("pending/team_bunch/id", id, me);
        set_temp("pending/team_bunch/accept", ({me}), me);
        set_temp("pending/team_doing", "bunch", me);
        foreach (tob in t)
        {
                if (tob == me)
                        continue;

                tell_object(tob, YEL + me->name(1) + "(" +
                            query("id", me)+")想讓大家一"
                            "同創建幫派，創立『" + arg + "』，"
                            "你是否同意(right/refuse)？\n" + NOR);
                set_temp("pending/answer/"+query("id", me)+"/right",
                              bind((: call_other, __FILE__, "do_right", tob, me :), tob), tob);
                set_temp("pending/answer/"+query("id", me)+"/refuse",
                              bind((: call_other, __FILE__, "do_refuse", tob, me :), tob), tob);
        }

        return 1;
}

int do_right(object me, object ob)
{
        object *t;
        object *r;
        string msg;
        object tob;
        int base, shen;
        string bunch_name, type, id;

        if (! ob || environment(ob) != environment(me))
                return notify_fail("可惜啊，人家已經不在這兒了。\n");

        if (! living(ob))
                return notify_fail("人家現在聽不到你説的話，還是算了吧。\n");

        t=query_temp("pending/team_bunch/member", ob);
        if (! arrayp(t))
                return notify_fail("人家現在已經不打算創建幫派了。\n");

        if (member_array(me, t) == -1)
                return notify_fail("你現在已經不在人家的創建幫派考慮範圍之內了。\n");

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
                msg = "$N點頭頷首，伸出一指點點大家，道：“天下豪傑，盡皆於此，可喜啊！”\n";
                break;
        case 5:
                msg = "$N一聲長歎，道：“$l此言極是，道出我心中多年之願！”\n";
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

        r=query_temp("pending/team_bunch/accept", ob);
        if (! arrayp(r) || sizeof(r) < 1)
                r = ({ me });
        else
                r += ({ me });

        if (sizeof(t) == sizeof(r) && ! sizeof(t - r) && ! sizeof(r - t))
        {
                string fail = 0;

                // 全部同意，檢查是否能夠完成的條件，同時計算
                // 幫派的名望。
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
                                       "家一同創建幫派，$N的提議只好作罷。\n";
                                break;
                        }

                        if( mapp(query("league", tob)) || mapp(query("bunch", tob)) )
                        {
                                fail = "雖然大家都同意"
                                       "了，可惜" + tob->name() +
                                       "已經加入了別的組織了，$N的提議只好作罷。\n";
                                break;
                        }

                        base+=query("weiwang", tob);
                        shen+=query("shen", tob);
                }

                // 失敗了，無法結義
                if (stringp(fail))
                {
                        delete_temp("pending/team_bunch", ob);
                        message_vision(fail, ob);
                        return 1;
                }

                // 完成結義
                if (shen < 0)
                        type = "bad";
                else
                        type = "good";

                bunch_name=query_temp("pending/team_bunch/name", ob);
                id=query_temp("pending/team_bunch/id", ob);
                BUNCH_D->create_bunch(bunch_name, id, type, base, t);
                addn("balance", -100000000, ob);
                switch (random(3))
                {
                case 0:
                        msg = "聽説" + implode(t->name(1), "、") + "創建『" +
                              bunch_name + "』，縱橫江湖。";
                        break;
                case 1:
                        msg = "據聞" + implode(t->name(1), "、") + "創建幫派，" +
                              "組成了『" + bunch_name + "』，震動江湖。";
                        break;
                default:
                        msg = "傳説" + implode(t->name(1), "、") + "情投意合，" +
                              "創建幫派，共創『" + bunch_name + "』。";
                        break;
                }

                msg = sort_string(msg, 100, strlen("【泥潭幫派】某人："))[0..<2];
                CHANNEL_D->do_channel(this_object(), "rumor", msg);
                delete_temp("pending/team_bunch", ob);
        } else
                set_temp("pending/team_bunch/accept", r, ob);

        return 1;
}

int do_refuse(object me, object ob)
{
        object *t;
        string msg;

        if (! ob || environment(ob) != environment(me))
                return notify_fail("可惜啊，人家已經不在這兒了。\n");

        if (! living(ob))
                return notify_fail("人家現在聽不到你説的話，還是算了吧。\n");

        t=query_temp("pending/team_bunch/member", ob);
        if (! arrayp(t))
                return notify_fail("人家現在已經不打算創建幫派了。\n");

        if (member_array(me, t) == -1)
                return notify_fail("你現在已經不在人家的創建幫派考慮範圍之內了。\n");

        delete_temp("pending/team_bunch", ob);
        message_vision("$N搖了搖頭，對$n道：“你們的事情我不管，但是我沒有興趣。”\n",
                       me, ob);
        t -= ({ 0 });
        message("vision", YEL + me->name(1) + "拒絕了" + ob->name(1) +
                "的創建幫派提議。\n" NOR, t, me);
        return 1;
}
