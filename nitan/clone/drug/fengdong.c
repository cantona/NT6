// Code of ShenZhou
// road: /zhongnan/fengdong.c
// by sdong 08/98

#include <ansi.h>
#include <room.h>
inherit ROOM;
private int blow_result(object victim);
int blow();
void setup_ob(object me,object victim);

void create()
{
                  set("short","風洞");

                  set("long",@LONG
這個大洞又高又寬，由兩大花崗巖夾峙而成。洞內清風習習，涼氣颼颼，
故稱風洞。聽說有時會狂風大作，看來要小心一些。
LONG);

                  set("exits",([
                                                                "out": __DIR__"shanlu18",
                                                         ])
                          );
          set("cost",1);
          setup();
}

void init()
{
        add_action("do_throw", "throw");
        remove_call_out("blow");
        call_out("blow",3 + random(3) );
}

int do_throw(string arg)
{
        object ob;
        if(!arg)return notify_fail("你想扔什麼？");
        ob = present(arg,this_player());
        if(!ob)return notify_fail("你想扔什麼？");
        message_vision( HIY"\n$N把$n往外扔去！\n"NOR, this_player(), ob);
        remove_call_out("blow");
        call_out("blow",1  );
        if(userp(ob))
        {
                ob->move("/d/zhongnan/shanlu18");
                message_vision( HIY"\n$N被扔了出來！\n"NOR, ob);
         }
        else destruct(ob);
        return 1;
}


int blow()
{
        object *inv = all_inventory(find_object("d/zhongnan/fengdong"));
        object ob, me= this_player();
        int i;

        if( !this_player() ) return 1;
        if(!environment(this_player())) return 1;
        if( base_name(environment(this_player())) != "/d/zhongnan/fengdong") return 1;

        message_vision( HIY"\n突然一陣狂風夾帶石塊向風洞襲來，聲勢驚人！\n"NOR, this_player() );

        for ( i=0 ; i < sizeof(inv); i++)
        {
                if( query("race", inv[i]) == "人類" )
                {
                        blow_result(inv[i]);
                }
        }

        remove_call_out("blow");
        call_out( "blow",3 + random(3) );
        return 1;
}

private int blow_result(object victim)
{
        object ob2,ob;
        string *limbs, str, dodge_skill, limb, result;
        int ap, dp, damage;

        if(random(100)==1)
        {
                ob2=new("/d/zhongnan/npc/bigbear");
                ob2->move(environment(victim));
                message_vision(HIR"突然從洞口中走進一只$N，它看到有人，大概受了驚嚇，發瘋似地向$n發起進攻！\n"NOR, ob2,victim);
                setup_ob(ob2,victim);
                ob2->kill_ob(victim);
                addn_temp("offenders/"+query("id", victim), 1, ob2);
                ob2->start_busy(1+random(3));
      victim->kill_ob(ob2);
        }

        ap = victim->query_dex()+victim->query_str();
        dp = victim->query_dex();
        ap*=query("combat_exp", victim)/1000;
        dp*=query("combat_exp", victim)/1000;
        ap = random(ap);

        ob = new ("/d/city/obj/stone");

        if ( ap > dp){
        limbs=query("limbs", victim);
                victim->receive_wound("qi", random(20), "被石塊砸死了！");
                victim->receive_damage("qi", random(ob->query_weight()/100), "被石塊砸死了！");

                message_vision(CYN"$N猝不及防，$n"+CYN+"砸在了$N的"+limbs[random(sizeof(limbs))]
                          +"上。\n"NOR, victim, ob);
                destruct(ob);
                //ob->move(environment(victim));
        }
        else if ( ap < dp/7 && ob->query_weight() < 7000
                 && query("race", victim) == "人類"){
                message_vision(CYN"不料$N眼明手快，身子一側，把$n"+CYN+"輕輕地接在手裡。\n\n"NOR, victim, ob);

                ob->move(victim);

         }
        else {

                dodge_skill = victim->query_skill_mapped("dodge");
                if( !dodge_skill ) dodge_skill = "dodge";
                message_vision("$N一閃，正好躲過"+query("name", ob)+".\n",victim);

                destruct(ob);
        }

        if( victim->query_skill("parry",1)<300)victim->improve_skill("parry",query("con", victim));

        return 1;
}

void setup_ob(object me,object victim)
{
        object *inv;
        mapping skill_status;
        string *sname;
        int i, max = 0, max1, j;


        if( !query_temp("copied", me)){
                if ( mapp(skill_status = victim->query_skills()) ) {
                skill_status = victim->query_skills();
                sname = keys(skill_status);

                for(i=0; i<sizeof(skill_status); i++) {
                        if ( skill_status[sname[i]] > max ) max = skill_status[sname[i]];
                }


                max1 = (int)max + random(max);

                if( query("combat_exp",1, victim)<10000)max1/2;
                me->set_skill("dodge", max1);
                me->set_skill("parry", max1 );
                me->set_skill("force", max1);

                set("combat_exp", query("combat_exp",victim)+random(query("combat_exp",victim)/10), me);

                set("max_qi",query("max_qi",  victim), me);
                set("eff_qi",query("max_qi",  victim), me);
                set("max_jing",query("max_jing",  victim), me);
                set("eff_jing",query("max_jing",  victim), me);
                set("qi",query("max_qi",  me), me);
                set("jing",query("max_jing",  me), me);
                set("jiali",query("jiali",  victim)*3/4, me);
                if( query("max_jingli", victim)>0){
                        set("max_jingli",query("max_jingli",  victim), me);
                }
                else set("max_jingli", 500, me);
                set("jingli",query("max_jingli",  me), me);

                set("no_sing", 1, me);
                set_temp("copied", 1, me);
                }
        }
}
