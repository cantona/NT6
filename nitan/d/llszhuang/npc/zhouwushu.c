#include <ansi.h>
inherit NPC;
void create()
{
        set_name("周五輸", ({ "zhou wushu","zhou","wushu"}) );
        set("long",@LONG
周五輸身材高大，面貌粗獷，雙眼細長而常常帶上一種病態的黃色，使人不
欲久看。可是，周五輸另帶有一種神秘奇異的吸引力。
LONG
         );
        set("title",GRN"神箭八雄"NOR);
       set("nickname","穿雨箭");       
        set("max_jing", 4000);
        set("max_qi", 8000);                    
        set("max_sen", 4000);
        set("max_neili",7000); 
        set("neili",7000);
        set("jiali",50);     
        set("combat_exp",3500000);
        set("cor",100);
        set_skill("pixie-jian", 520);
        set_skill("dodge", 500);
        set_skill("parry", 500);
        set_skill("sword",420);
        set_skill("force",800); //防止別人來彈指
        set_skill("hamagong",500);
        set_skill("tiyunzong",500);
        map_skill("sword","pixie-jian");
        map_skill("parry","pixie-jian");
        map_skill("dodge","tiyunzong");
        map_skill("force","hamagong");
        set_temp("apply/damage",250);
        set("chat_chance",3);
        set("chat_msg", ({
                "周五輸凝視著窗外的明月，姿態悠閒之極。\n",
                "周五輸舉起盛滿了清溪流泉的酒壺喝了一大口，笑道：痛快，痛快！\n"
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
