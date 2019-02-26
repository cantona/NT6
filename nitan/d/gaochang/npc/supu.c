// supu.c 蘇普

inherit NPC;

void create()
{
        set_name("蘇普", ({ "su pu", "su", "pu"}));
        set("gender", "男性");
        set("age", 19);
        set("long", 
"一個健碩的哈薩克少年，頭人蘇魯克的孩子。\n");
        set("combat_exp", 20000);
        set("shen_type", 1);
        set("jiali", 10);

        set_skill("force", 20);
        set_skill("blade", 20);
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_skill("parry", 20);

        set("inquiry", ([
                "李文秀" : "計爺爺説那個漢人小姑娘已經不在人世了。\n",
                "蘇魯克" : "那是我爹。\n",
                "阿曼"   : "她不就在我旁邊麼！？\n",
        ]) );

        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        set_temp("apply/damage", 10);

        setup();
        carry_object("/d/xingxiu/obj/wandao")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
