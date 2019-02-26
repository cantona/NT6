// zhang3.c

#include <ansi.h>
inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
int do_skills(string arg);
int do_join(string arg);

void create()
{
        set_name("章老三", ({ "zhang laosan", "zhang" }));
        set("gender", "男性");
        set("age", 44);
        set("str", 25);
        set("dex", 20);
        set("long", "這是一個乾瘦老頭,一雙小眼睛賊閃發光。\n");
        set("combat_exp", 25000);
        set("score", 2000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("force", 50);
        set_skill("unarmed", 70);
        set_skill("dodge", 70);
        set_skill("parry", 70);
        set_skill("yixingbu", 40);
        set_skill("shenlong-bashi", 50);
        map_skill("parry", "shenlong-bashi");
        map_skill("dodge", "yixingbu");

        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set_temp("apply/armor", 10);
        set_temp("apply/damage", 10);
        set("neili", 500); 
        set("max_neili", 500);
        set("jiali", 10);
        set("inquiry", ([
                "洪安通" : "這三個字是你説的嗎？",
                "洪教主" : "洪教主仙福永享，壽與天齊，洪教主神目如電，燭照四方。",
                "蘇荃"   : "沒規沒矩的。",
                "神龍島" : "神龍島在汝州的東北方向，從塘沽口出海便到。",
                "神龍教" : "一般人是入不了我神龍教的(join shenlongjiao)。\n",
                "入教"   : "一般人是入不了我神龍教的(join shenlongjiao)。\n",
                "教主"   : "教主脾氣不好，要討他歡心才好。\n",
                "口號"   : "萬年不老！永享仙福！壽與天齊！文武仁聖！\n",
        ]) );
        set("chat_chance", 3);
        set("chat_msg", ({
                "章老三説道：洪教主身通護佑，眾弟子勇氣百倍，以一當百，以百當萬。\n",
                "章老三説道：洪教主神目如電，燭照四方。\n",
                "章老三説道：我弟子殺敵護教，洪教主親加提拔，升任聖職。\n",
                "章老三説道：我教弟子護教而死，同升天堂。\n",
                "章老三高聲叫道：教主寶訓，時刻在心，建功克敵，無事不成！\n",
                "章老三忽然齊聲叫道：眾志齊心可成城，威震天下無比倫！\n",
                "章老三忽然齊聲叫道：神龍飛天齊仰望，教主聲威蓋八方！\n",
                "章老三忽然齊聲叫道：乘風破浪逞英豪，教主如同日月光！\n",
                "章老三齊聲叫道：教主永享仙福，壽與天齊！\n",
        }) );
        set("party/party_name", HIY"神龍教"NOR);
        set("party/rank", HIW"白龍門"NOR"教眾");
        set("party/level", 2);
        create_family("神龍教",2,"弟子");
        setup();
        carry_object(CLOTH_DIR"cloth")->wear();
        add_money("silver",5);
}

void init()
{
        add_action("do_join","join");
}

int recognize_apprentice(object ob)
{
        if( query("party/party_name", ob) == HIY"神龍教"NOR )
        {
                message_vision("$N搖了搖頭。\n",this_object());
                command("tell"+query("id", ob)+"你我素不相識，我憑什麼要教你呢？\n");
                return 0;
        }
        return 1;        
}

#include "/kungfu/class/shenlong/shenlong.h";
