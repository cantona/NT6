// letter.c
// Last Modified by sir
// 做成3萬exp經驗以下的新手入門任務,增加exp ,pot獎勵,恢復silver獎勵

#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(RED"信件"NOR, ({ "letter","xin","secret letter" }));
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else
        {
                set("unit", "封");
                set("long",
                        "這是一封信件，信封的很嚴實，封口蓋著紅漆印戳。\n");
                set("value", 0);
                set("material", "paper");
                set("no_drop",1);
                set("no_give",1);
                set("no_put",1);
        }
}
void init()
{        
        call_out("dest",random(200)+1200);
        add_action("do_send", "songxin");
        add_action("do_look", "kan");
        add_action("do_look", "chakan");
//        add_action("do_getxin", "get");
}
/*
int do_getxin(string arg)
{
        object me;
        me = this_player();
        
        if( (arg == "letter" || arg == "xin" || arg == "all") && !query_temp("gb_songxin", me) )
                return notify_fail("你不能拿別人的東西。\n");
}
*/
int do_look(string arg)
{
        int now_time, time;
        object me;

        me = this_player();
        now_time = me->query_condition("gb_songxin"); 
        time=query_temp("songxin_time", me);

        if(!arg) return 0;
        if( (arg == "letter" || arg == "xin") && query_temp("gb_songxin", me) )
        {
                write("\n這是一封由丐幫九袋長老魯有腳發出的信件，上面寫著"
                        HIR"「"+query_temp("songxin_target_name", me)+"」親啟。\n"NOR);
                if(now_time > time*3/4) write("你現在有充足的時間去送信。\n");
                if(now_time > time/2 && now_time <= time*3/4)
                        write("已經過去一小半時間了。\n");
                if(now_time > time/4 && now_time <= time/2)
                        write("你還有一半的時間去送信。\n");
                if(now_time > time/8 && now_time <= time/4)
                        write("你的時間已經不多了。\n");
                if(now_time > 0 && now_time <= time/8)
                        write("時間將至，任務即將失敗。\n");
        }
        else
        {
                if( (arg == "letter" || arg == "xin") && !query_temp("gb_songxin", me) )
                        write("這是一封密函，信封的很嚴實，封口蓋著紅漆印戳。\n");
        }
        return 1;
}

int do_send(string arg)
{
        int i,exp,pot,score,num,s_bonus,times,job_time,paytimes;
        object ob;
        object me,target,payment;
        string t_name;
        mapping fam;

        paytimes = 0;
        me=this_player();
        if(!arg) return notify_fail("你要送給誰？\n");
        if(!objectp(target = present(arg, environment(me))))
                return notify_fail("看清楚點，你要送信的人不在這裡！\n");
        t_name=query("name", target);
        job_time=query_temp("songxin_time", me);
        i = random((int)(target->query_skill("force",1)/5));

               if(!target) return notify_fail("看清楚點，你要送信的人不在這裡！\n");
        if(userp(target)) return notify_fail("嘿嘿，想作弊？！\n");
        if( query_temp("gb_songxin_late", me) )
                return notify_fail("你任務已經失敗了，重新再領一個吧。\n");
        if (!present("secret letter", this_player()) )
                return notify_fail("你身上沒有攜帶信件。\n"); 
/*
        if( !(fam=query("family", me)) || fam["family_name"] != "丐幫" )
                return notify_fail(RANK_D->query_respect(me) + "與丐幫素無來往，怎麼會送信給我？");
*/
        if( !query_temp("gb_songxin", me) )
                return notify_fail(t_name+"道：這是丐幫親自交給你，要你送的？你是不是從別人那裡搶來的？");
        if( query_temp("songxin_target_name", me) != t_name )
                return notify_fail(t_name+"道：這封信不是給我的，你是不是送錯了？");

        message_vision(HIY"$N擦了一把額頭的汗，從懷中掏出信交給$n說道，這是丐幫魯長老讓在下送給您的信，請您收好。\n"NOR, me, target);
        message_vision("$N交給了$n一封信。\n",me, target);
        message_vision(t_name+"點了點頭說道：辛苦你了,這辛苦費你就收下吧! \n",me);
        target->add_money("silver",(int)(target->query_skill("force",1)/5)+1);
        command("give"+query("id", me)+""+((target->query_skill("force",1)/5)+1)+"silver");

        message_vision(HIY "$N接過信看了看，點了點頭說道：這位"+RANK_D->query_respect(me)+"辛苦你了。\n"NOR, target, me);
 

        if( query("combat_exp", me) <= 5000 )
        {
                if( !query_temp("zuji", me) )
                {
                        exp=((1+random(3))*50+(int)(job_time/5));
                        pot=30+random(20);
                }
                else
                {
                        exp=((1+random(3))*90+(int)(job_time/5));
                        pot=50+random(20);
                }
        }
        if( query("combat_exp", me) <= 20000
                 && query("combat_exp", me)>5000 )
        {
                if( !query_temp("zuji", me) )
                {
                        exp=(1+random(2))*70+(int)(job_time/6);
                        pot=40+random(15);
                }
                else
                {
                        exp=(1+random(2))*100+(int)(job_time/6);
                        pot=60+random(30);
//                        if (pot >150) pot=150;
                }
        }
        if( query("combat_exp", me)>20000 )
        {
                if( !query_temp("zuji", me) )
                {
                        exp=(1+random(2))*60+(int)(job_time/8);
                        pot=30+random(30);
                }
                else
                 {
                        exp=(1+random(2))*80+(int)(job_time/16);
                        pot=40+random(40);
//                        if (pot >180) pot=180;
                }
        }

        
        num=query("perform/number", me)+1;
        if (num<4) times=num;
         else times=4;
        
        if( !(fam=query("family", me)) || fam["family_name"] != "丐幫")score=0;
         else score=random(10)+ 10 * times;
        
        s_bonus=50+random(50);
        
        addn("potential", pot, me);
        addn("combat_exp", exp, me);
        addn("score", s_bonus, me);
        addn("family/fealty", score, me);
        addn("gb_job", 1, me);
/*
        if (paytimes<i)       
        {
            payment=new("/clone/money/silver");
            payment->move(me);
            addn("paytimes", 1, me);
        }
*/
//      silver獎勵

        tell_object(me,HIW"好！任務完成,你被獎勵了：\n" + 
                chinese_number(exp) + "點實戰經驗\n" +
                chinese_number(pot) + "點潛能\n"+
                chinese_number(score) + "點忠誠度\n"+
                chinese_number(s_bonus) + "點江湖閱歷\n" +
                chinese_number(i)+"兩白銀\n"+
                "你為丐幫做了"+query("gb_job", me)+"次工作。\n"NOR);
                me->apply_condition("gb_songxin", me->query_condition("gb_songxin")/2);
                delete_temp("gb_songxin", me);
                delete_temp("songxin_time", me);
                delete_temp("songxin_target_name", me);
                delete_temp("songxin_where", me);
                delete_temp("letter_steal", me);
                delete_temp("zuji", me);
                set_temp("songxin_ok", 1, me);
                delete_temp("songxin_zuji", me);
              //me->clear_condition("gb_songxin");
                destruct(this_object());
                return 1;
}

void dest()
{
                destruct(this_object());
}