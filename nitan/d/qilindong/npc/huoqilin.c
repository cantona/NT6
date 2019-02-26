// Updated by yuchang
inherit NPC;
#include <ansi.h>
void big_blowing();

void create()
{
        set_name(HIR"火麒麟"NOR, ({ "huo qilin", "qilin" }) );
        set("race", "野獸");
        set("gender", "雄性");
        set("age", 200);
        set("long", 
"這是一條全身赤紅，吸天地之間的火氣而長大的火麒麟！
它全身散發着赤紅色的火焰。\n");
        
        set("str", 100);
        set("con", 100);
        set("dex", 100);

        set("dodge", 999);
        set("force", 999);
        set("unarmed", 999);
        set("parry", 999);
        set("max_qi", 50000);
        set("max_jing", 50000);
        set("max_neili", 50000);
        set("attitude", "aggressive");
        set("limbs", ({ "頭部", "身體", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );

        set("chat_chance_combat", 80); 
        set("chat_msg_combat",({(: big_blowing :)}));      
        set("combat_exp", 51100000);
        set("bellicosity", 30000 );
        
        set_temp("apply/attack", 1560+random(400));
        set_temp("apply/damage",1500+random(400));
        set_temp("apply/armor", 1500+random(400));

        setup();
} 

void big_blowing()
{
     int i, dam;
     object *inv, me, ob;

     ob = this_object();        
     me = this_player();

     tell_room(environment(ob),HIR "\n\n火麒麟突然吐出一股熾可焚金的火焰，"
                  "整個天地似乎都被燒着了！！！\n\n"NOR);


     inv = all_inventory(environment(ob));
     for(i = 0; i < sizeof(inv); i++)
     if( living(inv[i]) && inv[i] != ob )
     {
                dam = random(500) + 100;               
                inv[i]->receive_wound("qi",dam);
                tell_object(inv[i], HBRED"你被火焰燒着，頓覺氣血大受損傷！\n\n"NOR);
     } 
}



void init() 
{ 
        object me, ob; 

        ::init(); 
        if (! interactive(me = this_player())) 
               return; 

       // 自動攻擊玩家                
       kill_ob(me); 
} 
void die()
{
        object ob, obj;
        object killer;
        int exp, userexp;

        ob = this_object();
        message_vision(HIR"\n$N" HIG"掙扎了幾下，發出一聲慘叫，便不再動彈了。\n"NOR, ob);

        if(objectp(killer = ob->query_last_damage_from()) &&
           ! killer->query("reborn_start/qilindong/qilin") )
        {
                userexp = killer->query("combat_exp");
                exp=((int)killer->query("literate")*2)+random(1000)+10000+(userexp);
                obj = new(__DIR__"obj/qilin");
                obj ->move(killer, 1);
               
                message_vision(HIC "\n\n一團火焰猛地升騰，一個聲音對$N説道："
                               "謝謝你殺死火麒麟，你將得到麒麟臂作為獎勵！\n\n" NOR, killer); 
                message_vision(HIY"只見$N" HIY"慢慢消失，只剩下了一隻麒麟的前臂。\n"
                               "\n$n隨即將麒麟臂撿了起來。\n\n"NOR, ob, killer);            
                killer->set("reborn_start/qilindong/qilin",1);
                killer->add("combat_exp",exp);
                killer->add("potential",20000);                       
                message("vison", HBMAG"【轉世傳聞】：據説" + killer->query("name") +
                                "成功地殺死了火麒麟，得到寶物麒麟臂!\n"NOR, users());
        }              
        destruct(ob);
} 
