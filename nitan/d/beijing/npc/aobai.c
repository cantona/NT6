inherit NPC;
#include <ansi.h>

void create()
{
        set_name("鰲拜", ({ "ao bai", "ao", "bai" }));
        set("age", 32);
        set("gender", "男性");
        set("title", "當朝第一大臣");
        set("nickname", HIR "滿洲第一勇士" NOR );
        set("long",
                "他就是滿洲第一勇士，身穿一件黃馬褂。他身材魁梧，\n"
                "相貌猙獰，太陽穴高高鼓起，似乎身懷絕世武功。\n");
        set("attitude", "peaceful");

        set("age", 50);
        set("shen_type", -1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 1500);
        set("max_jing", 1500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 100);
        set("combat_exp", 150000);
        set("score", 50000);

        set_skill("unarmed", 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
        set_skill("sword", 120);
        set_skill("force", 120);
        set_skill("huashan-sword", 120);
        set_skill("shaolin-shenfa", 120);
        set_skill("literate", 100);

        map_skill("dodge", "shaolin-shenfa");
        map_skill("parry", "huashan-sword");
        map_skill("sword", "huashan-sword");

        setup();
       carry_object("/d/beijing/npc/obj/goldcloth1")->wear();
        carry_object("/d/beijing/npc/obj/diaoqiu")->wear();
}

int accept_fight(object me)
{
	command("say 他奶奶的，你活膩了！來人，給我拿下！\n");
	me->apply_condition("killer", 500);
        kill_ob(me);
        return 1;
}
