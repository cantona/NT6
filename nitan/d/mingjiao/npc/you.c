inherit NPC;
#include <ansi.h>
void create()
{
        set_name("遊客", ({ "you ke",  "ke" }) );
        if(random(10)<6) set("gender","男性");
        else set("gender","女性");
        set("age", 20+random(40));
        set("str", 16);
        set("attitude", "peaceful");
        set("long", "這個人看起來似乎不大高興。\n");
        set("combat_exp", 1000+random(500));
        set_skill("unarmed", 60);
        set_skill("parry", 60);
        set_skill("dodge", 60);
        set_skill("force", 60);
        set_skill("literate", 60);
        set("chat_chance",3);
        set("chat_msg",({
                CYN"遊客大叫道：倒黴！真倒黴！\n"NOR,
                CYN"遊客看着你惡狠狠的説道：你！小心點！這事沒這麼容易了結！\n"NOR,
        }) );
        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/clone/weapon/gangjian")->wield();
        add_money("silver", 10);
}
