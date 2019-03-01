// zutouren.c

inherit NPC;

void create()
{
        set_name("族頭人", ({ "zu touren", "touren" }));
        set("age", 42);
        set("gender", "男性");
        set("long", "這位是哈尼的族頭人，哈尼是大理國的第三大族，大多聚在大都
附近。此人貌甚精明，身穿對襟衣，亦是白布包頭。他坐在大土司的
右下首，對來人細細打量着。\n");
        set("attitude", "peaceful");

        set("str", 30);
        set("per", 20);
        set("dex", 36);
        set("combat_exp", 100000);
        set("shen_type", 1);

        set_skill("unarmed", 50);
        set_skill("dodge", 50);
        set_skill("parry", 40);
        set_skill("blade", 40);
        set_skill("force", 40);
        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/damage", 70);
        set_temp("apply/armor", 70);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
