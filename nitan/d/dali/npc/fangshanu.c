// fangshanu.c

inherit NPC;

void create()
{
    set_name("紡紗女",({ "fangsha nv", "girl" }) );
        set("gender", "女性" );
        set("age", 17);
        set("long", "一個年輕的擺夷村婦，心靈手巧，專擅紡紗。\n");
         set_temp("apply/defense", 5);
        set("combat_exp", 2000);
//        set("shen", 100);
        set("shen_type", 1);
        set("per", 18);
        set("str", 14);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/d/dali/npc/obj/bduanqun")->wear();
}
