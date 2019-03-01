inherit NPC;
void create()
{
        set_name("哈薩克婦女", ({ "hasake", "woman"}));
        set("gender", "女性");
        set("age", 25);
        set("long", "一位熱情好客的哈薩克族婦女。\n");
        set("attitude", "friendly");
        set("combat_exp", 500);
        set("str", 18);
        set("int", 18);
        set("con", 18);
        set("dex", 17);
        set("max_qi", 140);
        set("max_jing", 140);
        set("neili", 100);
        set("max_neili", 100);
        set_skill("unarmed", 10);
        set_skill("parry", 10);
        set_skill("dodge", 10);
        set_temp("apply/attack", 5);
        set_temp("apply/defense", 5);
        set_temp("apply/damage", 5);
        set("inquiry", ([
            "阿曼" : "阿曼是草原上一朵會走路的花。\n",
            "李文秀" : "李文秀這孩子，長得和阿曼一樣美麗，歌也唱得好。\n",
        ]) );
        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
"哈薩克婦女道: 請進來坐坐吧，喝碗草原上香甜的乳酪。\n",
        }) );
        carry_object(__DIR__"obj/yangao")->wear();
        carry_object(__DIR__"obj/shuinang");
}
