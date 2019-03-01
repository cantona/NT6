#include <ansi.h>
inherit NPC;
void create()
{
        set_name("吳六破", ({ "wu liupo","wu","liupo"}) );
        set("long",@LONG
他高瘦筆直、傲然挺立，自有一股書香世家的氣質．蒼白的臉帶著濃烈的
書卷氣，看上去很年青，但兩鬢偏已斑自，他的儒服兩袖高高捋趄，露出雪白
的手臂，手十指尖長，尤勝女孩兒家的手。尤其使人注目的是他耳朵上挾著一
根銀光閃閃長若五寸的針。
LONG
         );

        set("title",MAG"神箭八雄"NOR);
       set("nickname","散毒箭");
        set("max_jing", 6000);
        set("max_qi", 6000);                    
        set("max_sen", 6000);
        set("max_neili",6000); 
        set("neili",6000);
        set("jiali",180);     
        set("combat_exp",4500000);
        set("cor",100);
        set("age",65);

        set_skill("force", 400);
        set_skill("huagong-dafa", 480);
        set_skill("dodge", 480);
        set_skill("zhaixinggong", 410);
        set_skill("unarmed", 450);
        set_skill("xingxiu-duzhang", 400);
        set_skill("parry", 450);
        set_skill("staff", 470);
        set_skill("tianshan-zhang", 415);
        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("unarmed", "xingxiu-duzhang");
        map_skill("parry", "tianshan-zhang");
        map_skill("staff", "tianshan-zhang");
        set_temp("apply/attack",50);
        setup();
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
