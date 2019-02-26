#include <ansi.h>
#include <command.h>

inherit NPC;

void create()
{
        set_name("店小二", ({ "xiao er", "xiao", "waiter" }) );
        set("gender", "男性" );
        set("age", 22);
        set("long", "這位店小二正笑咪咪地忙著，還不時拿起掛在脖子上的抹布擦臉。\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "小二哥");
        setup();
        if (clonep()) keep_heart_beat();
}

string accept_ask(object me, string topic)
{
        switch (random(5))
        {
        case 0:
                return "嗨！我忙着呢，你和我那醉仙樓做活的兄弟聊聊吧！";

        case 1:
                return "你幹啥？沒看我忙着呢麼？";

        case 2:
                return "哎呀呀，你沒看我忙着呢麼，要打聽消息你去找我醉仙樓做活的兄弟吧？";

        case 3:
                return "春來茶館的老闆娘阿慶嫂消息也靈通，那些爺們什麼都告訴她，要不你問她去？";

        default:
               return "我那醉仙樓做活的兄弟消息才叫靈通，你去和他聊吧。";
        }
}

void init()
{       
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        // add_action("do_drop", "drop");
}

void greeting(object ob)
{
        if ( ! ob || environment(ob) != environment() ) return;
        switch( random(2) )
        {
        case 0:
                say( CYN "店小二笑咪咪地説道：這位" + RANK_D->query_respect(ob)
                   + CYN + "，進來喝杯茶，歇歇腿吧。\n" NOR);
                break;
        case 1:
                say( CYN "店小二用脖子上的毛巾抹了抹手，説道：這位" + RANK_D->query_respect(ob)
                   + CYN + "，請進請進。\n" NOR);
                break;
        }
}

int accept_object(object me, object ob)
{
        
        if( query("money_id", ob) && ob->value() >= 1000 )
        {
                tell_object(me, CYN "小二一哈腰，説道：多謝您老，客官請上樓歇息。\n" NOR);
                set_temp("rent_paid", 1, me);
                return 1;
        }

        switch (random(6))
        {
        case 0:
                command("say 好！好！");
                break;
        case 1:
                command("say 不需要的東西全給我！");
                break;
        }

        if (! ob->is_character())
        {
                destruct(ob);
                return -1;
        }
        return 1;
}

void heart_beat()
{
        string start_room;
        object ob;

        if (stringp(start_room = query("startroom"))
           && find_object(start_room) == environment())
        {
                foreach (ob in all_inventory(environment()))
                {
                        if (! ob->is_character()
                           || interactive(ob)
                           || playerp(ob)
                            || query_temp("owner", ob) )
                                continue;

                        if( stringp(start_room=query("startroom", ob) )
                           && find_object(start_room) == environment())
                                continue;

                        if( query("id", ob) == "corpse" )
                                message_vision(HIC "\n$N" HIC "站起身，把$n" HIC "拎到"
                                               "門外，然後又若無其事地走了回來。\n\n"
                                               NOR, this_object(), ob);
                        else if( query("race", ob) != "野獸" )
                                message_vision(CYN "\n$N" CYN "對$n" CYN "滿臉歉然地説"
                                               "道：對不住，小店已經滿座了。\n" HIC "$n"
                                               HIC "聽後一愣，搖了搖頭，罵罵咧咧地轉身"
                                               "離去。\n" NOR, this_object(), ob);
                        ob->move("/d/city/beidajie1");
                }
        }
        ::heart_beat();
}

int do_drop(string arg)
{
        int i;
        object *obs;
        object ob;
        object me;

        if (! arg)
                return 0;

        me = this_player();
        if (objectp(ob = present(arg, me)) &&
            ob->is_character() && ! playerp(ob))
        {
                addn_temp("static/drop_npc", 1, me);
                if( query_temp("static/drop_npc", me)>1 && 
                    query("combat_exp", me) >= 50000 )
                {
                        message_vision(CYN "\n$N" CYN "大怒道：好你個" + RANK_D->query_rude(ob)
                                       + CYN "，還敢來添亂？\n" NOR + HIC "説罷$N" HIC "一聲大"
                                       "叫，北醜頓時衝了出來，飛起兩腳，將$n" HIC "和" + ob->name()
                                       + HIC "一起踢了出去。\n\n" NOR, this_object(), me);

                        ob->move("/d/city/beidajie1");
                        me->move("/d/city/beidajie1");
                        message("vision", HIC "只聽客店處砰叮咣啷一陣轟響，便見" + me->name()
                                          + HIC "和" + ob->name() + HIC "一起飛了出來。\n"
                                          NOR, environment(me), me);

                        me->receive_damage("qi", 1);
                        ob->die();
                        me->unconcious();
                        return 1;
                }

                message_vision(CYN "\n$N" CYN "怒道：晦氣，晦氣！這裏又不是棺材店，你搬個要死"
                               "的人進來幹嘛？\n" NOR + HIC "説罷$N" HIC "一招手，頓時來了一羣"
                               "彪形大漢，將$n" HIC "和" + ob->name() + HIC "一起趕了出去。\n\n"
                               NOR, this_object(), me);

                ob->move("/d/city/beidajie1");
                me->move("/d/city/beidajie1");
                message("vision", HIC "只聽客店處傳來一陣轟鬧聲，" + me->name() + HIC "被人趕"
                                  "了出來，隨後半死不活的" + ob->name() + HIC "也被扔了出來。"
                                  "\n" NOR, environment(me), me);
                me->receive_damage("qi", 1);
                return 1;
        }

        if (! DROP_CMD->main(me, arg))
                return 0;

        if (! GET_CMD->main(this_object(), arg))
                return 1;

        obs = all_inventory(this_object());
        for (i = 0; i < sizeof(obs); i++)
                if (! obs[i]->is_character()) destruct(obs[i]);
        if (! random(5))
        {
                switch (random(4))
                {
                case 0:
                        command("say 你不要我要！");
                        break;
                case 1:
                        command("sigh"+query("id", this_player()));
                        command("say 糟蹋啊，作孽啊！");
                        break;
                case 2:
                        command("say 敗家子，敗家子！");
                        break;
                default:
                        command("heihei");
                        break;
                }
        }
        return 1;
}