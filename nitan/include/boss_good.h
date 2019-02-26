// boss_good.h

#define MAX_BUNCH_EXP        5000000000
void init()
{

        add_action("do_join","join");
        add_action("do_disengage","disengage");
        add_action("do_choose","choose");
        add_action("do_giveup","giveup");
}

int do_join()
{
        string msg, bname;
        object me, ob;

        me = this_player();
        ob = this_object();

        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");

        if (good_bunch(me))
        {
                bname=query("bunch/bunch_name", me);
                if (bname == bunch_good["bunch_name"])
                {
                        if( query("shen", me)<0 )
                        {
                                message_vision("$N對着$n勃然大怒：我們無極幫都是正義之士，豈能容得了你這種邪惡之徒？\n", ob, me);
                                delete("bunch", me);
                                set("last_leave_bunch", time(), me);
                                msg = "聽説" + me->name(1) + "被" + ob->name(1) + "逐出了" + bname;
                                CHANNEL_D->channel_broadcast("rumor", msg);
                                return notify_fail("你被" + ob->name() + "開除出了" + bname + "。\n");
                        }
                        return notify_fail("你已經是我" + bname + "的成員了，昏頭了？\n");
                }
                return notify_fail("你現在是" + bname + "的成員，要加入我" + bunch_good["bunch_name"] + "，得先脱離(disengage)原來的幫會。\n");
        }

        if( bad_bunch(me) || query("shen", me)<0 )
        {
                message_vision("$N上上下下的仔細打量着$n，臉色越來越難看。\n", ob, me);
                command("say " + "我們" + bunch_good["bunch_name"] + "都是正義之士，豈能容得了你這種邪惡之徒？");
                return notify_fail("看來" + ob->name() + "並不歡迎你！\n");
        }

        if( query("combat_exp", me)<100000 )
        {
                command("joke "+query("id", me));
                command("say 這位" + RANK_D->query_respect(me) + "，江湖險惡，您現在這樣的身手，還不適合闖蕩啊。");
                return notify_fail("看來" + ob->name() + "覺得你的身手太低了點。\n");
        }

        if( query("combat_exp", me) >= MAX_BUNCH_EXP )
        {
                command("joke "+query("id", me));
                command("say 這位" + RANK_D->query_respect(me) + "，您身手已經很不錯，應該把志向放的更高遠一些了。");
                return notify_fail("看來" + ob->name() + "覺得你身手太高了。\n");
        }

        if( time()-query("last_leave_bunch", me)<120 )
                return notify_fail(ob->name() + "看着你説：聽説你是剛脱離了別的幫會過來的吧？我得再觀察觀察你，過兩分鐘再來吧！\n");

        set("bunch", bunch_good, me);
        delete("last_leave_bunch", me);
        message_vision("$N單膝跪下，對着$n恭恭敬敬的喊了聲：幫主！\n", me, ob);
        message_vision("$N微微一笑，對着$n點了點頭，擺手讓$n站起身來。\n", ob, me);
        tell_object(me, "恭喜你成為" + bunch_good["bunch_name"] + "的一員！\n");
        msg = "聽説" + me->name(1) + "加入了" + bunch_good["bunch_name"]+"。";
        CHANNEL_D->channel_broadcast("rumor", msg);
        return 1;
}

int do_disengage()
{
        string msg;
        object me, ob;

        me = this_player();
        ob = this_object();

        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");

        if( !good_bunch(me) || query("bunch/bunch_name", me) != bunch_good["bunch_name"] )
        {
                command("yi "+query("id", me));
                command("say 這位" + RANK_D->query_respect(me) + "，你並非我" + bunch_good["bunch_name"] + "的成員啊！");
                return notify_fail("看來" + ob->name() + "給你搞的滿頭霧水。\n");
        }

        if( query("bunch/boss", me) != bunch_good["boss"] )
                return notify_fail("想脱離我"+bunch_good["bunch_name"]+"？找你的介紹人"+query("bunch/boss", me)+"去吧。\n");

        delete("bunch", me);
        set("last_leave_bunch", time(), me);

        if( query("shen", me)<0 )
        {
                message_vision("$N對着$n勃然大怒：你怎麼這麼不爭氣，我幫中沒有你這樣的兄弟！\n",ob,me);
                tell_object(me,"你被" + ob->name() + "開除出了" + bunch_good["bunch_name"] + "。\n");
                msg = "聽説" + me->name(1) + "被" + ob->name(1) + "逐出了" + bunch_good["bunch_name"]+"。";
                CHANNEL_D->channel_broadcast("rumor", msg);
        } else
        {
                message_vision("$N對着$n歎氣道：那好罷，你自己保重！\n",ob,me);
                tell_object(me,"你決定脱離" + bunch_good["bunch_name"] + "。\n");
        }
        return 1;
}

