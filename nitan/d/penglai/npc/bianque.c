// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

void create()
{
        if (random(2))
                set_name(HIC "扁鵲" NOR, ({ "bian que", "bian", "que" }));
        else
                set_name(HIC "秦越人" NOR, ({ "qin yueren", "qin", "yueren" }));                
                
        set("long", HIC "生活在春秋戰國時期的扁鵲，據説後來得仙人指引，修成正果。\n" NOR);

        set("gender", "男性");
        set("age", 9999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("unarmed", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);
        set_skill("medical", 2500);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "蓬萊仙島"               :   "這不是你該來的地方，我看你還是快走吧。\n",
        ]));
        
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object("/kungfu/class/sky/npc/obj/xianpao")->wear();
}

void unconcious()
{
        die();
}
