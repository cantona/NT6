#include <ansi.h>
inherit NPC;
void create()
{
        set_name("孫三毀", ({ "sun sanhui","sun","sanhui"}) );
        set("long",@LONG
他背上斜插著把長箭，高瘦修長，卻絲毫不給人半點體弱的感覺。整個人
像以鋼筋架成，深藏著驚人的力量。使人覺得他不動則已，一動起來必是萬分
迅捷靈巧。他面貌長而削，顴骨高起，雙睛神采異常，光華隱現。
LONG
         );
        set("title",CYN"神箭八雄"NOR);
       set("nickname","穿心箭");
        set("max_jing", 6000);
        set("max_qi", 5000);                    
        set("max_sen", 6000);
        set("max_neili",6000); 
        set("neili",6000);
        set("jiali",90);     
        set("combat_exp",4800000);
        set("cor",150);
        set("age",35);
        set_skill("pixie-jian", 420);
        set_skill("dodge", 500);
        set_skill("parry", 400);
        set_skill("sword",420);
        set_skill("force",800); //防止別人來彈指
        set_skill("hamagong",500);
        set_skill("tiyunzong",400);
        map_skill("sword","pixie-jian");
        map_skill("parry","pixie-jian");
        map_skill("dodge","tiyunzong");
        map_skill("force","hamagong");
        set_temp("apply/damage",50);
        set("chat_chance_combat",10);
        set("chat_msg_combat", ({
                (: exert_function,"powerup" :),
        }) );

        setup();
        carry_object("/clone/weapon/changjian")->wield();
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player())) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
         if(random(15) < 2)
                this_object()->set_leader(ob);
        }
}
