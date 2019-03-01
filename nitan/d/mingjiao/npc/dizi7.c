// dizi7.c 地字門教眾
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("地字門教眾", ({"jiao zhong","zhong"}));
        set("long","這是一位楊逍屬下天字門的教眾。\n");
        set("gender", "女性");
        set("attitude", "peaceful");
        set("age", 15+random(20));
        set("str", 20);
        set("int", 20);
        set("con", 20);
        set("dex", 20);
        set("max_qi", 400);
        set("max_jing", 300);
        set("neili", 400);
        set("max_neili", 400);
        set("jiaji", 1);
        set("combat_exp", 20000+(random(20000)));
        set_skill("force", 30);
        set_skill("shenghuo-shengong", 30);
        set_skill("dodge", 30);
        set_skill("piaoyi-shenfa", 30);
        set_skill("cuff", 30);
        set_skill("liehuo-jian", 30);
        set_skill("parry", 30);
        set_skill("sword", 30);
        map_skill("force", "shenghuo-shengong");
        map_skill("dodge", "piaoyi-shenfa");
        map_skill("parry", "liehuo-jian");
        map_skill("sword", "liehuo-jian");
        setup();
        create_family("明教",39,"教眾");
        carry_object("/clone/weapon/duanjian")->wield();
        carry_object("/d/mingjiao/obj/black-cloth")->wear();
}

void attempt_apprentice(object ob)
{     
        command("say 呵呵，我武功低微，可不敢收徒啊。");
        return;
}