int do_choose(string bh)
{
        string msg;
        mapping bunch_quest;
        object me, obj, ob;

        me = this_player();
        obj = this_object();

        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");

       //如果是黑道的，就趕走
        if (bad_bunch(me))
        {
                message_vision("$N上上下下的仔細打量着$n，臉色越來越難看。\n", obj, me);
                command("say " + "我們" + bunch_good["bunch_name"] + "都是正義之士，豈能容得了你這種邪惡之徒？");
                return notify_fail("看來" + obj->name() + "並不歡迎你！\n");
        }

        //如果不是本幫會的，不給領取任務
        if( !good_bunch(me) || query("bunch/bunch_name", me) != bunch_good["bunch_name"] )
        {
                command("yi "+query("id", me));
                command("say 這位" + RANK_D->query_respect(me) + "，你並非我" + bunch_good["bunch_name"] + "的成員啊！");
                return notify_fail("看來" + obj->name() + "給你搞的滿頭霧水。\n");
        }


        //如果是本幫會，但是變成了-神，那麼如果是本人收錄的成員，將其開除；否則，將其趕走
        if( query("shen", me)<0 )
        {
                message_vision("$N對着$n勃然大怒：你怎麼這麼不爭氣，我幫中沒有你這樣的兄弟！\n",obj,me);
                if( query("bunch/boss", me) == bunch_good["boss"] )
                {
                        message_vision("$N對着$n怒喝道：留你在我" + bunch_good["bunch_name"] + "豈非叫人笑話！\n",obj,me);
                        delete("bunch_quest", me);
                        delete("bunch", me);
                        set("last_leave_bunch", time(), me);
                        msg = "聽説" + me->name(1) + "被" + obj->name(1) + "逐出了" + bunch_good["bunch_name"];
                        CHANNEL_D->do_channel(this_object(), "rumor", msg);
                        return notify_fail("你被" + obj->name() + "開除出了" + bunch_good["bunch_name"] + "。\n");
                } else
                {
                        message_vision("$N對着$n怒喝：還不給我快滾！\n",obj,me);
                        return notify_fail("你沒有從" + obj->name() + "那裏領取到任何任務，反而捱了一頓臭罵。\n");
                }
        }

        //如果已經有任務在身，就痛罵一頓
        if( query("bunch_quest", me) )
                return notify_fail(obj->name() + "生氣的看着你説：你剛才領的任務還沒有完成，急什麼？\n");

        if( query("combat_exp", me) >= MAX_BUNCH_EXP )
        {
                command("joke "+query("id", me));
                command("say 這位" + RANK_D->query_respect(me) + "，您身手這麼高了，我怎麼還好意思讓你做這種小事情。");
                return notify_fail("看來" + obj->name() + "覺得你等級太高了。\n");
        }

        //如果沒有輸入編號，則提示指令
        if (! bh)
               return notify_fail(obj->name() + "奇怪的看着你，你想領取什麼任務？指令是：choose <編號>。\n");

        //如果是追殺任務，則不需要領取任務
        if (bh[0..1] == "zs")
                return notify_fail(obj->name() + "微微一笑，既然是追殺令，還用領取任務？趕緊去完成吧！\n");

        //如果是巡城，則看玩家是否加入的本地幫會
        if( bh == "xc" && query("bunch/place", me) != bunch_good["place"] )
                return notify_fail(obj->name() + "對你擺了擺手説：巡城這種事情，我本城的兄弟就可以勝任，不勞你大駕了！\n");

        //如果這個NPC正BUSY，則不給任務
        if (obj->is_busy())
                return notify_fail(obj->name() + "正忙着呢，你稍微等一下。\n");

        //如果這個玩家剛放棄過任務，需要等待
       if( time()-query("last_bunch_quest", me)<query("need_wait_time", me) )
                return notify_fail("完成不了任務，先好好反省一下，然後再來領取任務！\n");

        me->start_busy(1);

        //檢查該編號的任務是否存在
        bunch_quest = PARTY_QUEST_D->query_city_quest(PLACE, TYPE, bh);

        if (! bunch_quest)
                return notify_fail(obj->name() + "翻開簿子看了看，對你説：目前沒有" + bh + "這個任務。\n");

        //如果是巡城任務，則檢查當天是否已經有人在巡城
        if (bunch_quest["id"] == "xc" && ! bunch_quest["enable"])
                return notify_fail(obj->name() + "微微笑着説：今天已經有兄弟去巡城了，你就等改天吧！\n");

        //給任務，並且將該任務從列表中刪除
        obj->start_busy(1);
        PARTY_QUEST_D->delete_city_quest(PLACE,TYPE,bh);
        set("bunch_quest", bunch_quest, me);
        message_vision("$N對着$n點了點頭：那麼這個任務就交給你了，好好去幹！\n",obj,me);
        if (bunch_quest["id"] == "xc")
        {
                ob = new("/d/city/npc/obj/yaopai");
                ob->move(me);
                message_vision("$N將一塊" + ob->name() + "遞給了$n。\n",obj,me);

        }
        tell_object(me,"你接的任務是：\n" + bunch_quest["msg"] + "\n");
        return 1;
}

