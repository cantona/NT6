// assist.c

#include <ansi.h>
 
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;
        object *team;
        object *assistors;
        mapping q;

        if (! arg)
        {
                if( objectp(ob=query_temp("quest/assist", me)) )
                        write("你現在正幫助" CYN + ob->name(1) +
                              NOR "完成門派的任務。\n");
                else
                        write("你現在並沒有幫助任何人完成門派的任務。\n");
                return 1;
        }

        if (arg == "cancel" || arg == "none")
        {
                if( objectp(ob=query_temp("pending/assist", me)) )
                {
                        write("你打消了幫助" + ob->name(1) + "的念頭。\n");
                        delete_temp("pending/assist", me);
                        return 1;
                }

                if( !objectp(ob=query_temp("quest/assist", me)) )
                {
                        write("你現在並沒有去幫助別人啊！\n");
                        return 1;
                }

                if (environment(ob) == environment(me))
                        message_vision("$N揮了一揮手，對$n道：“我還有"
                                       "事，先不幫你了，改日再見！”\n",
                                       me, ob);

                // 解除幫助狀態
                delete_temp("quest/assist", me);
                team = me->query_team();
                if (arrayp(team) && team[0] == ob)
                {
                        // 我在幫助對象的隊伍中，自動解除
                        me->dismiss_team();
                        message_vision("$N離開了$n的隊伍。\n",
                                       me, ob);
                }
                return 1;
        }

        if( objectp(ob=query_temp("quest/assist", me)) )
        {
                write("你現在不是正打算幫助" + ob->name(1) +
                      "完成任務麼？是不是想取消(assist cancel)了？\n");
                return 1;
        }

        // 幫助某人完成任務
        ob = present(arg, environment(me));
        if (! objectp(ob))
        {
                write("你想幫助誰？\n");
                return 1;
        }

        if( !stringp(query("family/family_name", ob)) || 
            query("family/family_name", ob) != query("family/family_name", me) )
        {
                write("你和" + ob->name() + "並不是同一個門派"
                      "的呀，看來這份好意只能讓對方心領了。\n");
                return 1;
        }

        if (! living(ob))
        {
                write("看來" + ob->name() + "現在沒法接受你得好意了。\n");
                return 1;
        }

        if( ob == query_temp("pending/assist", me) )
        {
                write("你想幫助" + ob->name(1) + "，可是人家還沒有答應你呢。\n");
                return 1;
        }

        if( query("quest", me) )
        {
                write("你現在正有任務在身，還是先忙完自己的"
                      "事情再說吧！\n");
                return 1;
        }

        write("你決定開始幫助" + ob->name(1) + "完成任務。\n");
        message_vision("$N對$n道：“" + ob->name() +
                       "，我和你一起去吧！”\n", me, ob);
        set_temp("pending/assist", ob, me);
        if (! playerp(ob))
        {
                message_vision("$n對$N說：“我還有別的事情哦，"
                               "不用你幫忙啦！”\n", me, ob);
                return 1;
        }

        tell_object(ob, YEL + me->name(1) + YEL "決定幫助你一"
                    "同完成任務，你是否同意(right|refuse " +
                    query("id", me)+")？\n"NOR);

        ob->set_temp("pending/answer/"+query("id", me)+"/right",
                     bind((: call_other, __FILE__, "do_right", ob, me :), ob));
        ob->set_temp("pending/answer/"+query("id", me)+"/refuse",
                     bind((: call_other, __FILE__, "do_refuse", ob, me :), ob));

        return 1;
}

// 允諾對方加入
int do_right(object me, object ob)
{
        object *ob_team;

        if( query_temp("pending/assist", ob) != me )
        {
                // 對方還沒有說願意你幫助你呢
                write(ob->name() + "現在沒打算幫助你呀，你還是再問問吧！\n");
                return 1;
        }

        delete_temp("pending/assist", ob);

        // 對方願意你幫助你
        message_vision("$N爽快的對$n說：“好吧！多謝了！”\n",
                       me, ob);
        tell_object(ob, me->name(1) + "願意接受你的幫助。\n");
        set_temp("quest/assist", me, ob);

        if (! pointerp(me->query_team()) || me->is_team_leader())
        {
                if (sizeof(me->query_team()) >= 12)
                {
                        write("你這個隊伍中的人太多了，沒法邀請" +
                              ob->name(1) + "加入，這樣讓他幫助"
                              "就不方便了。\n");
                        return 1;
                }

                // 我不在隊伍中或是我就是隊伍的領袖，則讓幫手加入隊伍
                if (pointerp(ob_team = ob->query_team()))
                {
                        // 幫手也在一個隊伍中，看看是哪個隊伍
                        if (ob_team[0] == me)
                                // 幫手已經在我的隊伍中了
                                return 1;

                        // 幫手在其它隊伍中，先退出來
                        ob->dismiss_team();
                }

                // 幫手加入我的隊伍
                me->add_team_member(ob);
                message_vision("$n加入了$N的隊伍，一同行走江湖。\n",
                               me, ob);
        } else
                tell_object(me, "讓" + ob->name() + "幫助你最"
                            "好是和你在一個隊伍中，如果可以的"
                            "話，就邀請對方組隊吧！\n");

        return 1;
}

// 拒絕對方加入
int do_refuse(object me, object ob)
{
        object *ob_team;

        if( query_temp("pending/assist", ob) != me )
        {
                // 對方還沒有說願意你幫助你呢，你幹什麼呢？
                write(ob->name() + "現在沒打算幫助你呀，你拒絕什麼？\n");
                return 1;
        }

        delete_temp("pending/assist", ob);
        message_vision("$N搖搖頭，對道：“你的好意我心領了，"
                       "不過現在還不需要勞動大駕。”\n", me, ob);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : assist <玩家ID>

這個指令表示你想幫助另一個人一同完成掌門或是世家長老分配給他
的殺人任務。當然你必須和他是同門，而且你當時沒有任務。如果對
方同意接受你的幫助，那麼你會自動加入到對方的隊伍中（除非對方
在另外一個隊伍中並且不是隊長）。
HELP );
        return 1;
}