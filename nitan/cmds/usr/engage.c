// engage.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object witness;
        object ob;
        object old;
        string msg;

        seteuid(getuid());

        if (! arg)
                return notify_fail("你要向誰求婚？\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("好好忙你手頭的事情！\n");

        ob = present(arg, environment(me));

        if( objectp(old=query_temp("pending/engage", me)) && 
            (ob || arg == "cancel"))
        {
                if (old != ob)
                {
                        write("你打消了向" + old->name(1) + "求婚的念頭。\n");
                        if (environment(old) == environment(me))
                                tell_object(old, me->name(1) + "打消了向你求婚的念頭。\n");
                } else
                if (query_temp("pending/answer/" + query("id", me), old))
                        return notify_fail("你正在向人家求婚呢。\n");

                delete_temp("pending/engage", me);
                delete_temp("pending/answer/"+query("id", me), old);
                if (arg == "cancel")
                        return 1;
        }

        if (! ob)
                return notify_fail("這裡沒有這個人。\n");

        if (query_temp("pending/answer/" + query("id", ob), me) &&
            query_temp("pending/engage", ob) == me )
                return notify_fail("別人正在向你求婚呢，你究竟答應還是不答應？\n");


        if (! ob->is_character())
        {
                message_vision("$N痴痴的望著$n自言自語：嫁給"
                               "我吧...嫁給我吧...看來是瘋了。\n", me, ob);
                return 1;
        }

        if (ob == me)
        {
                message_vision("$N目光呆滯，兩眼發直。\n", me);
                return 1;
        }

        if( query("gender", me) == "女性" && query("gender", ob) == "女性" || 
            query("gender", me) != "女性" && query("gender", ob) != "女性" )
        {
                write("你想和" + ob->name(1) + "結婚生理上似乎不太合適吧？\n");
                return 1;
        }

        if( query("class", me) == "bonze" )
        {
                message_vision("$N對$n哼哼道：我也要結婚，我也要結婚！\n", me, ob);
                return 1;
        }

        if( query("class", ob) == "bonze" )
        {
                message_vision("$N淚流滿面的對$n道：你快還俗吧！我要和你結婚！\n", me, ob);
                return 1;
        }

        if( !query("can_speak", ob) )
        {
                message_vision("$N望著$n傻笑，一副變態的模樣。\n", me, ob);
                return 1;
        }

        if( query("couple/couple_id", me) == query("id", ob) )
                return notify_fail("你大腦進了水？\n");

        if( query("couple", me) )
                return notify_fail("你可要穩住！根據泥潭法典第九十九條，重婚者打入地獄！\n");

        if( query("couple", ob) )
                return notify_fail("你怎麼也得等人家離婚了再說吧？\n");

        if( query("age", me)<18 )
        {
                message_vision("$N對$n大聲喊道：我要快快長大，早早結婚！\n",
                               me, ob);
                return 1;
        }

        if( query("age", ob)<18 )
        {
                message_vision("$N對$n大聲喊道：你要快快長大，我要等你結婚！\n",
                               me, ob);
                return 1;
        }

        me->start_busy(1);
        if (! objectp(witness = present("marriage witness", environment(me))))
        {
                if( query_temp("pending/engage_to", me) == query("id", ob) )
                {
                        CHANNEL_D->do_channel(this_object(), "rumor",
                                "據說" + me->name(1) + "下定決心，要和" +
                                ob->name(1) + "私定終身。");
                } else
                {
                        write("這裡連個証婚人都沒有？你想私定終身嘛？要"
                              "是這樣就在輸入一次這個命令。\n");
                        set_temp("pending/engage_to",query("id",  ob), me);
                        return 1;
                }
        } else
        {
                if (! living(witness))
                        return notify_fail("沒看見" + witness->name() +
                                           "現在趴在地上呢麼，你還是等一會兒吧。\n");

                if (witness->is_fighting())
                        return notify_fail(witness->name() + "現在正打架，" +
                                           "幫不上你的忙。\n");

                return witness->do_witness(me, ob);
        }

        msg=(query("gender", me) == "女性")?"$N含情脈脈的對$n道：“你娶了我吧！”\n"
                                              : "$N鄭重其事的對$n道：“你嫁給我吧！”\n";

        message_vision(msg, me, ob);
        if (! living(ob))
        {
                write("然而" + ob->name() + "昏迷不醒，無法理會你的請求。\n");
                return 1;
        }

        if (! userp(ob))
        {
                write("但是" + ob->name() + "面露難色，看來是作不了主。\n");
                return 1;
        }

        tell_object(ob, YEL + me->name(1) + "在向你求婚呢，你答應(right)還是不答應(refuse)？\n" NOR);
        set_temp("pending/answer/"+query("id", me)+"/right",
                     bind((: call_other, __FILE__, "do_right", ob, me :), ob), ob);
        set_temp("pending/answer/"+query("id", me)+"/refuse",
                     bind((: call_other, __FILE__, "do_refuse", ob, me :), ob), ob);
        set_temp("pending/engage", ob, me);

        return 1;
}

