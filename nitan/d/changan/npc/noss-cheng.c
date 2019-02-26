//boss-cheng.c

#include <ansi.h>

inherit NPC;

#define PLACE "ca"      // 長安
#define TYPE  "good"    // 白道
#define WAIT_TIME 60    // 完成不了任務的反省時間

mapping bunch_good = ([
        "name" : "俠義盟",
        "id"   : "xym",
        "place": "ca",
        "boss" : "成中嶽",
        "type" : "good",
]);

void create()
{
        set_name("成中嶽", ({ "cheng zhongyue", "cheng" }));
        set("gender", "男性");
        set("age", 45);
        set("long", "他就是鼎鼎大名的" + bunch_good["bunch_name"] + "的總瓢把子。\n");
        set("nickname",HIY"俠肝義膽"NOR);
        set("title","俠義盟大當家");
        set("per",20);
        set("combat_exp", 1000000);
        set("shen_type", 1);

        set("attitude", "peaceful");
        
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",2);
}

#include <boss_good.h>