int do_giveup()
{
        string msg;
        object me, obj;

        me = this_player();
        obj = this_object();

        if (me->is_busy())
                return notify_fail("你正忙着呢。\n");

        if (bad_bunch(me))
        {
                message_vision("$N上上下下的仔細打量着$n，臉色越來越難看。\n",obj,me);
                command("say " + "你這種邪派人士的到我這裏來幹什麼？想找茬子？");
                return notify_fail("看來" + obj->name() + "並不歡迎你！\n");
        }

       //如果不是本幫會的，不理會
       if( !good_bunch(me) || query("bunch/bunch_name", me) != bunch_good["bunch_name"] )
       {
               command("yi "+query("id", me));
               command("say 這位" + RANK_D->query_respect(me) + "，你並非我" + bunch_good["bunch_name"] + "的成員啊！");
               return notify_fail("看來" + obj->name() + "給你搞的滿頭霧水。\n");
       }

       //如果是本幫會，但是變成了-神，那麼如果是本人收錄的成員，將其開除；否則，將其趕走
       if( query("shen", me)<0 )
       {
               message_vision("$N對着$n勃然大怒：你怎麼這麼不爭氣，我幫中沒有你這樣的兄弟！\n",obj,me);
               if( query("bunch/boss", me) == bunch_good["boss"] )
               {
                       message_vision("$N對着$n怒喝道：留你在我" + bunch_good["bunch_name"] + "豈非叫人笑話！\n",obj,me);
                       delete("bunch_quest", me);
                       delete("bunch", me);
                       set("last_leave_bunch", time(), me);
                       msg = "聽説" + me->name(1) + "被" + obj->name(1) + "逐出了" + bunch_good["bunch_name"];
                       CHANNEL_D->channel_broadcast("rumor", msg);
                       return notify_fail("你被" + obj->name() + "開除出了" + bunch_good["bunch_name"] + "。\n");
               } else
               {
                       message_vision("$N對着$n怒喝：還不給我快滾！\n",obj,me);
                       return notify_fail("你被" + obj->name() + "狠狠的痛罵了一番。\n");
               }
       }

       if( !query("bunch_quest", me) )
               return notify_fail(obj->name() + "奇怪的看着你説：你現在並沒有任務在身啊，是不是閒的發慌了？\n");

       delete("bunch_quest", me);
       message_vision("$N對着$n一個勁的歎氣，似乎不明白為什麼$n為何如此的不成材。\n",obj,me);
       tell_object(me,obj->name() + "衝你瞪了一眼：這點小事情都完成不了，一邊去好好反省反省！\n");

       //記錄放棄時間
       set("last_bunch_quest", time(), me);

       //如果玩家沒有連續完成任務的次數記錄，則累加該玩家需要等待的時間，最多WAIT_TIME秒，否則，等待3秒
       if( !query_temp("finish_bang_times", me) )
              set("need_wait_time",query("need_wait_time",  me)+3, me);
       else set("need_wait_time", 3, me);

       if( query("need_wait_time", me)>WAIT_TIME)set("need_wait_time", WAIT_TIME, me);

       //清除連續完成任務的次數
       delete_temp("finish_bang_times", me);
       return 1;
}
/*
int accept_object(object me,object ob)
{
       int exp,pot,score,weiwang;
       mapping bunch_quest,bonus;
       object who,env;
       string *place;
       string the_place,msg;

       who = this_object();
       if (base_name(ob) != "/d/city/npc/obj/yaopai")
       {
               msg=who->name()+"不屑地把"+query("name", ob)+"拋還給你：什麼爛東西也給我？\n";
               tell_object(me,msg);
               return 0;
       }
       if( !query("bunch_quest", me) )
       {
               msg = who->name() + "朝你點了點頭，沒有説什麼話。\n";
               tell_object(me,msg);
               return 1;
       }

       bunch_quest=query("bunch_quest", me);

       if (bunch_quest["id"] != "xc" || bunch_quest["bunch_name"] != "巡揚州城")
       {
               msg = who->name() + "朝你點了點頭，沒有説什麼話。\n";
               tell_object(me,msg);
               return 1;
       }

       place = bunch_quest["place"];

       if (sizeof(place))
       {
               the_place = place[random(sizeof(place))];
               env = get_object(the_place);
               msg = who->name() + "生氣的對你説：";
               msg += fail_xc_msg1[random(sizeof(fail_xc_msg1))];
               msg = replace_string(msg,"place",env->short());
               msg += fail_xc_msg2[random(sizeof(fail_xc_msg2))];
               tell_object(me,msg + "\n");
               return 0;
       }

       message_vision("$N高興的拍了拍$n的肩膀：乾的好！\n",who,me);

       addn("pk_score", -2, me);
       if( query("pk_score", me)<0)set("pk_score", 0, me);

       exp = bunch_quest["bonus"];
       pot = exp/(2+random(2));
       weiwang = 5 + random(10);
       score = 5 + random(10);
       delete("bunch_quest", me);
       addn_temp("finish_bang_times", 1, me);
       bonus = ([ "exp" : exp,
                  "pot" : pot,
                  "score" : score,
                  "weiwang" : weiwang,
                  "prompt": "在巡揚州城的過程中，經過鍛鍊"
               ]);
       QUEST_D->delay_bonus(me, bonus);
       destruct(ob);
       return 1;
}
*/
