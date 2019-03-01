// qian.c

inherit NPC;

#include <ansi.h>;
void create()
{
        set_name("錢青健", ({ "qian qingjian", "qian", "qingjian" }));
        set("gender", "男性");
        set("title", HIY"黃河四鬼老四"NOR);
        set("nickname", HIC"喪門斧"NOR);
        set("age", 32);
        set("str", 25);
        set("dex", 16);
        set("per", 16);
        set("long", "錢青健是黃河四鬼的老四，是鬼門龍王沙通天的四弟子，擅
於斧法。\n");
        set("combat_exp", 20000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("unarmed", 30);
        set_skill("force", 30);
        set_skill("axe", 30);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 30);

        set("neili", 400);
        set("max_neili", 400);
        set("jiali", 10);

        setup();
        carry_object(__DIR__"obj/axe")->wield();
        carry_object("/clone/misc/cloth")->wear();
}
