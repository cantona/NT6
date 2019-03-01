// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

int in_ask, answer;
int bCheckingRobot;


void say_question(object me, object ob)
{
        // object ob = this_player();
        int a, b, c;
        string oper;

        // if( in_ask || random(20) > 10 ) return;
        if( !ob || !userp(ob) || !me || !userp(me) )
        {
                bCheckingRobot = 0;
                return;
        }

        delete_temp("wrong");
        a = random(19) + 2;
        b = random(19) + 2;
        switch(random(5)) {
                case 0:
                        answer = a + b;
                        oper = chinese_number(a) + "加" + chinese_number(b)+ "等于多少？";
                        break;
                case 1:
                        if (a < b) { c = b; b = a; a = c;}
                        answer = a - b;
                        oper = chinese_number(a) + "減去" + chinese_number(b)+ "等于多少？";
                        break;
                case 2:
                        if( a * b < 200 ) {
                                answer = a * b;
                                oper = chinese_number(a) + "乘" + chinese_number(b)+ "等于多少？";
                        } else {
                                answer = (a * b) % 10;
                                oper = chinese_number(a) + "乘" + chinese_number(b)+ "，個位數等於多少？";
                        }
                        break;
                case 3:
                        answer = a % b;
                        oper = chinese_number(a) + "除以" + chinese_number(b)+ "的余數是多少？";
                        break;
                case 4:
                        oper = chinese_number(a) + "和" + chinese_number(b)+ "的最大公因數是多少？";
                        if( b < a ) { c = b; b = a; a = c; }
                        while( a > 1 && b%a > 1 ) {
                                c = a;
                                a = b%a;
                                b = c;
                        }
                        answer = b%a == 1 ? 1 : a;
                        break;
        }
        message_vision("$N對$n提問道："+oper + "，請在三十秒內作答(da <number>))。\n",me,ob);
        in_ask = 1;
        remove_call_out("say_answer");
        call_out("say_answer", 30, me,ob);
}

void say_answer(object me, object ob)
{
        object env, *inv;
        int i;

        if( !ob || !userp(ob) || !me || !userp(me) )
        {
                bCheckingRobot = 0;
                return;
        }

        addn("robot_check_wrong", 1, ob);
        call_out("ans_wrong", 1, me, ob);

        message_vision("$N說道：這麼簡單都不會？答案等于" + chinese_number(answer) + "。\n",me);
        in_ask = 0;
        remove_call_out("say_question");
        call_out("say_question", 1, me, ob);
}


