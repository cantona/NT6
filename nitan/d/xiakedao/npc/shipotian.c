// shipotian.c
#include <ansi.h>
inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;
int ask_weiwang();

void create()
{
        set_name("石破天", ({"shi potian", "shi","potian"}));
        set("title", "長樂幫幫主");
        set("gender", "男性");
        set("age", 20);
        set("long", "他大約二十多歲，穿着一身破爛的衣服，卻也擋不住他一身的英氣。\n");

        set("attitude", "peaceful");

        set("str", 25);
        set("int", 35);
        set("con", 25);
        set("dex", 25);

        set("qi", 2000);
        set("max_qi", 2000);
        set("jing", 1000);
        set("max_jing", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 100);

        set("combat_exp", 1000000);
        set("score", 30000);

        set_skill("force", 100);                 // 基本內功
        set_skill("huntian-qigong", 150);        // 混天氣功
        set_skill("unarmed", 100);               // 基本拳腳
        set_skill("xianglong-zhang", 150);       // 降龍十八掌
        set_skill("dodge", 100);                 // 基本躲閃
        set_skill("xiaoyaoyou", 150);            // 逍遙遊
        set_skill("parry", 100);                 // 基本招架
        set_skill("begging", 50);               // 叫化絕活
        set_skill("checking", 50);              // 道聽途説

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "xianglong-zhang");
        map_skill("dodge", "xiaoyaoyou");
        map_skill("parry", "xianglong-zhang");
        set("chat_chance", 8);
        set("chat_msg", ({
        "石破天説道: 我來俠客島這麼多天了，也不知道阿繡和婆婆現在怎麼樣了。\n",
        "石破天説: 江湖威望很重要，威望高大有好處啊。\n",
        "石破天突然説道: 不行，我不放心阿繡，我要去看看她。\n",
        "石破天突然説道: 矣！我的體內怎麼好像有一羣蝌蚪在動呢。\n",
        "石破天説道: 你能給我玄冰碧火酒嗎? \n",
        }));
        set("inquiry", ([
                "臘八粥" :  "\n你去問龍島主，試試你的運氣吧。\n",
                "石中玉" :  "\n他是我的兄弟，他現在在摩天崖。\n",
                "阿繡" :  "\n呀！你見過她嗎?她還好吧。\n",
                "玄冰碧火酒" : "\n嘻嘻！多在俠客島轉轉吧。\n",
                "賞善罰惡令" : "\n你可以用它來要臘八粥。\n",
                "威望" :  (: ask_weiwang :),
                "江湖威望" : (: ask_weiwang :),
        ]) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

int ask_weiwang()
{
        command("tell"+query("id", this_player())+"你現在的江湖威望是"+(query("weiwang", this_player())));
        say("\n石破天説：如果你威望值很高，有些人見了你不但不會殺你，還會教你武功，送你寶貝。\n"
                +"而且你還可以加入幫會，率領會眾去攻打目標，就連去錢莊取錢也會有利息 。。。。。\n");
        say("\n石破天又説：殺某些壞人或救某些好人可以提高江湖威望。\n");
        return 1;
}

int recognize_apprentice(object ob)
{
        if( query("weiwang", ob)<50 )
        {
                message_vision("$N搖了搖頭。\n",this_object());
                command("tell"+query("id", ob)+"你的身份太低，我不能教你。\n");
                return 0;
        }
        return 1;
}

void init()
{
        ::init();
        add_action("do_skills","skills");
        add_action("do_skills","cha");

}

int do_skills(string arg)
{
        object ob ;
        ob = this_player () ;
        if(wizardp(ob))
                return 0;
        if( query("weiwang", ob)<50 )
        {
                message_vision("$N搖了搖頭。\n",this_object());
                command("tell"+query("id", ob)+"你怎麼能看我的武功呢。\n");
                return 1;
        }
        command("tell"+query("id", ob)+"我所有的武功如下：\n"+
"  叫化絕活 (begging)                       - 出類拔萃  50/   \n"+
"  道聽途説 (checking)                      - 出類拔萃  50/   \n"+
"  基本輕功 (dodge)                         - 一代宗師  100/   \n"+
"  基本內功 (force)                         - 一代宗師  100/   \n"+
"□混天氣功 (huntian-qigong)                - 一代宗師  150/   \n"+
"  基本招架 (parry)                         - 登峯造極  100/   \n"+
"  基本拳腳 (unarmed)                       - 一代宗師  100/   \n"+
"□降龍十八掌 (xianglong-zhang)             - 登峯造極  150/   \n"+
"□逍遙遊 (xiaoyaoyou)                      - 一代宗師  150/   \n");
        return 1;
}

int accept_object(object who, object ob)
{
        object obn;
        if( !who || environment(who) != environment() )
                return 0;
        if( !objectp(ob) )
                return 0;
        if( !present(ob,who) )
                return notify_fail("你沒有這樣東西。\n");

        if( query("id", ob) == "xuanbing jiu" )
        {
                remove_call_out("destroy");
                call_out("destroy", 1, who, ob);

                message_vision( "\n石破天激動的説：這位大哥，我該怎麼謝你呢。\n",who);
                obn = new("/d/xiakedao/obj/xuantie");
                obn->move(who);
                return 1;
        }
}

void destroy(object me, object ob)
{
        destruct(ob);
        return;
}
