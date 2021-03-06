// mawude.c

#include <ansi.h>

inherit NPC;
inherit F_DEALER;

void create()
{
        set_name("馬五德", ({ "ma wude", "ma" }));
        set("title","金牛武館館長");
        set("long", "馬老爺子是武館的締造者，辛苦一輩子了，仍勇於提攜後生。\n");
        set("gender", "男性");
        set("age", 65);

        set_skill("dodge", 80);
        set_skill("force", 80);
        set_skill("parry", 80);
        set_skill("unarmed", 80);
        set_skill("hand", 80);
        set_skill("blade", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 400000);
            set("vendor_goods", ({ 
                    "/clone/book/advance-dagger", 
                    "/clone/book/advance-blade", 
                    "/clone/book/advance-sword", 
                    "/clone/book/advance-unarmed", 
                    "/clone/book/advance-dodge", 
                    "/clone/book/advance-parry", 
                    "/clone/book/advance-force", 
                    "/clone/book/advance-staff", 
                    "/clone/book/advance-whip", 
                    "/clone/book/advance-throwing", 
                    "/clone/book/advance-cuff", 
                    "/clone/book/advance-hand", 
                    "/clone/book/advance-strike", 
                    "/clone/book/advance-finger", 
                    "/clone/book/advance-claw", 
                    "/clone/book/advance-club", 
            })); 
        set("shen_type", 1);
        setup();

/*
        carry_object("/clone/book/advance-sword");
        carry_object("/clone/book/advance-sword");
        carry_object("/clone/book/advance-sword");
        carry_object("/clone/book/advance-sword");
        carry_object("/clone/book/advance-sword");
        carry_object("/clone/book/advance-blade");
        carry_object("/clone/book/advance-blade");
        carry_object("/clone/book/advance-blade");
        carry_object("/clone/book/advance-blade");
        carry_object("/clone/book/advance-blade");
        carry_object("/clone/book/advance-dagger");
        carry_object("/clone/book/advance-dagger");
        carry_object("/clone/book/advance-dagger");
        carry_object("/clone/book/advance-dagger");
        carry_object("/clone/book/advance-dagger");
        carry_object("/clone/book/advance-unarmed");
        carry_object("/clone/book/advance-unarmed");
        carry_object("/clone/book/advance-unarmed");
        carry_object("/clone/book/advance-unarmed");
        carry_object("/clone/book/advance-unarmed");
        carry_object("/clone/book/advance-dodge");
        carry_object("/clone/book/advance-dodge");
        carry_object("/clone/book/advance-dodge");
        carry_object("/clone/book/advance-dodge");
        carry_object("/clone/book/advance-dodge");
        carry_object("/clone/book/advance-parry");
        carry_object("/clone/book/advance-parry");
        carry_object("/clone/book/advance-parry");
        carry_object("/clone/book/advance-parry");
        carry_object("/clone/book/advance-parry");
        carry_object("/clone/book/advance-force");
        carry_object("/clone/book/advance-force");
        carry_object("/clone/book/advance-force");
        carry_object("/clone/book/advance-force");
        carry_object("/clone/book/advance-force");
        carry_object("/clone/book/advance-staff");
        carry_object("/clone/book/advance-staff");
        carry_object("/clone/book/advance-staff");
        carry_object("/clone/book/advance-staff");
        carry_object("/clone/book/advance-staff");
        carry_object("/clone/book/advance-whip");
        carry_object("/clone/book/advance-whip");
        carry_object("/clone/book/advance-whip");
        carry_object("/clone/book/advance-whip");
        carry_object("/clone/book/advance-whip");
        carry_object("/clone/book/advance-throwing");
        carry_object("/clone/book/advance-throwing");
        carry_object("/clone/book/advance-throwing");
        carry_object("/clone/book/advance-throwing");
        carry_object("/clone/book/advance-throwing");
        carry_object("/clone/book/advance-cuff");
        carry_object("/clone/book/advance-cuff");
        carry_object("/clone/book/advance-cuff");
        carry_object("/clone/book/advance-cuff");
        carry_object("/clone/book/advance-cuff");
        carry_object("/clone/book/advance-hand");
        carry_object("/clone/book/advance-hand");
        carry_object("/clone/book/advance-hand");
        carry_object("/clone/book/advance-hand");
        carry_object("/clone/book/advance-hand");
        carry_object("/clone/book/advance-strike");
        carry_object("/clone/book/advance-strike");
        carry_object("/clone/book/advance-strike");
        carry_object("/clone/book/advance-strike");
        carry_object("/clone/book/advance-strike");
        carry_object("/clone/book/advance-finger");
        carry_object("/clone/book/advance-finger");
        carry_object("/clone/book/advance-finger");
        carry_object("/clone/book/advance-finger");
        carry_object("/clone/book/advance-finger");
        carry_object("/clone/book/advance-claw");
        carry_object("/clone/book/advance-claw");
        carry_object("/clone/book/advance-claw");
        carry_object("/clone/book/advance-claw");
        carry_object("/clone/book/advance-claw");
*/
}

void init()
{
        add_action("do_buy", "buy");
        add_action("do_list", "list");
}

int recognize_apprentice(object ob)
{
        if( !query_temp("marks/jinniu_paied", ob) == 1)return 0;
        return 1;
}
