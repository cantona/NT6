//zsh_duan.c

#include <ansi.h>

inherit NPC;

#define PLACE "bje"     //北京分會
#define TYPE  "good"    //白道
#define WAIT_TIME 60    //完成不了任務的反省時間

mapping bunch_good = ([ 
        "bunch_name" : "紫衫會",
        "id"   : "zsh",
        "place": "sz",      //總會
        "boss" : "宋大先生",
        "place_name" : "北京", //分會
        "type" : "good",
]);

void create()
{
        set_name("段清", ({ "duan qing", "duan" }));
        set("gender", "男性");
        set("age", 28);
        set("long", "他就是" + bunch_good["bunch_name"] + "設在" + bunch_good["place_name"] + "的分會會長。\n");
        set("nickname",HIY"綸扇書生"NOR);
        set("title",GRN"紫衫會北京分會會長"NOR);
        set("per",28);
        set("combat_exp", 800000);
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
