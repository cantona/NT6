#include <ansi.h>

inherit NPC;

#define PLACE "hz"     //長安
#define TYPE  "bad"    //白道
#define WAIT_TIME 60    //完成不了任務的反省時間

mapping bunch_bad = ([
        "bunch_name" : "小刀會",
        "id"   : "xdh",
        "place": "hz",
        "boss" : "馬六",
        "place_name" : "杭州",
        "type" : "bad",
]);

void create()
{
        set_name("馬六", ({ "ma liu", "ma" }));
        set("gender", "男性");
        set("age", 29);
        set("long", "他就是本地的地頭蛇組織" + bunch_bad["bunch_name"] + "的頭子。\n");
        set("nickname",HIY"無惡不作"NOR);
        set("title","小刀會杭州分舵頭子");
        set("per",20);
        set("combat_exp", 1000000);
        set("shen_type", -1);

        set("attitude", "peaceful");
        
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",2);
}

#include "boss_bad.h"
