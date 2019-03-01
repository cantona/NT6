// haoshou.c 號手

inherit NPC;

void create()
{
        set_name("星宿派號手", ({ "haoshou" }));
        set("long", 
                "他是星宿派的吹號手。\n"
                "他手中拿著一只銅號，鼓足力氣一臉沉醉地吹著。\n");
        set("gender", "男性");
        set("age", 33);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 26);
        set("int", 16);
        set("con", 22);
        set("dex", 24);

        set("max_qi", 300);
        set("max_jing", 300);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", 10);
        set("combat_exp", 3000);

        set_skill("force", 30);
        set_skill("dodge", 30);
        set_skill("unarmed", 30);
        set_skill("parry", 30);

//      create_family("星宿派", 3, "吹鼓手");

        setup();
/*        set("chat_chance", 2);
        set("chat_msg", ({
"吹鼓手敲著銅鈸，高聲唱道，“星～宿～老～仙，威～震～寰～宇”。\n",
"吹鼓手敲著銅鈸，高聲唱道，“星～宿～老～仙，德～配～天～地”。\n",
"吹鼓手敲著銅鈸，高聲唱道，“星～宿～老～仙，古～今～無～比”。\n",
        }) );
*/

        carry_object("/d/xingxiu/obj/tonghao")->wield();
}
