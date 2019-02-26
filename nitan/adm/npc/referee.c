// referee.c 公平子

inherit NPC;
#include <ansi.h>;

int do_bihua(string arg);
int do_no();
void shout_message(string msg);

void create()
{
        set_name("公平子", ({ "gongping zi", "zi", "referee" }) );
        set("gender", "男性");
        set("age", 35);
        set("no_get", 1);
        set("long",
                "這是一位仙風道骨的中年道人，早年雲遊四方，性好任俠，公正無私。\n");
        set("combat_exp", 60000);
        set("shen_type", 1);
        set("attitude", "friendly");

        set("apply/attack", 50);
        set("apply/defense", 50);

        set("max_qi", 800);
        set("max_jing", 800);
        set("max_neili", 800);

        setup();

        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}


void init()
{
        ::init();
        add_action("do_team", "team");
        add_action("do_bihua", "bihua");
        add_action("do_bihua", "bi");
        add_action("do_bihua", "hit");
        add_action("do_bihua", "fight");
        add_action("do_bihua", "qiecuo");
        add_action("do_halt", "halt");
        add_action("do_halt", "h");
        add_action("do_no", "beg");
        add_action("do_no", "steal");
        add_action("do_no", "quanjia");
        add_action("do_no", "persuade");
        add_action("do_no", "touxi");
        add_action("do_no", "ansuan");
        add_action("do_no", "kill");
}

int do_team(string arg)
{
        if (! arg)
                return 0;

        if (sscanf(arg, "kill %*s") == 1)
        {
                message_vision("$N飛上前來就給了$n一個耳光，$n當場暈了過去。\n",
                               this_object(), this_player());
                this_player()->unconcious();
                return 1;
        }

        return 0;
}

int do_bihua(string arg)
{
        object me;
        object ob;
        object old;

        if (! arg || ! objectp(ob = present(arg)))
        {
                write("你要和誰比劃？\n");
                return 1;
        }

        me = this_player();
        if (me == ob)
        {
                write("你是不是以為天下就你自己是老大，再沒有第二個英雄了。\n");
                return 1;
        }

        if (! userp(ob))
        {
                write("你想向人家挑戰，可是人家根本沒有理你。\n");
                return 1;
        }

        if (! living(ob))
        {
                write("你還是等人家醒了再説吧。\n");
                return 1;
        }

        if (me->is_fighting() && me->query_competitor())
        {
                write("你現在正在和" + me->query_competitor()->name() +
                      "比試呢。\n");
                return 1;
        }

        if (ob->is_fighting())
        {
                write("人家正在動手，你上去插手幹什麼？\n");
                return 1;
        }

        if( query("qi", me)*100/query("max_qi", me)<70 )
        {
                write("你現在體力不夠充沛，何必忙着動手？\n");
                return 1;
        }

        if( query("qi", ob)*100/query("max_qi", ob)<70 )
        {
                write("人家現在似乎體力不支，還是等會兒再説吧。\n");
                return 1;
        }

        if( query("combat_exp", me)<10000 )
        {
                write("公平子冷笑道：你是哪兒來的？我怎麼從來沒有"
                      "聽説過？滾開！少在這裏添亂。\n");
                return 1;
        }

        if( query("combat_exp", ob)<10000 )
        {
                write("公平子看看你道：算了吧，" + ob->name() +
                      "武功低微，你出手似乎有失身份。\n");
                return 1;
        }

        if( old=query_temp("pending/fight", me) )
        {
                if (old == ob)
                {
                        write("你正在向人家挑戰，可是人家還沒有答應。\n");
                        return 1;
                }

                tell_object(old, me->name() + "改變主意不想向你挑戰了。\n");
                tell_object(me, "你改變主意不打算向" + old->name() + "挑戰了。\n");
        }

        if( query_temp("pending/fight", ob) != me )
        {
                set_temp("pending/fight", ob, me);
                message_vision(HIY "\n$N" HIY "朗聲對$n" HIY "道：今日幸會，我們何不一較"
                               "高低，就由" + name() + "先生為我們見證可好？\n\n" NOR,
                               me, ob);
                return 1;
        }

        delete_temp("pending/fight", ob);

        message_vision(HIY "\n$N" HIY "點頭道：很好，來吧，不必客氣！\n\n" NOR,
                       me, ob);

        shout_message(me->name(1)+"("+query("id", me)+")道："+
                      RANK_D->query_self(me) + me->name(1) + "，今日特向" +
                      RANK_D->query_respect(ob) + "請教。");
        me->set_override("win",  bind((: call_other, __FILE__, "player_win",  environment() :), me));
        me->set_override("lost", bind((: call_other, __FILE__, "player_lost", environment() :), me));
        ob->set_override("win",  bind((: call_other, __FILE__, "player_win",  environment() :), ob));
        ob->set_override("lost", bind((: call_other, __FILE__, "player_lost", environment() :), ob));
        me->competition_with(ob);
        return 1;
}

void player_win(object env, object me)
{
        object ob;

        ob = me->query_competitor();
        if (! objectp(ob))
        {
                shout_message(name() + "歎道：這次比武，" + me->name(1) + "獲勝。");
                return;
        }

        if (environment(ob) != environment(me))
        {
                shout_message(name() + "笑道：" + ob->name(1) +
                              "比武時臨陣脱逃，" + me->name(1) + "不戰而勝。");
        } else
        if( query("age", me)>query("age", ob) )
        {
                shout_message(name() + "點頭道：姜果然還是是老的辣，今日" +
                              me->name(1) + "比武戰勝" + ob->name(1) + "！");
        } else
        if( query("age", me)>query("age", ob) )
        {
                shout_message(name() + "讚道：今日" + me->name(1) + "比武戰勝" +
                              ob->name(1) + "，真可謂是長江後浪推前浪！");
        } else
        {
                shout_message(name() + "道：" + me->name(1) + "比武戰勝" +
                              ob->name(1) + "，恭喜恭喜。");
        }
}

void player_lost(object env, object me)
{
        mapping exits;
        string exit;

        if( environment(me) != env || !mapp(exits=query("exits", env)) )
                return;

        exit = values(exits)[random(sizeof(exits))];
        me->move(exit);
        tell_room(env, "只見" + me->name() + "大叫一聲，跌了下去。\n");
        message_vision("只見$N咕嚕咕嚕的滾下了擂台，哼哼呀呀的在地上躺了半天。\n", me);
}

int do_no()
{
        command("say " + this_player()->name() + "！這裏眾目睽睽，豈能做此不才之事？");
        return 1;
}

int accept_ansuan(object ob)
{
        message("vision", "一個黑影撲來，" + name() +
                "隨手一揮，把" + ob->name() + "彈了出去，摔了個灰頭土臉。\n",
                environment());
        tell_object(ob, "你縱身撲去，去被" + name() + "伸手一揮，把你彈了回來。\n");
        return notify_fail("人家武功太高，你還是老老實實的不要亂動。\n");
}

void receive_damage(string type, int count) {}

void kill_ob(object ob) {}

void fight_ob(object ob) {}

void shout_message(string msg)
{
        message("channel:chat", HIW "【以武會友】" + msg + "\n" NOR,
                all_interactive());
}

int want_receive_msg() { return 1; }

void receive_message(string msgclass, string msg)
{
        object ob;
        object *bct;

        if (! objectp(ob = environment()) ||
            ! arrayp(bct = ob->broadcast_to()))
        {
                // needn't broadcast to others
                return;
        }

        message("vision", WHT "【武林快報】" NOR + BBLU +
                          replace_string(msg, NOR, BBLU) + NOR,
                bct);
}