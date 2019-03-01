//NPC /d/city/npc/kanmenseng.c
#include <ansi.h>
inherit NPC;
void greeting(object ob);
void create()
{
        set_name("看門僧", ({ "kanmen seng", "seng" })); 
        set("long", "一個中年僧人，卻是一臉的疲態，一雙眼睛倒不象是出家人，勢利得很。\n");
        set("gender", "男性");
        set("class", "bonze");
        set("title", "禪智寺和尚");
        set("age", 35);
        set("attitude", "friendly");
        set("shen_type", -1);

        set("per", 15);
        set("str", 15);
        set("int", 14);
        set("con", 15);
        set("dex", 16);
        set("qi", 200);
        set("max_qi", 200);
        set("jing", 100);
        set("max_jing", 100);
        set("neili", 10);
        set("max_neili", 10);
        set("combat_exp", 2000);

        set_skill("unarmed", 10);
        set_skill("dodge", 10);
        set_skill("parry", 10);

        setup();
        carry_object("/d/shaolin/obj/cloth")->wear();
}