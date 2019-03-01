// boss-ju.c 
#include <ansi.h>

inherit NPC;

#define PLACE "cd"     //揚州
#define TYPE  "bad"    //黑道
#define WAIT_TIME 60    //完成不了任務的反省時間



mapping bunch_bad = ([
        "bunch_name" : "修羅門",
        "id"   : "xlm",
        "place": "cd",
        "boss" : "冷無風",
        "place_name": "成都",
        "type" : "bad",
]);

void create()
{
        set_name("冷無風", ({ "leng wufeng", "leng","wufeng" }));
        set("gender", "男性");
        set("age", 32);
        set("long", "他看起來冷冷的，面部好象僵住了一般，沒有一點表情變化。他就是" + bunch_bad["bunch_name"] + "的成都壇主。\n");
        set("title",HIB"修羅門成都壇主"NOR);
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
#include <boss_bad.h>

