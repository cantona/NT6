#include <ansi.h>
inherit NPC;
void create()
{
        set_name("錢二敗", ({ "qian erbai","qian","erbai"}) );
        set("long",@LONG
那人看來不算老，卻臉皮都皺了起來，身材矮小，原本應是個毫不起眼的漢子，
可是他一對眼睛神芒閃爍，銳利至像能透視別人肺腑般，一腳踏在凳上，手肘枕在膝
頭處托著箭壺，有種穩如泰山的感覺，在在都使人感到他絕非平凡之輩。
LONG
         );
        set("title",BLU"神箭八雄"NOR);
        set("nickname","穿雲箭");
        set("max_jing", 6000);
        set("max_qi", 6000);                    
        set("max_sen", 6000);
        set("max_neili",6000); 
        set("neili",6000);
        set("jiali",120);     
        set("combat_exp",5800000);
        set("cor",200);
        set("kar",200);
        set("age",65);
        set_skill("pixie-jian", 420);
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
        set_temp("apply/attack",50);
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
