// swear.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;
        object old;
        string msg;

        if (! stringp(arg) || arg != "cancel" && sscanf(arg, "with %s", arg) != 1)
                return notify_fail("你要和誰一同結義？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("好好忙你手頭的事情！\n");

        ob = present(arg, environment(me));

        if( objectp(old=query_temp("pending/swear", me)) && 
            (ob || arg == "cancel"))
        {
                if (old != ob)
                {
                        write("你打消了和" + old->name(1) + "結義的念頭。\n");
                        if (environment(old) == environment(me))
                                tell_object(old, me->name(1) + "打消了和你結義的念頭。\n");
                } else
                if (query_temp("pending/answer/" + query("id", me), old))
                        return notify_fail("你正在向人家提出請求呢，可是人家還沒有答應你。\n");

                delete_temp("pending/swear", me);
                delete_temp("pending/answer/"+query("id", me), old);
                if (arg == "cancel")
                        return 1;
        }

        if (! ob)
                return notify_fail("這裏沒有這個人。\n");

        if (query_temp("pending/answer/" + query("id", ob), me) &&
            query_temp("pending/swear", ob) == me )
                return notify_fail("別人正在向你提議結拜呢，你究竟答應還是不答應？\n");


        if (! ob->is_character())
        {
                message_vision("$N盯着$n自言自語道：“咱們...咱"
                               "們結拜吧！求求你了！”...看來是"
                               "瘋了。\n", me, ob);
                return 1;
        }

        if (ob == me)
        {
                message_vision("$N目光呆滯，兩眼發直，口中唸唸有詞。\n", me);
                return 1;
        }

        if( query("age", me)<18 )
        {
                write("小毛孩子搗什麼亂？一邊玩去！\n");
                return 1;
        }

        if( query("age", ob)<18 )
        {
                write(ob->name() + "還是一個小毛孩子，你就省省吧，別逗人家了。\n");
                return 1;
        }

        if( !query("can_speak", ob) )
        {
                message_vision("$N望着$n傻笑的不停，不知道中了什麼邪。\n", me, ob);
                return 1;
        }

        if( stringp(query("born_family", me)) && 
            query("born_family", me) != "沒有" && 
            query("born_family", me) == query("born_family", ob) )
        {
                write("你和人家是同族弟子，結拜個什麼？\n");
                return 1;
        }

        if (me->is_brother(ob))
        {
                write("你已經和他結義了，似乎沒有必要再來一次吧。\n");
                return 1;
        }

        if( mapp(query("brothers", me)) && sizeof(query("brothers", me))>12 )
        {
                write("你結義的兄弟也太多了，連你自己都快記不清楚了。\n");
                return 1;
        }

        if (! living(ob))
        {
                write(ob->name() + "現在昏迷不醒，無法理會你的請求。\n");
                return 1;
        }

        me->start_busy(1);

        switch (random(6))
        {
        case 0:
                msg = "$N對$n大聲説道：“$R，你我一見如故，何不就此結義？”\n";
                break;
        case 1:
                msg = "$N歎道：“天下雖大，知音難覓，$nn，你我有緣，今日何不結"
                      "拜？”\n";
                break;
        case 2:
                msg = "$N望着$n，喜不自勝道：“今日得遇$R，實乃三生有幸，你我"
                      "結拜可好？”\n";
                break;
        case 3:
                msg = "$N跨上一步，大聲道：“千金易得，良友難覓，$nn！你我何不"
                      "就此結拜？”\n";
                break;
        case 4:
                msg = "$N道：“$nn！在下有意和你結為異姓骨肉，你看可好？”\n";
                break;
        default:
                msg = "$N拉着$n的手，鄭重道：“今日良辰，你我在"
                      "此相逢，當真難得，不如結拜可好？”\n";
                break;
        }

        msg = replace_string(msg, "$nn", ob->name(1));
        msg = replace_string(msg, "$R", RANK_D->query_respect(ob));
        message_vision(msg, me, ob);

        if (! userp(ob))
        {
                write("但是" + ob->name() + "面露難色，看來是不感興趣。\n");
                return 1;
        }

        tell_object(ob, YEL + me->name(1) + "請求和你結拜，你答應(right)還是不答應(refuse)？\n" NOR);
        set_temp("pending/answer/"+query("id", me)+"/right",
                     bind((: call_other, __FILE__, "do_right", ob, me :), ob), ob);
        set_temp("pending/answer/"+query("id", me)+"/refuse",
                     bind((: call_other, __FILE__, "do_refuse", ob, me :), ob), ob);
        set_temp("pending/swear", ob, me);

        return 1;
}

