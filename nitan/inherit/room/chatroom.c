// chat room
// by Doing

#include <room.h>
#include <ansi.h>
#include <command.h>

inherit ROOM;

int is_chat_room() { return 1; }
int do_help(string arg);

string look_board();
int do_ban(string arg);
int do_invite(string arg);

void setup()
{
        set("channel_id", "聊天精靈");
        ::setup();
}

void create()
{
        set("short", "聊天室");
        set("long", @DESC
這裏什麼也沒有。
DESC );
        set("no_fight", 1);
        set("no_sleep_room",1);
        set("item_desc", ([
                "chalkboard" : (: look_board :),
        ]));

        setup();
}

void init_room(object out_room, object me)
{
        object board;

        set("owner_id",query("id", me));
        set("startroom", base_name(out_room));
        set("short",me->name(1)+"("+query("id", me)+")的聊天室");
        set("long", sort_string("這裏是" + me->name(1) + "為大家提供的聊"
                                "天室，中間幾個桌凳，上面零零散散的擺着茶"
                                "水和煙灰缸，地上則是一地的瓜子皮和煙頭，"
                                "除此之外空空蕩蕩的什麼也沒有。在門口歪歪"
                                "斜斜的放着一個黑板(chalkboard)，上面寫着"
                                "幾行字。\n", 64, 4));
        set("exits/out", base_name(out_room));

        if( query("env/auto_ban", me) )
                do_ban(query("env/auto_ban", me));

        if( query("env/auto_invite", me) )
                do_invite(query("env/auto_invite", me));

        CHANNEL_D->do_channel(out_room, "sys",
                              sprintf("%s(%s)在%s建立了一個聊天室。",
                                      me->name(1),query("id", me),
                                      out_room->short()));
        if (me->query_skill("idle-force", 1) >= 100)
        {
                board = new("/clone/board/chatroom_b");
                board->set_from_me(me, this_object());
        }
}

protected string look_board()
{
        string topic;

        if (! stringp(topic = query("topic")))
                return "海闊憑魚躍，天高任鳥飛 - 暢所欲言。\n";

        return "今天的話題是：" + topic + "\n";
}

int is_owner(object me)
{
        if( query("id", me) == query("owner_id") || 
            query("couple/id", me) == query("owner_id") )
                return 1;

        return notify_fail("你不是這個聊天室的主人，沒有發話的權利。\n");
}

int welcome(object me)
{
        string *ban;
        string *can;

        if (is_owner(me))
                return 1;

        if (query("ban_all"))
        {
                if (! arrayp(can = query("can")))
                        return notify_fail("現在主人不允許任何人進入這個聊天室。\n");

                if( member_array(query("id", me),can) == -1 )
                        return notify_fail("你現在不能進入這個聊天室。\n");
                return 1;
        }

        if (! arrayp(ban = query("ban")))
                return 1;

        if( member_array(query("id", me),ban) != -1 )
                return notify_fail("你現在不能進入這個聊天室。\n");

        return 1;
}

int invisible_for(object me)
{
        if (! query("secret") ||
            welcome(me))
                return 0;

        return 1;
}

