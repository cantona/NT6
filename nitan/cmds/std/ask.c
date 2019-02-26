// ask.c

#include <ansi.h>

inherit F_CLEAN_UP;

string query_inquiry(object me, object ob);

string *msg_dunno = ({
        "$n搖搖頭，説道：沒聽説過。\n",
        "$n疑惑地看着$N，搖了搖頭。\n",
        "$n睜大眼睛望着$N，顯然不知道$P在説什麼。\n",
        "$n聳了聳肩，很抱歉地説：無可奉告。\n",
        "$n説道：嗯....這我可不清楚，你最好問問別人吧。\n",
        "$n想了一會兒，説道：對不起，你問的事我實在沒有印象。\n"
});

int main(object me, string arg)
{
        string dest, topic;
        mixed msg;
        object ob;
        mapping inquiry;
        object env;
        mixed info;

        seteuid(getuid());

        if (! arg)
                return notify_fail("你要問誰什麼事？\n");

        if (sscanf(arg, "%s about %s", dest, topic) != 2 &&
            sscanf(arg, "%s %s", dest, topic) != 2)
                return notify_fail("你要問誰什麼事？\n");

        if( topic == "quest_name" && query("quest/name", me) )
                topic=query("quest/name", me);

        env = environment(me);
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

        if (! objectp(ob = present(dest, env)))
                return notify_fail("這裏沒有這個人。\n");

        /*
        if (me->ban_say(1) && playerp(ob))
                return 0;
        */

        if (! ob->is_character())
        {
                message_vision("$N對着$n自言自語....\n", me, ob);
                return 1;
        }

        if (ob == me)
        {
                message_vision("$N自己自言自語。\n", me);
                return 1;
        }

        if( query("jing", me)<30 && !playerp(ob) && !me->is_ghost() )
        {
                write("你現在的精神不太好，沒法和別人套瓷。\n");
                return 1;
        }

        if( !query("can_speak", ob) )
        {
                message_vision(CYN "$N" CYN "向$n" CYN 
                               "打聽有關『" HIG + topic + NOR CYN "』"
                               "的消息，但是$p顯然聽不懂人話。\n" NOR, me, ob);
                return 1;
        }

        if (! INQUIRY_D->parse_inquiry(me, ob, topic))
        if( query("id", ob) != "you xun" )
                message_vision(CYN "$N" CYN "向$n" CYN "打聽有關『" HIG +
                               topic + NOR CYN "』的消息。\n" NOR, me, ob);

        if (! living(ob))
        {
                message_vision("但是很顯然的，$n現在的狀況沒有辦法給$N任何答覆。\n",
                        me, ob);
                return 1;
        }

        if (playerp(ob) || ob->is_chatter())
        {
                set_temp("ask_you",query("id",  me), ob);
                return 1;
        }

//        if (! me->is_ghost()) me->receive_damage("jing", 10 + random(10));
        if( msg=query("inquiry/"+topic, ob) || 
            msg = ob->accept_ask(me, topic))
        {
                if (functionp(msg))
                        // msg = (*msg)(msg, ob); 
                        msg = evaluate(msg, ob); 

                if (stringp(msg))
                {
                        // message_vision(CYN "$N對$n説道：" + msg + "\n" NOR, ob, me);
                        tell_object(me, CYN + ob->name() + CYN "對你説道：" + msg + "\n" NOR);
                        return 1;
                }
        } else
        if (topic == "all")
        {               
                 query_inquiry(me, ob);
                 return 1;
        } else
                message_vision(msg_dunno[random(sizeof(msg_dunno))], me, ob);

        return 1;
}

// 從 npc 身上讀取 inquiry
string query_inquiry(object me, object ob)
{
        int i = 0;
        mapping inq;
        string str = "";
        string *indexs;
        
        if( mapp(inq=query("inquiry", ob)) )
        {
                indexs = keys(inq);
                for (i = 0; i < sizeof(indexs); i++)
                {
                        //str = indexs[i] + " " + str;
                        str += HIY "第"+chinese_number(i+1)+"條："HIG+indexs[i]+"\n" NOR;
                }
                str = "有關於\n" + str + "\n這些事情，你若想知道的話可以問我！";
                tell_room(environment(me), CYN + ob->name() + "在" + me->name() + "耳邊小聲地説了些話。\n" NOR, ({ me, ob }));
                tell_object( me, GRN + ob->name() + "在你的耳邊悄聲説道：" + str + "\n" NOR);
                return "\n";
        }
        tell_object( me, ob->name(1) + "對你説道：實在是對不起，我什麼也不知道呀！\n");
        return "\n";
}

int help(object me)
{
        write( @HELP
指令格式: ask <someone> about <something>

這個指令在解謎時很重要, 通常必須藉由此一指令才能
獲得進一步的資訊。
預設的詢問主題:
        here
        name
        all
        clue
        rumor

其中的about可以省略。
HELP );
        return 1;
}
