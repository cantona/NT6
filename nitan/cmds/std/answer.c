// reply.c

#include <ansi.h>
#include <net/dns.h>

inherit F_CLEAN_UP;

int help(object me);

int main(object me, string arg)
{
        string st, target;
        object ob, obj, env;
        mixed info;

        if (! arg || arg == "")
                return notify_fail("你要回答什麼？\n");

        env = environment(me);

        if( query_temp("quest_gift/npc", me) )
        {
                int gift, gongxian;
                string un;

                obj=query_temp("quest_gift/npc", me);
                obj = present(obj, env);

                gongxian=query_temp("quest_gift/gongxian", me);

                if (arg == "Y" || arg == "y" || arg == "yes")
                        gift = 2;

                if (arg == "N" || arg == "n" || arg == "no")
                        gift = 1;

                if (objectp(obj) && environment(obj) == env
                   && living(obj) && gift == 2)
                {
                        if( query_temp("quest_gift/skill", me) )
                        {
                                message_vision( CYN "\n$N" CYN "急忙點點頭，說"
                                                "道：這武功正好我也想學，就傳授給"
                                                "我吧。\n" NOR, me );

                                if( query("family/gongji", me)<gongxian )
                                {
                                        message_vision( CYN "$N" CYN "突然一愣"
                                                        "，說道：嗯？這個…你最"
                                                        "近還不夠努力…下次吧。"
                                                        "\n" NOR, obj );
                                        delete_temp("quest_gift", me);
                                        return notify_fail(HIY "看來是你的門派"
                                                        "貢獻值不夠了。\n" NOR);
                                }

                                me->set_skill(query_temp("quest_gift/skill", me),180);
                                addn("family/gongji", -gongxian, me);


                                message_vision( HIY "$n" HIY "微微一笑，將"
                                                +to_chinese(query_temp("quest_gift/skill", me))+
                                                HIY "傳授給$N" HIY "。\n" NOR,
                                                me, obj );
                        }
                        else
                        {
                                message_vision( CYN "\n$N" CYN "急忙點點頭，說"
                                                "道：這東西正好我也需要，就交給"
                                                "我吧。\n" NOR, me );

                                if( query("family/gongji", me)<gongxian )
                                {
                                        message_vision( CYN "$N" CYN "突然一愣"
                                                        "，說道：嗯？這個…你最"
                                                        "近還不夠努力…下次吧。"
                                                        "\n" NOR, obj );
                                        delete_temp("quest_gift", me);
                                        return notify_fail(HIY "看來是你的門派"
                                                        "貢獻值不夠了。\n" NOR);
                                }

                                ob=new(query_temp("quest_gift/obj", me));

                                if (! ob)
                                {
                                        message_vision(CYN "$N" CYN "納悶道："
                                                        "咦？我的東西呢？剛才還"
                                                        "在，怎麼突然就沒了。\n"
                                                        NOR, obj);
                                                delete_temp("quest_gift", me);
                                        return notify_fail("物品文件出現了問題"
                                                        "，請與巫師聯系。\n");
                                }

                                if( query("base_unit", ob) )
                                        un=query("base_unit", ob);
                                else
                                        un=query("unit", ob);

                                addn("family/gongji", -gongxian, me);

                                message_vision( CYN "$n" CYN "微微一笑，從懷中"
                                                "取出一" + un + ob->name() +
                                                CYN "交給$N" CYN "。\n" NOR,
                                                me, obj );
                                ob->move(me, 1);
                        }
                        delete_temp("quest_gift", me);
                        return 1;

                } else
                if (objectp(obj) && environment(obj) == env
                   && living(obj) && gift == 1)
                {
                        if( query_temp("quest_gift/skill", me) )
                        {
                                message_vision(CYN "\n$N" CYN "頗為尷尬的說道："
                                       "嗯…我對這個武功沒有興趣，還"
                                       "是算了吧。\n" NOR, me);

                                message_vision(CYN "$n" CYN "對$N" CYN "嘆氣道"
                                       "：也罷，既然你不想學，這武功我"
                                       "就傳授給別人吧。\n" NOR, me, obj);
                        }
                        else
                        {
                                message_vision(CYN "\n$N" CYN "頗為尷尬的說道："
                                       "嗯…我現在拿這東西也無用處，還"
                                       "是算了吧。\n" NOR, me);

                                message_vision(CYN "$n" CYN "對$N" CYN "嘆氣道"
                                       "：也罷，既然你不需要，這東西我"
                                       "就留給別人吧。\n" NOR, me, obj);
                        }

                        delete_temp("quest_gift", me);
                        return 1;
                }
        } else
                obj = 0;

        if (sscanf(arg, "%s %s", st, arg) == 2 &&
            ! objectp(obj = present(st, env)))
        {
                arg = st + " " + arg;
        }

        if( info=query("no_say", env) )
        {
                if (stringp(info))
                {
                        write(info);
                        return 1;
                }

                write("這個地方不能講話。\n");
                return 1;
        }

        if( !stringp(target=query_temp("ask_you", me)) )
                return notify_fail("剛才沒有人向你詢問。\n");

        if (me->ban_say(1))
                return 0;

        if (objectp(obj) && ! playerp(obj) && ! obj->is_chatter())
                obj = 0;

        if (! obj) obj = find_player(target);
        if (! obj) obj = MESSAGE_D->find_user(target);

        if (! obj)
                return notify_fail("剛才向你詢問的人現在無法聽見你，或"
                                   "者已經離開遊戲了。\n");

        if (environment(obj) != environment(me))
                return notify_fail("剛才向你詢問的人現在不再這裡了。\n");

        message_vision(CYN "$N" CYN "回答$n" CYN
                       "：『" HIG + arg + NOR CYN "』\n" NOR, me, obj);

        if (userp(obj) || obj->is_chatter())
        {
                set_temp("ask_you",query("id",  me), obj);
                return 1;
        }

        return 1;
}

int help(object me)
{
        write(@HELP
指令格式：answer [ <player> ] <訊息>

你可以用這個指令和剛才用 ask 和你說話的使用者說話，如果
指明了玩家則回答指定的玩家。

see also : tell
HELP
        );
        return 1;
}