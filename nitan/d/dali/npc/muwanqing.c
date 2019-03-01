// muwangqing.c

inherit NPC;

void create()
{
        set_name("木婉清",({ "mu wanqing", "mu", "wanqing" }) );
        set("gender", "女性" );
        set("age", 17);
        set("long", 
"她長得似新月清暈，如花樹堆雪，一張臉秀麗絕俗，只是過于蒼白，
沒半點血色，想是她長時面幕蒙臉之故，兩片薄薄的嘴唇，也是血
色極淡，神情楚楚可憐，嬌柔婉轉。\n");
        set("combat_exp", 200000);
        set("shen_type", 1);
        set("per", 29);
        set("str", 30);
        set("dex", 30);
        set("con", 30);
        set("int", 30);
        set("attitude", "friendly");
        set("max_qi", 1000);
        set("max_jing", 500);
        set("neili", 1200);
        set("max_neili", 1200);
        set("jiali", 100);

        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("cuff", 100);
        set_skill("strike", 100);
        set_skill("whip", 100);
        set_skill("sword", 100);
        set_skill("kurong-changong", 100);
        set_skill("tiannan-bu", 100);
        set_skill("jinyu-quan", 100);
        set_skill("duanjia-jian", 100);
        set_skill("wuluo-zhang", 100);
        set_skill("feifeng-bian", 100);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("whip", "feifeng-bian");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("sword", "duanjia-jian");
        map_skill("parry", "duanjia-jian");
        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");

        setup();
        carry_object("/d/dali/npc/obj/whitecloth1")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}
