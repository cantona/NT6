// Last Modified by sir 2003.11.14
#include <ansi.h>
inherit NPC;

int do_back(object me);

void create()
{
        set_name("黑衣人", ({ "heiyi ren","ren"}));
        set("gender", "男性");
        set("quest_no_guard",1);
        set("no_steal",1);
        set("no_ansuan",1);
        set("long", "一個穿著黑色夜行衣的人。\n");
        set( "chat_chance_combat", 80);         
  set( "chat_msg_combat",({
                        (: exert_function, "recover" :),
                        (: exert_function, "powerup" :),
           }) );
        setup();
        NAME_D->generate_cn_name(this_object());
        carry_object("/d/city/obj/tiejia")->wear();
        call_out("do_back", 360,  this_object());
}

int do_back(object me)
{                        
        if (objectp(environment(me)))
        {
                tell_room(environment(me),query("name", me)+"匆匆忙忙的離開了。\n",({me}));
                destruct(me); 
        }
  return 1;
}

void die()
{
        object ob = this_object();
        object me,fme;
        object *obs;
        int pot,exp,level,score;
        int all_exp,all_pot;
        int per_exp,per_pot;
        int i;

        all_exp=200+random(200);
        all_pot=all_exp*3/10+random(60)-30;
        
        obs=query_temp("killer", ob);
        if (!sizeof(obs)) return ::die();

        fme=query_temp("faint_by", ob);
        
        per_exp = all_exp / (sizeof(obs)+2);
        per_pot = all_exp / (sizeof(obs)+2);

        for (i=0;i<sizeof(obs);i++)
        {
                if( objectp(obs[i]) && environment(obs[i])==environment(ob) )
                {
                        exp = per_exp;
                        pot = per_pot;
                        if (obs[i]==fme)
                        {
                                        exp += per_exp;
                                        pot += per_pot;
                        }
                        if( query("id", obs[i]) == query("owner", ob) )
                        {
                                        exp += per_exp;
                                        pot += per_pot;
                        }
                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        set_temp("prize_reason", "追殺", me);
                        set_temp("can_give_prize", 1, me);
                        set_temp("prize_exp", exp, me);
                        set_temp("prize_pot", pot, me);

                        tell_object(me,HIW"經過這番歷練，\n你被獎勵了：\n");
                        tell_object(me,chinese_number(exp) +"點實戰經驗\n" +
                        chinese_number(pot) + "點潛能\n"NOR);
                }
        }
        me=find_player(query("owner", ob));
        if (objectp(me))
        set("quest/kill/finished", 1, me);
  ::die();    
}

int accept_fight(object ob)
{
        set_temp("killer",ob);
        command("say 好！咱們就比劃比劃！");
        kill_ob(ob);
        return 1;
}

int accept_hit(object ob)
{
        set_temp("killer",ob);
        command("say 你死去吧！");
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        set_temp("killer",ob);
        command("say 哼！找死！");
        return 1;
}
int accept_ansuan(object who) {return notify_fail("此人警惕性太高，沒法暗算。\n");}
int accept_touxi(object who)        {return accept_kill(who);}