int do_answer(string arg)
{
        object ob = this_player();
        object partner;
        string s;
        int ans;

        if( !query_temp("partner", ob) || !query_temp("partner_id", ob) || !(partner=present(query_temp("partner_id", ob),environment(ob))) )
                return notify_fail("這裡沒有你想要與之討論的人。\n");


        if( !in_ask ) return notify_fail("你必須等下一題。\n");
        if( !arg ) return notify_fail("請你回答一個數字。\n");

        message_vision( CYN "$N答道：" + arg + "\n" NOR, ob);

        if( sscanf(arg, "%d", ans)==1 ) {
                if( ans==answer ) {
                        addn("robot_check", 1, ob);
                        message_vision("$N說道：答對了！\n",partner);
                        partner->command("pat"+query("id", this_player()));

                        remove_call_out("say_answer");
                        in_ask = 0;
                        if( query("robot_check", this_player()) >= 3){
                                message_vision(HIG"$N說道：很好，你果然對算法頗有研究，佩服！佩服！我們繼續討論武功吧。\n\n"NOR,partner);
                                delete("robot_check", ob);
                                delete("robot_check_wrong", ob);
                                delete("robot_checking", ob);
                                delete("robot_check", partner);
                                delete("robot_check_wrong", partner);
                                delete("robot_checking", partner);
                                bCheckingRobot = 0;
                                return 1;
                        }
                        else
                        {
                                remove_call_out("say_question");
                                call_out("say_question", 1, partner,ob);
                        }

                } else {
                        message_vision("$N說道：錯！\n",partner);
                        addn("robot_check_wrong", 1, this_player());
                        addn_temp("wrong/"+query("id", this_player()),1);
                        call_out("ans_wrong", 0, partner,ob);
                        if( query_temp("wrong/"+query("id", this_player()))>3){
                                message_vision(HIG"只見青光一閃，黃藥師突然出現在$N的眼前。\n"NOR,ob);
                                message_vision(HIY"黃藥師很生氣地對$N喝道：你這不肖之徒，連這麼簡單問題都答不出，去死吧。\n"NOR,ob);
                                message_vision(HIR"黃藥師彈指一彈，一股內勁破空而出，向$n襲來，$N只覺得透不過氣來，撲的一聲倒在地上。\n"NOR,ob,ob);
                                message_vision(HIC"黃藥師袖袍一揮，把$N凌空卷起，走到屋外，對啞僕喊道：“你們把這不肖之徒扔到外島去，越遠越好！”\n\n黃藥師氣哼哼的走了。\n\n"NOR,ob);

                                this_player()->receive_wound("qi", 100, this_object());
                                set("jingli", -1, this_player());
                                set("qi", -1, this_player());
                                this_player()->move("/d/island/icefire_land");
                                delete("robot_checking", ob);
                                delete("robot_check", ob);
                                delete("robot_check_wrong", ob);
                                bCheckingRobot = 0;
                                in_ask = 0;
                                remove_call_out("say_question");
                                remove_call_out("say_answer");
                        }

                        //remove_call_out("say_question");
                        //call_out("say_question", 1, ob);
                }
        }
        return 1;
}

int ans_wrong(object partner,object ob)
{
        if( query("robot_check_wrong", ob)>5){
                message_vision(HIG"只見青光一閃，黃藥師突然出現在$N的眼前。\n"NOR,ob);
                message_vision(HIY"黃藥師很生氣地對$N喝道：你這不肖之徒，連這麼簡單問題都答不出，去死吧。\n"NOR,ob);
                message_vision(HIR"黃藥師彈指一彈，一股內勁破空而出，向$n襲來，$N只覺得透不過氣來，撲的一聲倒在地上。\n"NOR,ob,ob);
                message_vision(HIC"黃藥師袖袍一揮，把$N凌空卷起，走到屋外，對啞僕喊道：“你們把這不肖之徒扔到外島去，越遠越好！”\n\n黃藥師氣哼哼的走了。\n\n"NOR,ob);

                ob->move("/d/island/icefire_land");
                delete("robot_check_wrong", ob);
                delete("robot_check", ob);
                delete("robot_checking", ob);
                delete("robot_check_wrong", partner);
                delete("robot_check", partner);
                delete("robot_checking", partner);
                bCheckingRobot = 0;
                in_ask = 0;
                remove_call_out("say_question");
                remove_call_out("say_answer");
        }
        return 1;
}


