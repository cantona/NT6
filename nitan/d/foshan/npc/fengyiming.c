inherit NPC;

void create()
{
        set_name("鳳一鳴", ({ "feng yiming", "feng", "yiming" }));
        set("long", @LONG
鳳一鳴是佛山鎮上大財主鳳天南之子。只見他
步履輕捷，臉上英氣勃勃，顯是武功不弱。
LONG);
        set("title", "佛山五虎門傳人");
        set("gender", "男性");
        set("age", 25);
        set("combat_exp", 40000);
        set_skill("unarmed", 50);
        set_skill("force", 60);
        set_skill("blade", 80);
        set_skill("dodge", 50);
        set_skill("parry", 50);

        set_temp("apply/attack", 30);
        set_temp("apply/defense", 30);
        set_temp("apply/armor", 5);
        set_temp("apply/damage", 10);
        setup();

        carry_object("/clone/cloth/fu-cloth")->wear();
        carry_object("/clone/cloth/jade-belt")->wear();
}