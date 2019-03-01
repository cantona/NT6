// jian-ke.c
#include <ansi.h>
inherit NPC;
void create()
{
    set_name("劍客", ({ "jian ke","ke" }) );
    set("gender", "男性");
    set("age", 45);
    set("long",
        "這是位中年武人，肩背長劍，長長的劍穗隨風飄揚，看來似乎身懷絕藝。\n");
    set("combat_exp", 20000);
        set("shen_type", -1);
    set("attitude", "heroism");
    set("apply/attack",  30);
    set("apply/defense", 30);
    set_skill("sword", 60);
    set_skill("unarmed", 50);
    set_skill("parry", 50);
    set_skill("dodge", 50);
    setup();
    carry_object("/d/city/obj/changjian")->wield();
    carry_object("/clone/misc/cloth")->wear();
    add_money("silver", 20);
}