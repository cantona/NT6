// Room: /d/xingxiu/npc/xxdizi.c
// Last Modified by winder on Apr. 25 2001

inherit NPC;
void create()
{
        set_name("星宿派弟子", ({ "xingxiu dizi", "dizi"}));
        set("long", "他是星宿派的惡徒, 燒殺搶姦賭, 無惡不作。\n");
        set("gender", "男性");
        set("age", 30 + random(10));
        set("attitude", "peaceful");
        set("shen", -1000);

        set("str", 30);
        set("int", 20);
        set("con", 22);
        set("dex", 22);

        set("max_qi", 500);
        set("max_jing", 500);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 20);
        set("combat_exp", 10000 + random(20000));

        set_skill("force", 50);
        set_skill("huagong-dafa", 30);
        set_skill("dodge", 50);
        set_skill("zhaixinggong", 30);
        set_skill("strike", 50);
        set_skill("chousui-zhang", 30);
        set_skill("parry", 50);
        map_skill("force", "huagong-dafa");
        map_skill("dodge", "zhaixinggong");
        map_skill("strike", "chousui-zhang");
        map_skill("parry", "chousui-zhang");
        prepare_skill("parry", "chousui-zhang");

        create_family("星宿派", 3, "弟子");
        setup();
        carry_object("/clone/cloth/dao-cloth")->wear();
        set("chat_chance", 5);
        set("chat_msg", ({
                "星宿派弟子一會兒吹奏絲竹簫管, 一會兒高聲頌道，“星～宿～老～仙，古～今～無～比”。\n",
                "星宿派弟子一會兒吹奏絲竹簫管, 一會兒高聲頌道，“星～宿～老～仙，威～震～寰～宇”。\n",
                "星宿派弟子一會兒吹奏絲竹簫管, 一會兒高聲頌道，“星～宿～老～仙，德～配～天～地”。\n",
        }) );

}