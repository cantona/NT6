#include <ansi.h>

inherit NPC;

#define PLACE "bjw"     //長安
#define TYPE  "good"    //白道
#define WAIT_TIME 60    //完成不了任務的反省時間

mapping bunch_good = ([
        "bunch_name" : "無極幫",
        "id"   : "wjb",
        "place": "bjw",
        "boss" : "鍾百雄",
        "type" : "good",
        
]);

void create()
{
        set_name("鍾百雄", ({ "zhong baixiong", "zhong" }));
        set("gender", "男性");
        set("age", 42);
        set("long", "他就是大名鼎鼎的鐘百雄鍾大俠。\n");
        set("nickname",HIY"楚霸王"NOR);
        set("title","無極幫北京西城分舵");
        set("per",23);
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
