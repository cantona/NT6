#include <ansi.h>

inherit "/maze/necropolis/necropolis_npc";
void do_summon();
void create()
{
        string *names = ({"僵屍王"}); 
        // set_name( names[random(sizeof(names))], ({ "lord zombie","zombie"}));
        set_name( names[random(sizeof(names))], ({ "lord zombie" }));
        set("vendetta_mark","zombie");
        set("long", "這是一個腐爛的僵屍。\n");
        set("title", HIB "(鬼氣)" NOR); 

        set("str", 50);
        set("con", 120);
        set("dex", 50); 
        set("int", 50);
        set("max_qi", 250000);
        set("max_jing", 260000);
        set("neili", 550000);
        set("max_neili", 550000);
        set("max_jingli", 80000);
        set("attitude", "peaceful");
        //set("shen_type", -1);       
        //set("chat_chance", 2);
        //set("chat_msg", ({
        //                "骷髏空洞的眼眶裡閃爍著可怕的熒光。\n"
        //}) ); 

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: do_summon() :),
        }) ); 

        set("combat_exp", 200000000);
        set("bellicosity", 5 );
        set("death_msg",RED"\n$N化作了一灘血水。\n\n"NOR);

        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("unarmed", 120);
        set_skill("parry", 120);      
        set_temp("apply/attack", 1500);
        set_temp("apply/parry", 1500);
        set_temp("apply/unarmed_damage", 1800);
        set("drops", ([
                 "RA&RARE40" : 70, 
                 "RA&RARE50" : 30, 
        ]));

        setup();
        carry_object(__DIR__"obj/zombie_blood");
} 

int is_undead() {
        return 1;
}

/*
int is_zombie() {
        return 1;
}
*/



void do_summon() {
   object zombie,me,enemy,*enemies;
        me = this_object();
        
        message_vision(HIM "\n$N□□幹嚎，周圍的僵屍應聲而來。\n" NOR, me); 
        seteuid(getuid());   
        if(random(2))
                zombie = new(__DIR__"zombie_blood");
        else
                zombie = new(__DIR__"zombie_power");
        zombie->move(environment(me));
        enemies = me->query_enemy();
        foreach(enemy in enemies) {
                        zombie->kill_ob(enemy);
                        enemy->kill_ob(zombie);
        } 
        message_vision( "\n\n$N惡狠狠地撲了上來。\n" , zombie);
        call_out("leave",10+random(10),zombie);
        if (! this_object()->is_busy())
                this_object()->start_busy(3);
}

void leave(object zombie){
        if (! zombie) return;
        message_vision("\n$N消失了。\n",zombie);
        destruct(zombie);
}
