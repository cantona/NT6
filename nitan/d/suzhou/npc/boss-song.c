#include <ansi.h>


inherit NPC;

#define PLACE "sz"     //長安
#define TYPE  "good"    //白道
#define WAIT_TIME 60    //完成不了任務的反省時間

mapping bunch_good = ([
        "bunch_name" : "紫衫會",
        "id"   : "zsh",
        "place": "sz",
        "boss" : "宋大先生",
        "type" : "good",
]);

void create()
{
        set_name("宋大先生", ({ "song xiansheng", "song" }));
        set("gender", "男性");
        set("age", 46);
        set("long", "他就是鼎鼎大名的" + bunch_good["bunch_name"] + "的主管。\n");
        set("nickname",HIY"袖裏乾坤"NOR);
        set("title","紫衫會主管");
        set("per",28);
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
