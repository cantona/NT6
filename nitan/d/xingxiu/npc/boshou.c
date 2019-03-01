// boshou.c 鈸手

inherit NPC;

void create()
{
        set_name("星宿派鈸手", ({ "boshou"}));
        set("long", 
                "他是星宿派的擊鈸手。\n"
                "他手中拿着一對銅鈸，一邊敲一邊扯着嗓子唱些肉麻的話。\n");
        set("gender", "男性");
        set("age", 33);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 26);
        set("int", 16);
        set("con", 22);
        set("dex", 24);

        set("max_qi", 200);
        set("max_jing", 200);
        set("neili", 200);
        set("max_neili", 200);
        set("jiali", 10);
        set("combat_exp", 2000);

        set_skill("force", 20);
        set_skill("dodge", 20);
        set_skill("unarmed", 20);
        set_skill("parry", 20);

//      create_family("星宿派", 3, "吹鼓手");

        setup();
        set("chat_chance", 2);
        set("chat_msg", ({
"鈸手敲着銅鈸，高聲唱道，“星～宿～老～仙，威～震～寰～宇”。\n",
"鈸手敲着銅鈸，高聲唱道，“星～宿～老～仙，德～配～天～地”。\n",
"鈸手敲着銅鈸，高聲唱道，“星～宿～老～仙，古～今～無～比”。\n",
        }) );

        carry_object("/d/xingxiu/obj/tongbo")->wield();
}
