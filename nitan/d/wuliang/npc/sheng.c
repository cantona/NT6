// shen.c
// Date: Oct.18 1999 by Winder
#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("阿勝", ({ "sheng" }));
        set("title", HIY"神農幫幫眾"NOR);
        set("age", 32);
        set("gender", "男性");
        set("long", "這是一個神農幫的幫眾，身穿黃衣，肩懸藥囊，手持一柄藥鋤。\n");
        set("attitude", "peaceful");

        set("str", 24);
        set("per", 20);
        set("dex", 16);
        set("combat_exp", 30000);
        set("shen_type", 1);

        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_skill("hammer", 60);
        set_skill("force", 60);
        set_temp("apply/attack", 60);
        set_temp("apply/defense", 60);
        set_temp("apply/damage", 40);
        set_temp("apply/armor", 60);

        setup();
        carry_object("/d/xingxiu/npc/obj/yaochu")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}