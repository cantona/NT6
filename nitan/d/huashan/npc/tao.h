// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

int accept_fight(object ob)
{
        object me = this_object();
        object ob1, ob2, ob3, ob4, ob5, ob6;
        string msg1, msg2, msg3, msg4, msg5, msg6;
        int my_max_qi=query("max_qi", me);

        /*
        if (query_competitor() == ob)
                return 1;
        */

        if (query("qi") < query("eff_qi") * 2 / 3
            || query("jing") < query("eff_jing") * 2 / 3
            || query("neili") < query("max_neili") * 2 / 3)
        {
                // command("say 我現在有點疲倦，待我歇會兒再説。");
                return 0;
        }

        ob1 = present("tao genxian", environment(me));
        ob2 = present("tao ganxian", environment(me));
        ob3 = present("tao zhixian", environment(me));
        ob4 = present("tao yexian", environment(me));
        ob5 = present("tao huaxian", environment(me));
        ob6 = present("tao shixian", environment(me));

        msg1 = "桃根仙突然逼近$N，一把向$N的左手捉去。\n";
        msg2 = "桃幹仙突然逼近$N，一把向$N的右手捉去。\n";
        msg3 = "桃枝仙突然逼近$N，一把向$N的左腳捉去。\n";
        msg4 = "桃葉仙突然逼近$N，一把向$N的右腳捉去。\n";
        msg5 = "桃花仙突然逼近$N，一把向$N的左手捉去。\n";
        msg6 = "桃實仙突然逼近$N，一把向$N的右腳捉去。\n";

        command( "say 大夥兒準備。" );
        competition_with(ob);

        if (objectp(ob1) && ob1 != me) call_out("tear_and_kill", random(5), ob1, ob, msg1);
        if (objectp(ob2) && ob2 != me) call_out("tear_and_kill", random(5), ob2, ob, msg2);
        if (objectp(ob3) && ob3 != me) call_out("tear_and_kill", random(5), ob3, ob, msg3);
        if (objectp(ob4) && ob4 != me) call_out("tear_and_kill", random(5), ob4, ob, msg4);
        if (objectp(ob5) && ob5 != me) call_out("tear_and_kill", random(5), ob5, ob, msg5);
        if (objectp(ob6) && ob6 != me) call_out("tear_and_kill", random(5), ob6, ob, msg6);

        return 1;
}

string ask_me()
{
        return "你打得過咱們六兄弟，我自然會帶你去見他。";
}

int accept_kill(object ob)
{
        object me = this_object();
        object ob1, ob2, ob3, ob4, ob5, ob6;

        delete_temp("win", ob);
        command( "say 你想謀材害命不成，是不是妒忌咱們六兄弟名滿江湖？\n");

        if (objectp(ob1 = present("tao genxian", environment(me)))) ob1->kill_ob(ob);
        if (objectp(ob2 = present("tao ganxian", environment(me)))) ob2->kill_ob(ob);
        if (objectp(ob3 = present("tao zhixian", environment(me)))) ob3->kill_ob(ob);
        if (objectp(ob4 = present("tao yexian",  environment(me)))) ob4->kill_ob(ob);
        if (objectp(ob5 = present("tao huaxian", environment(me)))) ob5->kill_ob(ob);
        if (objectp(ob6 = present("tao shixian", environment(me)))) ob6->kill_ob(ob);

        return 1;
}

int tear_and_kill(object me, object ob, string msg)
{
    // 這個函數是延時呼叫的，所以執行前先要判斷兩個物件都否都還在
    if (! objectp(ob) || !objectp(me))
        return 1;

        if( !ob->is_fighting(me) || query("qi", ob)*2 >= query("max_qi", ob) )
        {
                delete_temp("caught", ob);
                return 1;
        }

        message_combatd(msg, ob);

        if( random(query("combat_exp", me))>query("combat_exp", ob)/2 )
        {
                addn_temp("caught", 1, ob);
                message_combatd("結果$N被" + me->name() + "捉個正着！\n", ob);
                if( query_temp("caught", ob) == 4 )
                {
                        message_combatd("\n桃谷六仙捉着$N四肢猛然一扯，$N只覺得一陣劇痛，便失去知覺了。\n", ob);
                        delete_temp("caught", ob);
                        ob->unconcious();
                        set_temp("die_reason", "被桃谷六仙撕成四塊了", ob);
                        ob->remove_all_enemy(0);
                        me->remove_all_enemy(0);
                        ob->die();
                        CHANNEL_D->do_channel(me,"chat",sprintf("%s被桃谷六仙撕成四塊了！",ob->name()));
                }
        } else
        {
                message_combatd("$N成功地閃開了。\n", ob);
        }

        return 1;
}

void lost()
{
        object me, ob;

        ob = this_object();
        me = query_competitor();
        command( "say " + RANK_D->query_respect(ob) + "果然有幾手，我還是讓你歇會兒吧，可不是我打不過你喔。");

        if( ob->name() == "桃根仙")set_temp("win/tao1", 1, me);
        if( ob->name() == "桃幹仙")set_temp("win/tao2", 1, me);
        if( ob->name() == "桃枝仙")set_temp("win/tao3", 1, me);
        if( ob->name() == "桃葉仙")set_temp("win/tao4", 1, me);
        if( ob->name() == "桃花仙")set_temp("win/tao5", 1, me);
        if( ob->name() == "桃實仙")set_temp("win/tao6", 1, me);
        delete_temp("caught", me);
        ::lost();
}

void win()
{
        object me = query_competitor();

        if (! objectp(me))
        {
                command("heihei");
                return;
        }
        delete_temp("caught", me);
        command("say 就你這點水平也想過我的關？下去練練再來吧。");
        ::win();
}
