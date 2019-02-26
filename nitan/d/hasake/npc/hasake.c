inherit NPC;
void create()
{
        set_name("哈薩克牧民", ({ "hasake", "mu min"}));
        set("gender", "男性");
        set("age", 26);
        set("long", "一位健壯的哈薩克族民，正趕着幾十只羊。\n");
        set("attitude", "friendly");
        set("combat_exp", 4000 + random(500));
        set("str", 32);
        set("int", 18);
        set("con", 22);
        set("dex", 17);
        set("max_qi", 300);
        set("max_jing", 300);
        set("neili", 300);
        set("max_neili", 300);
        set("jiali", 5);
        set_skill("unarmed", 20);
        set_skill("blade", 20);
        set_skill("parry", 20);
        set_skill("dodge", 20);

        set_temp("apply/attack", 25);
        set_temp("apply/defense", 25);
        set_temp("apply/damage", 25);
        
        set("inquiry", ([
            "蘇普" : "蘇普是蘇魯克的兒子，跟他爹一樣是個好漢子！\n",
            "蘇魯克" : "蘇魯克是我們哈薩克人中的大英雄，他有個兒子叫蘇普。\n",
            "阿曼" : "阿曼是草原上一朵會走路的花。\n",
            "計老人" : "計老人會釀又香又烈的美酒，會醫牛羊馬匹的疾病。\n",
        ]) );

        setup();
        set("chat_chance", 5);
        set("chat_msg", ({
"哈薩克牧民高興地説: 上個月，我用刀砍死了一頭狼，剝了狼皮送給咱阿妹。\n",
"哈薩克牧民道:  歡迎來到我們哈薩克部族，請去喝碗香甜的乳酪吧。\n",
        }) );
        carry_object(__DIR__"obj/madao")->wield();
        carry_object(__DIR__"obj/yangao")->wear();
        carry_object(__DIR__"obj/jiunang");
}