int do_right(object me, object ob)
{
        string msg;

        if (! ob || environment(ob) != environment(me))
                return notify_fail("可惜啊，人家已經不在這兒了。\n");

        if (! living(ob))
                return notify_fail("人家現在聽不到你説的話，還是算了吧。\n");

        if( query_temp("pending/swear", ob) != me )
                return notify_fail("人家現在已經不打算和你結拜了。\n");

        delete_temp("pending/swear", ob);

        if (me->is_brother(ob))
        {
                write("你已經和他結義了，似乎沒有必要再來一次吧。\n");
                return 1;
        }

        if( mapp(query("brothers", me)) && sizeof(query("brothers", me))>12 )
        {
                message_vision("$N為難的對$n道：“不是我不想...只是...”\n",
                               me, ob);
                write("你結義的兄弟也太多了，連你自己都快記不清楚了。\n");
                return 1;
        }

        message_vision("$N看着$n，連連點頭道：“" + RANK_D->query_self(me) +
                       "正有此意！甚好，甚好！”\n言罷，兩人"
                       "齊齊跪下，撮土為香，一起磕頭髮誓：“"
                       "雖非骨肉，情同手足。\n雞腿情深，酒袋"
                       "恩重！不是同年同月同日生，但願同年同"
                       "月同日死！”\n", me, ob);

        // 記錄數據
        set("brothers/"+query("id", ob), ob->name(1), me);
        set("brothers/"+query("id", me), me->name(1), ob);
        me->save();
        ob->save();

        switch (random(3))
        {
        case 0:
                msg = "聽説" + me->name(1) + "已和" +
                      ob->name(1) + "結為異姓骨肉，共闖江湖。";
                break;
        case 1:
                msg = "據説" + me->name(1) + "和" + ob->name(1) +
                      "一見如故，已經結為異姓骨肉。";
                break;
        default:
                msg = "聽説" + me->name(1) + "與" + ob->name(1) +
                      "結義，攜手行走江湖。";
                break;
        }
        CHANNEL_D->do_channel(this_object(), "rumor", msg);
        return 1;
}

int do_refuse(object me, object ob)
{
        string msg;

        if (! ob || environment(ob) != environment(me))
                return notify_fail("可惜啊，人家已經不在這兒了。\n");

        if (! living(ob))
                return notify_fail("人家現在聽不到你説的話，還是算了吧。\n");

        if( query_temp("pending/swear", ob) != me )
                return notify_fail("人家現在已經不打算和你結拜了。\n");

        delete_temp("pending/swear", ob);

        switch (random(6))
        {
        case 0:
                msg = "$N嘿嘿乾笑了幾聲，清了清嗓子，對$n道："
                      "“在下怎敢高攀？”\n";
                break;
        case 1:
                msg = "$N一皺眉，對$n道：“這... 這似乎不太好"
                      "吧？還是改日再説吧！”\n";
                break;
        case 2:
                msg = "$N面有難色，道：“$nn，你的美意我心領了"
                      "，只是... 只是... 唉！不説也罷。”\n";
                break;
        case 3:
                msg = "$N歎了一口氣道：“$nn，我只是覺得今日時"
                      "辰有些不美，談及此事不太好，不太好啊！”\n";
                break;
        case 4:
                msg = "$N嗯了一聲，忽然道：“你我輩分不合，這"
                      "個，這個我看還是算了吧。”\n";
                break;
        default:
                msg = "$N不看$n，只是顧左右而言它，看來是不"
                      "打算和$n結拜。\n";
                break;
        }

        msg = replace_string(msg, "$nn", ob->name(1));
        message_vision(msg, me, ob);
        tell_object(ob, "看來人家對你沒什麼興趣。\n");

        return 1;
}

int help(object me)
{
           write( @HELP
指令格式: swear cancel | with <someone>

和某人結義。

see also：brothers
HELP );
           return 1;
}
