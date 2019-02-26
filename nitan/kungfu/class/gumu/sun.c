// sun.c 孫婆婆
// Last Modified by winder on Feb. 28 2001

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("孫婆婆", ({"sun popo", "sun"}));
        set("gender", "女性");
        set("age", 55);
        set("long",
                "這是一位慈祥的老婆婆，正看着你微微一笑。\n"
        );
        set("attitude", "friendly");

        set("qi", 1200);
        set("max_qi", 1200);
        set("jing", 400);
        set("max_jing", 400);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 40);

        set("combat_exp", 150000);
        set("score", 0);

        set_skill("force", 100);
        set_skill("yunv-xinfa", 100);    //玉女心法
        set_skill("sword", 90);
        set_skill("yunv-jian", 120);     //玉女劍
        set_skill("dodge", 70);
        set_skill("yunv-shenfa", 120);   //玉女身法
        set_skill("quanzhen-jian", 50);
        set_skill("qufeng", 100);
        set_skill("parry", 60);
        set_skill("unarmed",80);
        set_skill("meinv-quan", 120);    //美女拳法
        set_skill("literate",80);

        map_skill("force", "yunv-xinfa");
        map_skill("sword", "yunv-jian");
        map_skill("dodge", "yunv-shenfa");
        map_skill("parry", "meinv-quan");
        map_skill("unarmed", "meinv-quan");

        create_family("古墓派", 3, "弟子");
        set("inquiry", ([
                "小龍女" : "龍姑娘是我一手帶大的，她從小沒了父母，現在又獨個兒住在這古墓裏，唉..\n",
        ]) );

        set("env/wimpy", 50);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("clone/misc/cloth")->wear();

}