int do_discuss(string arg)
{
        object me,partner;
        int exp1, exp2, pot1, pot2, times, i;
        string name1, name2, name3, name4, target;

        me = this_player();
                  if (me->is_busy()
                   || query_temp("pending/exercising", me )
                   || query_temp("exit_blocked", me) )
                                         return notify_fail("你現在正忙著呢。\n");

        if( !arg || arg == getuid(me))
                return notify_fail("沒有你想要與之討論的人。\n");

/*
        if (sscanf(arg, "%s %d", target ,times)!=2 ) {
                times = 1;
        if( !arg || arg == getuid(me))
                return notify_fail("沒有你想要與之討論的人。\n");
        }
*/
        if (sscanf(arg, "%s %d", target ,times)!=2 ) {
                times = 1;
            if (sscanf(arg, "%s", target )!=1 )
                return notify_fail("這裡沒有你想要與之討論的人。\n");
        }
        
        if (times < 1) 
                return notify_fail("你要討論多少次？\n");
        if( !(partner = present(target, environment(me))) || !partner->is_character() || me == partner)
                return notify_fail("這裡沒有你想要與之討論的人。\n");


        exp1=query_temp("exp_gain", me);
        pot1=query_temp("pot_gain", me);
        name1 = me->name();
        name3=query_temp("partner", me);
        exp2=query_temp("exp_gain", partner);
        pot2=query_temp("pot_gain", partner);
        name2 = partner->name();
        name4=query_temp("partner", partner);

        set_temp("partner_id",query("id",  me), partner);
        set_temp("partner_id",query("id",  partner), me);
        if( query("th_discuss", me)>2000 )
                return notify_fail("你討論了這麼多，應該實踐一下本門武功的技巧了。\n");
        if( query("th_discuss", partner)>2000 )
                return notify_fail(name2+"已經討論過很多本門武學，應該實踐一下了。\n");

/*
        if( query("huang_called", me) )
                return notify_fail("黃藥師要你去見他，身為弟子，該當先遵行師命才是，可不是切磋功夫的時候。\n");
        if( query("huang_called", partner) )
                return notify_fail("黃藥師要"+name2+"去見他，身為弟子，該當先遵行師命才是，可不是切磋功夫的時候。\n");

        if( query("th_ask", me) )
                return notify_fail("你還沒去找"+query("th_ask", me)+"呢。\n");
        if( query("th_ask", partner) )
                return notify_fail("對方還沒處理完師父交代的事。\n");
        if( query("th_teach", me) )
                return notify_fail("你幫"+query("th_teach", me)+"練功夫，才幫到一半哪。\n");
        if( query("th_teach", partner) )
                return notify_fail("對方還沒處理完師父交代的事。\n");
*/
        if( (exp1 < times || exp2 < times ) && times > 1)
                return notify_fail("□怕你們討論不了這麼大范圍。\n");

        if( query("jing", me)<20 || query("jingli", me)<20 )
                return notify_fail("你太累了，無法繼續討論下去。\n");
                  if( query("jing", partner)<20 || query("jingli", partner)<20 )
                                         return notify_fail("你的同伴一副昏昏欲睡的樣子，看來無法繼續討論下去。\n");

        if( query("jing", me)<10+10*times || query("jingli", me)<10+10*times )
                return notify_fail("以你目前的精神狀況，□怕一次討論不了這麼多東西。\n");
                  if( query("jing", partner)<10+10*times || query("jingli", partner)<10+10*times )
                                         return notify_fail("以對方目前的精神狀況，□怕一次討論不了這麼多東西。\n");

        addn("jing", -10*times, me);
        addn("jing", -10*times, partner);
        addn("jingli", -10*times, me);
        addn("jingli", -10*times, partner);

        if( exp1 < 1 && exp2 < 1) {
                tell_object(me,CYN"你和"+name2+"窮聊了一陣，感覺腦袋空盪盪的，一無所得。\n"NOR);
                tell_object(partner,CYN"你和"+name1+"窮聊了一陣，感覺腦袋空盪盪的，一無所得。\n"NOR);
                message_vision(CYN"$N和$n正有一搭，沒一搭的擺空龍門陣。\n"NOR,me,partner);
                delete_temp("exp_gain", me);
                delete_temp("exp_gain", partner);
                me->start_busy(random(3));
                partner->start_busy(random(3));
                return 1;
        }

        if( exp1 < 1 ) {
                tell_object(me,CYN"你想要和"+name2+"探討一下武功心得，但卻覺得沒啥好說的...\n"NOR);
                tell_object(partner,CYN""+name1+"似乎想和你討論點什麼的樣子...\n"NOR);
                message_vision(CYN"$N對$n一副欲言又止的尷尬模樣。\n"NOR,me,partner);
                delete_temp("exp_gain", me);
                return 1;
        }

                  if( exp2 < 1 ) {
                                         tell_object(me,CYN"你想要和"+name2+"探討一下武功心得，但"+name2+"卻一副心不在焉的樣子...\n"NOR);
                                         tell_object(partner,CYN""+name1+"似乎想和你討論點什麼的樣子，但你卻覺得沒啥好說的...\n"NOR);
                                         message_vision(CYN"$n對$N一副欲言又止的尷尬模樣。\n"NOR,me,partner);
                                         delete_temp("exp_gain", me);
                                         return 1;
                  }

  if( query("robot_checking", me) )
  {
        if(bCheckingRobot == 0)
        {
                bCheckingRobot = 1;
                call_out("say_question",1,partner,me);
        }
        return notify_fail("你還是先把問題答完再想別的吧! \n");
  }

  if( query("robot_checking", partner) )
  {
        if(bCheckingRobot == 0)
        {
                bCheckingRobot = 1;
                call_out("say_question",1,me,partner);
        }
        return notify_fail("還是等人家先把問題答完再說吧! \n");
  }

//discuss變成discuss xxx <次數>後，下指令機會減少，check robot機會減低太多，暫時取消

/*
  if( random( 150 ) == 1 && bCheckingRobot == 0)
  {
        message_vision(HIG"$N說道：本桃花島派不但以武功稱譽天下，而且師父對奇門八卦、諸子百家無所不精、無所不通。\n",me);
        message_vision("$N說道：我等弟子若能學到師父一成兩成學問，就此生無憾了。\n",me);
        message_vision("$N說道：今天練功這麼久，不如休息休息，讓我們來探討探討一些算法問題。\n"NOR,me);
        set("robot_checking", 1, partner);
        bCheckingRobot = 1;
        call_out("say_question",1,me,partner);
        return 1;
  }

        if( query("th_discuss", me)>2000){
        message_vision("$N正欲討論武學精要，一個啞僕走了過來，對$N咿咿呀呀地做了個手勢，是黃藥師有事要找$N，不知有何吩咐。\n",me,partner);
        message_vision("$N和$n對望一眼，停了下來。$N向啞僕揮揮手，示意知道，啞僕便即離去。\n",me,partner);
        set("huang_called", 1, me);
        delete("th_discuss", me);
        return 1;
        }
*/

        message_vision(CYN"$N和$n熱烈的探討著各自武功的得失，及其對武學的理解。\n"NOR,me,partner);
        tell_object(me,HIY"你一邊和"+name2+"印証武學，一邊回想著與"+name3+"的比武經過，對武學的認識又深了一層！\n"NOR);
                  tell_object(partner,HIY"你一邊和"+name1+"印証武學，一邊回想著與"+name4+"的比武經過，對武學的認識又深了一層！\n"NOR);
        //me->start_busy(1+random(2));
        //partner->start_busy(1+random(2));

        exp1 = exp1-times; pot1 = pot1-times;
        exp2 = exp2-times; pot2 = pot2-times;

        set_temp("exp_gain", exp1, me);
        set_temp("exp_gain", exp2, partner);

                    for (i=0; i<times; i++) {
        addn("combat_exp", (me->query_int()/30+1), me);
        addn("th_discuss", 1, me);
        addn("combat_exp", (partner->query_int()/30+1), partner);
        addn("th_discuss", 1, partner);
        }

        if (pot1>0) {
                set_temp("pot_gain", pot1, me);
                for (i=0; i<times; i++) {
                if( query("potential", me)<query("max_potential", me )
                && random(3) == 1) {
                addn("potential", (me->query_int()/20+1), me);
                }
                }
        }else delete_temp("pot_gain", me);

        if (pot2>0) {
                set_temp("pot_gain", pot2, partner);
                for (i=0; i<times; i++) {
                if( query("potential", partner)<query("max_potential", partner )
                && random(3) == 1) {
                addn("potential", (partner->query_int()/20+1), partner);
                }
                }
        }else delete_temp("pot_gain", partner);
                if( wizardp(me) )
        message_vision("exp1:"+exp1+" exp2:"+exp2+" pot1:"+pot1+" pot2:"+pot2+"\n",me,partner);

        return 1;
}