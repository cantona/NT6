// feizei.c
//last modified by sir 4.21.2002

#include <dbase.h>
#include <login.h>
#include <ansi.h>

inherit NPC;
inherit F_CLEAN_UP;
inherit F_UNIQUE;
int set_perform();

void create()
{
        set_name("飛賊",({ "fei zei","fei","zei" }) );
        set("title",HIY"飛天遁地"NOR);
        set("age", 30+random(20));
        set("long", 
"這是無惡不做的飛賊，背上有一個小小包裹，看樣子是才偷了什麼東西在手。\n");
        set("int", 30);
        set("str", 20+random(10));
        set("con", 30);
        set("dex", 80+random(30));
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("no_get",1);
        set("max_qi", 2500+random(500));
        set("max_jing", 1200+random(300));
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 50+random(80));
        set("combat_exp", 500000);
        set("score", 15000);
        set_temp("apply/attack", 60);
        set_temp("apply/defense", 60);
        set_temp("apply/damage", 40);
        
        set("str_lvl",1);
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({
          (:call_out,"random_move",0:),
                }) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("gold",1);

}
void init()
{
        object ob, me, money;
        int i;
        object *inv;
        if (!query("inited")) {set("inited",1);set_perform();}
        ob = this_player();
        if (!interactive(ob)) return;
        if( !living(ob) || query_temp("noliving", ob))return ;
        if( query_temp("ride_horse", ob))return ;
        if(random(5)>1)
        {
                        me=this_object();         
                        command("heihei"+query("id", ob));
                        if(money = present("gold_money", ob))
                        {
                                //destruct(money);
                                tell_object(ob,HIR"你突然發現身上的"+query("name", money)+HIR+"不見了！\n"NOR);
                                if (!money->move(this_object())) destruct(money);
                        }
                        else if(money = present("silver_money", ob))
                        {
                                //destruct(money);
                                tell_object(ob,HIR"你突然發現身上的"+query("name", money)+HIR+"不見了！\n"NOR);
                                if (!money->move(this_object())) destruct(money);
                        }
//                        else if(money = present("budai",ob))
//                        {
//                                tell_object(ob, HIR "你突然發現身上的"+money->query("name")+HIR+"不見了！\n"NOR);                                
//                                if (!money->move(this_object())) destruct(money);
//                        }
                        else 
                        {
                                inv=all_inventory(ob);
                                for(i=0;i<sizeof(inv);i++)
                                {
                                        if( (inv[i]->is_container()) || (inv[i]->is_unique() && !query("equipped", inv[i])) )
                                        {
                                                tell_object(ob,HIR"你突然發現身上的"+query("name", inv[i])+HIR+"不見了！\n"NOR);
                                                if (!inv[i]->move(this_object())) destruct(inv[i]);
                                                    break;
                                          }
                                }
                                if ( i==sizeof(inv) )
                                {
                                  command("say 你這個窮光蛋，連點油水都沒有，給我滾！");
                                        if (!ob->is_busy()) ob->start_busy(1);
                                }
                        }
                        command("kick"+query("id", ob));
                }
  
//                add_action("do_hit","hit");
//                add_action("do_hit","kill");
                add_action("do_halt","halt");
                add_action("do_halt","surrender");
}
int set_perform()
{
                object ob = this_object();

                NPC_D->set_perform(ob);
                set("chat_chance_combat", 40, ob);
                return 1;
}
int accept_hit(object me)
{
                object ob = this_object();

                if( query("combat_exp", me)>query("combat_exp", ob) )
                set("combat_exp",query("combat_exp",  me), ob);
                ob->fight_ob(me); 
                if( living(ob) && !query_temp("noliving", ob )
                        && !ob->is_busy() && userp(me))
                set_temp("enemy/"+query("id", me), 1, ob);
                return 1;
}
int accept_fight(object who)        {return accept_hit(who);}
int accept_kill(object who)                {return accept_hit(who);}
int accept_ansuan(object who) {return accept_hit(who);}
int accept_touxi(object who)        {return accept_hit(who);}
void random_move()
{
        return NPC_D->random_move(this_object());
}
int do_halt()
{
        object me = this_player();
        object ob = this_object();

        if ( me->is_fighting(ob))
        {
                message_vision(HIW"$N喝道：“既然被你看出身份，就休想活着離開！”\n"NOR, ob, me);
                return 1;
        }
        return 0;
}
void die()
{
        object ob = this_object();
        object me,fme;
        int pot,exp,level,score;
        int flag,i;
        string *enemys;
        object who;
        
        me=query_temp("last_damage_from", ob);
        fme=query_temp("last_opponent", ob);
        if (!objectp(me) || !userp(me))//如果是npc打死 或者意外死亡
        {
                if( !query_temp("enemy", ob))return ::die();
                enemys=keys(query_temp("enemy", ob));
                flag=1;
                for(i=0;i<sizeof(enemys);i++)
                {
                        if(!objectp(who=present(enemys[i],environment(ob)))
                        || !userp(who)) continue;
                        if(who->is_fighting(ob) )
                        {
                                flag = 0;
                                break;
                        }
                }
                if (flag==1) return ::die();
//                else return; //如果環境中還有玩家敵人 那麼將不會被npc打死
        }
        else
        {
                if (!query_temp("enemy/"+query("id",me),ob)) return ::die();
                level=query("str_lvl", ob);
                pot = level*100;
                exp = level*350;
                score =300+random(50);
                addn("combat_exp", exp, me);
                addn("potential", pot, me);
                addn("score", score, me);
                message_vision("$N咬牙切齒地對着天空大叫：“賊老天！”\n",ob);
                tell_object(me,HIW"你殺敵有功，得到如下獎勵：\n");
                tell_object(me,chinese_number(exp) +"點實戰經驗\n" +
                chinese_number(pot) + "點潛能\n" +
                chinese_number(score)+"點江湖閲歷\n"NOR);
                return ::die(); 
        }
}