int do_ban(string arg)
{
        object me;
        string *ban;
        string *can;
        string msg;
        string *all;
        int i;

        me = this_player();
        if (! is_owner(me) || arg && ! stringp(arg))
                return 0;

        if (! arrayp(ban = query("ban"))) ban = ({ });
        if (! arrayp(can = query("can"))) can = ({ });

        if (! arg)
        {
                if (query("ban_all"))
                {
                        write("你現在拒絕所有沒有經過邀請的人進入聊天室。\n");
                        return 1;
                }

                if (! sizeof(ban))
                {
                        write("你現在並沒有拒絕任何人進入聊天室。\n");
                        return 1;
                }

                msg = "你的黑名單：\n" HIR;
                for (i = 0; i < sizeof(ban); i++)
                {
                        msg += sprintf("%12-s", ban[i]);
                        if (! ((i + 1) % 4)) msg += "\n";
                }

                if (i % 4) msg += "\n";
                msg += NOR;
                write(msg);
                return 1;
        }

        if (arg == "all" || arg == "ALL" || arg == "-all" || arg == "-ALL")
        {
                if (! query("ban_all"))
                {
                        write("現在開始你將拒絕那些沒有經過邀"
                              "請的人進入聊天室。\n");
                        set("ban_all", 1);
                } else
                        write("你剛才已經拒絕那些沒有經過邀請"
                              "的人進入聊天室了。\n");
                return 1;
        }

        if (member_array(arg, ban) != -1)
        {
                write("此人現在已經被設定為拒絕入內的人士了。\n");
                return 1;
        }

        if( arg == query("id", me) )
        {
                write("拒絕你自己入內？你是不是大腦有問題？\n");
                return 1;
        }

        if (arg == query("owner_id"))
        {
                write("連屋主你也想關在外面？看來你是有點問題了。\n");
        }

        all = explode(arg, ",") - ({ "", query("owner") }) - ban;
        if (! sizeof(all))
        {
                write("這些人現在已經被設定為邀請入內的人士了。\n");
                return 1;
        }
        if (sizeof(ban) > 50)
        {
                write("夠了，你已經指定太多的人了，還不如干脆"
                      "許可所有的人(invite all)入內好了。\n");
                return 1;
        }

        ban += all;
        can -= all;
        arg = implode(all, ",");
        write("你將(" + arg + ")打入了黑名單，從現在開始拒絕其入內。\n");
        set("ban", ban);
        set("can", can);
        return 1;
}

int do_invite(string arg)
{
        object me;
        object ob;
        string *ban;
        string *can;
        string msg;
        string *all;
        int i;

        me = this_player();
        if (! is_owner(me) || arg && ! stringp(arg))
                return 0;

        if (! arrayp(ban = query("ban"))) ban = ({ });
        if (! arrayp(can = query("can"))) can = ({ });

        if (! arg)
        {
                if (! query("ban_all"))
                {
                        write("你現在同意任何沒有被拒絕的人進入聊天室。\n");
                        return 1;
                }

                if (! sizeof(can))
                {
                        write("你現在並沒有特別邀請任何人進入聊天室。\n");
                        return 1;
                }

                msg = "以下這些人是你特地關照要請進來的：\n" HIC;
                for (i = 0; i < sizeof(can); i++)
                {
                        msg += sprintf("%12-s", can[i]);
                        if (! ((i + 1) % 4)) msg += "\n";
                }

                if (i % 4) msg += "\n";
                msg += NOR;
                write(msg);
                return 1;
        }

        if (arg == "all" || arg == "ALL" || arg == "-all" || arg == "-ALL")
        {
                if (query("ban_all"))
                {
                        write("現在開始你同意讓所有沒有被打入"
                              "黑名單的人都能進入聊天室。\n");
                        delete("ban_all");
                } else
                        write("你已經同意讓所有沒有被打入黑名"
                              "單的人都能進入聊天室了。\n");
                return 1;
        }

        if (member_array(arg, can) != -1)
        {
                write("此人現在已經被設定為邀請入內的人士了。\n");
                return 1;
        }

        if( arg == query("id", me) )
        {
                write("邀請你自己？看來是沒有這個必要。\n");
                return 1;
        }

        if (arg == query("owner_id"))
        {
                write("邀請屋主麼？似乎多此一舉了。\n");
        }

        all=explode(arg,",")-({"",query("owner"),query("id", me)});
        all -= can;

        if (! sizeof(all))
        {
                write("這些人現在已經被設定為邀請入內的人士了。\n");
                return 1;
        }

        if (sizeof(can) > 50)
        {
                write("夠了，你已經指定太多的人了，還不如干脆"
                      "許可所有的人(invite all)入內好了。\n");
                return 1;
        }

        ban -= all;
        can += all;
        arg = implode(all, ",");
        write("你將(" + arg + ")列入邀請名單，從現在開始特別邀請他入內。\n");
        set("ban", ban);
        set("can", can);

        if (sizeof(all) == 1 &&
            objectp(ob = find_player(arg)) &&
            ! present(ob, this_object()))
                TELL_CMD->main(me, arg + " 來我的聊天室聊聊天吧！");
        return 1;
}

