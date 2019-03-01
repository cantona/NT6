#include <ansi.h>

inherit "/maze/necropolis/necropolis_npc";
void do_fire();
void create()
{
        string *names = ({"幽冥之火"}); 
        // set_name( names[random(sizeof(names))], ({ "ghost fire","ghost"}));
        set_name( names[random(sizeof(names))], ({ "ghost fire" }));
        set("vendetta_mark","ghost");
        set("long", "這是個若隱若現的幽靈。\n");
        set("title", HIB "(鬼氣)" NOR); 

        set("str", 50);
        set("con", 120);
        set("dex", 22); 
        set("int", 50);
        set("max_qi", 80000);
        set("max_jing", 85000);
        set("neili", 450000);
        set("max_neili", 450000);
        set("max_jingli", 50000);
        set("attitude", "peaceful");
        //set("shen_type", -1);        
        //set("chat_chance", 2);
        //set("chat_msg", ({
        //               "骷髏空洞的眼眶裡閃爍著可怕的熒光。\n"
        //}) ); 
        set("death_msg",BLU"\n$N消失不見了。\n\n"NOR);
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: do_fire() :),
        }) ); 
        set("self_go_msg",1);
        set("arrive_msg","幽冥之火飄了過來。");
        set("leave_msg","幽冥之火飄走了。");
        set("chat_chance", 1);
        set("chat_msg", ({
                (: random_move :)
        }) );  
        set("combat_exp", 150000000);
        set("bellicosity", 5 );

        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("unarmed", 120);
        set_skill("parry", 120);              
        set_temp("apply/attack", 1000);
        set_temp("apply/parry", 500);
        set_temp("apply/unarmed_damage", 500);
/*
        set("drops", ([
                 "RA&RARE40" : 70, 
                 "RA&RARE50" : 30, 
        ]));
*/

        setup();
        //carry_object(__DIR__"obj/bone_finger");
} 

int is_undead() {
        return 1;
}

//int is_ghost() {
//        return 1;
//}


void do_fire() {
        object *enemies,enemy;
        enemies = query_enemy();
        if(!enemies || sizeof(enemies)==0)
                return;
        message_vision(HIB"$N突然消失，同時無數幽幽的藍火仿佛受到召喚從地下升騰而起， \n$N周圍頓時變成了恐怖的人間煉獄。 \n"NOR, this_object()); 
        foreach(enemy in enemies) {
                if(enemy) {
                        message_vision(HIC "\n一條條蠕動的藍火如蟒蛇般纏上了$N。\n"NOR, enemy, this_object()); 
                        enemy->receive_damage("jing",2000+random(1000),this_object());
                        COMBAT_D->report_status(enemy);
                }
        }
        if (!this_object()->is_busy())
                this_object()->start_busy(2);
}
