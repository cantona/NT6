// jiading.c 家丁

inherit NPC;

void create()
{
        set_name("裘千丈", ({ "qiu qianzhang", "qiu" }));
        set("nickname", "肉掌水底鑽");
        set("gender", "男性");
        set("age", 65);
        set("long", "他有個弟弟叫裘千仞，他還有個妹妹叫裘千尺。他自己，雖然比弟弟
多了三千尺，比妹妹更是多了九千尺，手上的功夫呢卻比他們稀鬆至
少九萬尺。\n"); 
        set("per",14);
        set("combat_exp", 50000);
        set_skill("dodge", 50);
        set_skill("lingxu-bu", 50);
        set_skill("unarmed", 50);
        set_skill("parry", 50);
        set_skill("changquan", 50);
        map_skill("dodge", "lingxu-bu");
        map_skill("parry", "changquan");
        map_skill("unarmed", "changquan");
        set("shen_type", -1);
        setup();

        add_money("silver",3);
        carry_object("/clone/misc/cloth")->wear();
}
