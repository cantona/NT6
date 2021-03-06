// abi.c

inherit NPC;

void create()
{
        set_name("阿碧", ({ "abi", "bi" }));
        set("long",
                "這是個身穿綠衣的女郎，約十六七歲年紀，滿臉都是温柔，\n"
                "滿身都是秀氣。一張可愛的瓜子臉，膚白如新剝鮮藕，説話\n"
                "聲音極甜極清，令人一聽之下説不出的舒適。嘴角邊一粒細\n"
                "細的黑痔，更增俏媚。\n");
        set("gender", "女性");
        set("age", 16);
        set("shen_type", 1);

        set("neili", 200);
        set("max_neili", 200);
        set("max_qi", 160);
        set("max_jing", 160);
        set_skill("force", 40);
        set_skill("unarmed", 40);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set_skill("sword", 30);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        set_temp("apply/damage", 5);

        set("combat_exp", 10000);
        set("inquiry",([
            "曼陀山莊" : "我才不敢去曼陀山莊，王夫人太霸道了!\n",
            "王語嫣"   : "哎，只有她才配得上我們公子，也不知她現在怎麼樣了!\n",
            "阿朱"     : "那小妮子只大我一歲，整天就喜歡扮別人玩。\n",
        ]) );
        setup();
        carry_object(__DIR__"obj/goldring")->wear();
        carry_object(__DIR__"obj/necklace")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object(__DIR__"obj/green_cloth")->wear();
        carry_object(__DIR__"obj/flower_shoe")->wear();
}