int do_kickout(string arg)
{
        object me;
        object ob;
        int i;

        me = this_player();
        if (! is_owner(me))
                return 0;

        if (! arg)
                return notify_fail("你要把誰踢出去？\n");

        ob = present(arg, this_object());
        if (! ob)
                return notify_fail("這裏沒有這個人啊！\n");

        if( query("id", ob) == "menshen" )
        {
                message_vision("$N把$n仔細的疊了起來收好。\n",
                               me, ob);
                destruct(ob);
                return 1;
        }

        if (! ob->is_character())
                return notify_fail("看清楚了，那可不是活人。\n");

        if (ob == me)
                return notify_fail("你大腦有水？\n");

        message_vision("$N飛起一腳，將$n咕嚕咕嚕的踢出門去！\n",
                       me, ob);
        ob->move(query("startroom"));
        ob->start_busy(3);
        message("vision", "只聽“啪嗒”一聲，" + ob->name() +
                "狼狽不堪的滾了出來，屁股上面還清清楚楚的留"
                "着一個鞋印。\n", environment(ob), ({ ob }));
        return 1;
}

int do_closechat()
{
        object me;
        object ob;
        object *obs;
        int i;

        me = this_player();
        if (! is_owner(me))
                return 0;

        message_vision("$N站起來，伸了個懶腰，道：走吧走吧，該走了。\n", me);
        obs = filter_array(deep_inventory(this_object()), (: userp :));
        for (i = 0; i < sizeof(obs); i++)
        {
                message_vision("$N走了出去。\n", obs[i]);
                obs[i]->move(query("startroom"));
                if (living(obs[i]))
                        message("vision", obs[i]->name() + "從" + short() +
                                "裏面走了出來。\n", environment(obs[i]), ({ obs[i] }));
                else
                        message("visoin", obs[i]->name() + "被人從" + short() +
                                "裏面抬了出來。\n", environment(obs[i]), ({ obs[i] }));
        }
        CHANNEL_D->do_channel(this_object(), "sys",
                              sprintf("%s被%s(%s)拆除了。",
                                      short(),
                                      me->name(1),query("id", me)));
        destruct(this_object());
        return 1;
}

int do_summon(string arg)
{
        object ob;

        if (! is_owner(this_player()))
                return 0;

        if (arg != "menshen" && arg != "men shen")
                return notify_fail("你要召喚什麼？\n");

        if (objectp(present("men shen", this_object())))
        {
                write("這裏已經有門神為你把守了。\n");
                return 1;
        }

        if (this_player()->query_skill("idle-force", 1) < 100)
        {
                write("你的發呆神功水平有限，還無法發呆出一個門神來。\n");
                return 1;
        }

        ob = new("/clone/npc/menshen");
        message_vision("$N忽然不説話了，發了一會兒呆，過了一"
                       "陣，突然天上掉下一張年畫，\n上面畫着"
                       "一個威武雄壯的門神。$N把它揀了起來，"
                       "貼在門上面。\n", this_player());
        ob->move(this_object());
        return 1;
}

int do_secret(string arg)
{
        object me;

        if (! arg)
        {
                write("現在聊天室" + (query("secret") ? "處於祕密狀態。\n"
                                                      : "處於公開狀態。\n"));
                return 1;
        }

        me = this_player();
        if (! is_owner(me))
                return 0;

        if (arg == "on" || arg == "ON" || arg == "+")
        {
                if (query("secret"))
                {
                        write("現在聊天室已經是祕密的了。\n");
                        return 1;
                }

                message_vision("$N神神祕祕的看了看四周，把手指豎在"
                               "脣前，小聲道：“籲”。\n", me);
                set("secret", 1);
                message("vision", HIG "現在聊天室已經是祕密的了。\n" NOR,
                        all_inventory());
        } else
        if (arg == "off" || arg == "OFF" || arg == "-")
        {
                if (! query("secret"))
                {
                        write("現在聊天室並不是祕密的。\n");
                        return 1;
                }

                message_vision("$N鬼鬼祟祟的看了看四周，道：“大家是不"
                               "是都説完悄悄話了？”\n", me);
                delete("secret");
                message("vision", HIC "現在聊天室已經是公開的了。\n" NOR,
                        all_inventory());
        } else
                do_help("secret");

        return 1;
}

