// tanghua.c

inherit NPC;

void create()
{
        set_name("唐掌櫃", ({ "tang", "boss" }) );
        set("long",
                "唐掌櫃是這家大酒樓的主人，別看他只是一個小小的酒樓老闆，在成\n"
                "都除了提督老爺以外，恐怕就屬他最財大勢大。\n" );
        set("age", 46);
        set("attitude", "peaceful");
        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_temp("apply/attack", 30);
        set_temp("apply/attack", 30);
        set_temp("apply/damage", 15);

        set("combat_exp", 50000);
        set("attitude", "friendly");
        
        set("inquiry", ([
                "name": "在下姓唐單名一個樺字。\n",
                "here": "此處便是蓉城酒樓，客倌如要點菜，吩咐店裏的小二一聲便可。\n",
                "唐樺": "不敢，在下便是唐樺，不知客倌有何吩咐？\n",
                "蓉城酒樓": "這裏就是，客倌是第一次來嗎？\n"
        ]) );
        setup();
        add_money("silver", 15);
        carry_object("/clone/misc/cloth")->wear();
}
