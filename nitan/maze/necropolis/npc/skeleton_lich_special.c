#include <ansi.h>

inherit "/maze/necropolis/necropolis_npc";
void do_bone_spirit();
void create()
{
        string *names = ({"巫妖"}); 
        // set_name( names[random(sizeof(names))], ({ "skeleton lich","skeleton"}));
        set_name( names[random(sizeof(names))], ({ "skeleton lich" }));
        set("vendetta_mark","skeleton");
        set("long", "這是一只骨頭架子。\n");
        set("title", HIB "(鬼氣)" NOR); 

        set("str", 50);
        set("con", 120);
        set("dex", 50); 
        set("int", 50);
        set("max_qi", 150000);
        set("max_jing", 160000);
        set("neili", 550000);
        set("max_neili", 550000);
        set("max_jingli", 80000);
        set("attitude", "peaceful");
/*
        set("chat_chance", 1);
        set("chat_msg", ({
                "骷髏空洞的眼眶裡閃爍著可怕的熒光。\n"
        }) ); 
*/
        set("death_msg",BLU"\n$N散成了一堆碎骨頭。\n\n"NOR);
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: do_bone_spirit() :),
        }) ); 

        set("combat_exp", 300000000);
        set("bellicosity",1000000 );

        set_skill("force", 220);
        set_skill("dodge", 220);
        set_skill("unarmed", 220);
        set_skill("staff", 220);
        set_skill("parry", 220);           
        set_temp("apply/attack", 2000);
        set_temp("apply/parry", 1500);
        set_temp("apply/damage", 2000);
        set("drops", ([
                 "RA&RARE40" : 70, 
                 "RA&RARE50" : 30, 
        ]));

        setup();
        carry_object(__DIR__"obj/bone_staff")->wield();
} 

int is_undead() {
        return 1;
}

void do_bone_spirit() {
        object *enemies,enemy;
        int i,no_busy;
        message_vision(BLU"\n$N沙啞的聲音念誦著咒語，周身凝聚了一個個散發著死亡氣息的光球！\n\n"NOR,this_object());
        enemies = query_enemy();
        foreach(enemy in enemies) {
                if(!enemy)
                        continue;
                if(!present(enemy, environment(this_object())))
                        continue;
                i = random(5);
                if(i>=3)
                        i=random(2);
                switch (i)
                {
                case(0):
                        message_vision(RED"一個紅色光球擊中$N爆炸開來！\n"NOR,enemy);
                        enemy->receive_damage("qi",4000+random(4000),this_object());
                        COMBAT_D->report_status(enemy);
                        break;
                case(1):
                        message_vision(GRN"一個綠色光球圍繞$N轉了一圈！\n"NOR,enemy);
                        message_vision(GRN"$N神志變得模糊起來......\n"NOR,enemy);
                        if(!enemy->is_busy())
                                enemy->start_busy(3);
                        break;
                case(2):
                        message_vision(BLU"一個黑色光球悄無聲息的湮滅在$N的眉心處！"NOR,enemy);
                        enemy->unconcious();
                        break;
                }
        }
        if (this_object() && ! this_object()->is_busy())
                this_object()->start_busy(2);
}