int do_topic(string arg)
{
        object me;
        object ob;

        me = this_player();
        if (! is_owner(me))
                return 0;

        if (! arg)
        {
                if (query("topic"))
                        write("目前的話題是：" + query("topic") + "。\n");
                else
                        write("目前沒有限制什麼話題。\n");
                write("你打算指定什麼新話題？\n");
                return 1;
        }

        if (arg == "none")
        {
                delete("topic");
                message_vision("$N道：大家隨便聊聊吧，不必拘泥於某個話題。\n", me);
                return 1;
        }

        set("topic", arg);
        message_vision("$N道：咱們今天不如談談『" + arg + "』這個話題。\n"
                       "説完從地上找到一根粉筆在黑板上胡亂塗了幾行字。\n", me);
        return 1;
}

int do_help(string arg)
{
        switch (arg)
        {
        case "here":
                write(@HELP
在這裏你可以使用以下這些和聊天室相關的命令：
    ban          禁止某些人訪問聊天室
    closechat    關閉這個聊天室(所有人都被踢出)
    invite       邀請某個人進入聊天室
    kickout      將某個人踢出聊天室
    summon       呼叫神靈
    look         看看聊天室裏面都有誰
    out          離開聊天室
    topic        設置聊天室的話題
HELP );
                break;

        case "ban":
                write(@HELP_BAN
指令格式 : ban <玩家ID> [all]

此指令讓你禁止指定的玩家進入你的聊天室。如果指明的參數是 all
則禁止所有的玩家進入，這時只有那些經過邀請的玩家才能進入。這
條指令不會影響此時已經在聊天室內的玩家。如果一次需要禁止多個
玩家，可以用逗號分開，比如：ban xxx,yyy,zzz。 在聊天室剛剛建
立好的時候會自動執行ban auto_ban，其中auto_ban是你設置的參數。

相關指令：kickout, invite
HELP_BAN );
                break;

        case "closechat":
                write(@HELP_CLOSECHAT
指令格式 : closechat

關閉這個聊天室。

HELP_CLOSECHAT );

        case "invite":
                write(@HELP_BAN
指令格式 : invite <玩家ID> [all]

此指令讓你邀請指定的玩家進入你的聊天室。如果先前這個玩家被指
明禁止進入，這此時狀態取消，同時如果玩家可以接收tell的話將會
收到你的邀請信息。如果指明的參數是 all則表明取消禁止所有的玩
家進入的限制，這是相對ban all 而言的。如果一次需要邀請多個玩
家，可以用逗號分開，比如：ban xxx,yyy,zzz。 在聊天室剛剛建立
好的時候會自動執行invite auto_invite， 其中auto_invite是你設
置的參數。

相關指令：kickout, ban
HELP_BAN );
                break;

        case "kickout":
                write(@HELP_BAN
指令格式 : invite <玩家ID>

踢出某一個搗亂的玩家，如果ID是men shen則把門神收起來。

相關指令：ban, invite
HELP_BAN );
                break;

        case "summon":
                write(@HELP_SUMMON
指令格式 : summon menshen

如果你有一百級的發呆神功，在你自己的聊天室裏面就可以使用這條
命令呼叫門神幫你把守聊天室，自動踢出那些混進聊天室的人。
HELP_SUMMON );
                break;

        case "topic":
                write(@HELP_BAN
指令格式 : topic <任意信息> | <none>

指定一個聊天的話題。

HELP_BAN );
                break;

        case "secret":
                write(@HELP_SECRET
指令格式 : secret [+ | on | - | off]

使自己的聊天室成為祕密的聊天室，或者解除祕密狀態。

HELP_SECRET );
                break;

        default:
                return notify_fail("你要查看什麼幫助？\n");
        }

        return 1;
}

void add_all_action()
{
        // add all action for this_player()
        add_action("do_ban", "ban");
        add_action("do_closechat", "closechat");
        add_action("do_invite", "invite");
        add_action("do_kickout", "kickout");
        add_action("do_invite", "invite");
        add_action("do_topic", "topic");
        add_action("do_help", "help");
        add_action("do_secret", "secret");
        add_action("do_summon", "summon");
}

void init()
{
        add_all_action();
}

int clean_up()
{
        object *obs;

        // 聊天室裏面有玩家、聊天魂魄、LV10兵器則不析構
        obs = filter_array(all_inventory(), (: userp($1) || playerp($1) || $1->is_chatter() ||
                                               $1->is_item_make() && $1->is_stay_in_room() :));
        if (! sizeof(obs))
        {
                destruct(this_object());
                return 0;
        }

        return 1;
}