int do_right(object me, object ob)
{
        object witness;

        if (! ob || environment(ob) != environment(me))
                return notify_fail("可惜啊，人家已經不在這兒了。\n");

        if (! living(ob))
                return notify_fail("人家現在聽不到你說的話，還是算了吧。\n");

        if( query_temp("pending/engage", ob) != me )
                return notify_fail("人家現在已經不打算向你求婚了。\n");

        delete_temp("pending/engage", ob);

        if( query("couple", ob) )
                return notify_fail("人家已經結婚了，你還是不要去趟混水了！\n");

        if( query("couple", me) )
                return notify_fail("你可要穩住！根據泥潭法典第九十九條，重婚者打入地獄！\n");

        if( query("class", me) == "bonze" )
                return notify_fail("想結婚？還是先還俗吧！\n");

        if( query("class", ob) == "bonze" )
                return notify_fail("想結婚？還是先等人家還俗吧！\n");

        if( witness=query_temp("pending/marriage_witness", ob) )
                return witness->do_right(me, ob);

        if( query("gender", me) == "女性" )
        {
                switch(query("character", me) )
                {
                case "心狠手辣":
                        message_vision("$N微微冷笑道：好吧，本"
                                       "小姐姑且就同意你吧。\n", me, ob);
                        break;

                case "狡黠多變":
                        message_vision("$N羞答答的對$n道：好吧...\n", me, ob);
                        break;

                case "光明磊落":
                        message_vision("$N脆生生的對$n道：好吧！\n", me, ob);
                        break;

                default:
                        message_vision("$N望了望$n，嘻嘻笑道：好"
                                       "啊好啊，我最喜歡你了！\n", me, ob);
                        break;
                }
        } else
        {
                switch(query("character", me) )
                {
                case "心狠手辣":
                        message_vision("$N微微冷笑道：好吧，咱們就這樣！",
                                       me, ob);
                        break;

                case "狡黠多變":
                        message_vision("$N笑眯眯的對$n道：很好很好，我...我...\n", me, ob);
                        break;

                case "光明磊落":
                        message_vision("$N意氣風發的對$n道：好！\n", me, ob);
                        break;

                default:
                        message_vision("$N望了望$n，嘻嘻笑道：好"
                                       "啊好啊，我最喜歡你了！\n", me, ob);
                        break;
                }
        }

        set("couple/couple_id",query("id",  ob), me);
        set("couple/couple_name", ob->name(1), me);
        addn("static/marry", 1, me);
        me->save();
        set("couple/couple_id",query("id",  me), ob);
        set("couple/couple_name", me->name(1), ob);
        addn("static/marry", 1, ob);
        ob->save();
        CHANNEL_D->do_channel(this_object(), "rumor",
                              "恭喜" + me->name(1) + "和" +
                              ob->name(1) + "私定終身，" +
                              (random(2) ? "終結連理。" : "比翼雙飛。"));
        return 1;
}

int do_refuse(object me, object ob)
{
        object witness;

        if (! ob || environment(ob) != environment(me))
                return notify_fail("可惜啊，人家已經不在這兒了。\n");

        if (! living(ob))
                return notify_fail("人家現在聽不到你說的話，還是算了吧。\n");

        if( query_temp("pending/engage", ob) != me )
                return notify_fail("人家現在已經不打算向你求婚了。\n");

        delete_temp("pending/engage", ob);

        if( query("couple", me) )
        {
                message_vision("$N皺眉道：我已經結婚了，你的要求"
                               "我實在不能答應！\n", me, ob);
                return 1;
        }

        if( witness=query_temp("pending/marriage_witness", ob) )
                return witness->do_refuse(me, ob);

        if( query("gender", me) == "女性" )
        {
                switch(query("character", me) )
                {
                case "心狠手辣":
                        message_vision("$N橫眉冷目對$n罵道：滾！癩"
                                "蛤蟆想吃天鵝肉？\n", me, ob);
                        break;

                case "狡黠多變":
                        message_vision("$N莞而一笑，對$n道：不要了，"
                                "我怎麼看都不太合適，還是以後"
                                "再說吧！\n", me, ob);
                        break;

                case "光明磊落":
                        message_vision("$N幹幹脆脆的對$n道：我不同"
                                "意，你死了這條心吧！\n", me, ob);
                        break;

                default:
                        message_vision("$N望了望$n，冷笑道：要好，"
                                "拿出兩百萬兩黃金作聘禮，外加"
                                "三千顆菩提子再說吧！\n", me, ob);
                        break;
                }
        } else
        {
                switch(query("character", me) )
                {
                case "心狠手辣":
                        message_vision("$N橫眉冷目對$n罵道：滾！你"
                                "這臭婆娘！\n", me, ob);
                        break;

                case "狡黠多變":
                        message_vision("$N眼珠轉了幾轉，對$n道：何必"
                                "著急？這事兒咱們以後再說。\n", me, ob);
                        break;

                case "光明磊落":
                        message_vision("$N搖搖頭，對$n道：我這人配不"
                                "上你，你還是另尋高就吧！\n", me, ob);
                        break;

                default:
                        message_vision("$N望了望$n，姦笑兩聲道：咱們"
                                "何必結婚呢？這樣不也挺好的麼？\n", me, ob);
                        break;
                }
        }

        return 1;
}

int help(object me)
{
           write( @HELP
指令格式: engage <someone>

向某人提出求婚，如果你是和尚或是尼姑，還是算了吧！

see also : divorce
HELP );
           return 1;
}
