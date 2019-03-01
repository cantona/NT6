// NPC jiuyi.c

#include <ansi.h>

inherit NPC;
string ask_me();

void create()
{
        set_name("烏老大", ({ "wu laoda", "wu"}));
        set("long",@LONG
他就是名動江湖的烏老大，
由於謀反童姥未遂而被囚禁於此。
LONG        
           );
        set("gender", "男性");
        set("age", 40);
        set("shen_type",-1);
        set("attitude", "peaceful");

        set("str", 27);
        set("int", 23);
        set("con", 24);
        set("dex", 30);

        
        set("max_qi", 1000);
        set("qi", 1000);
        set("jing", 500);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 0);

        set("combat_exp", 100000);
        set("score", 2000);

        set("inquiry", ([
                "白雲熊膽丸" : (: ask_me :),
        ]));
        set("chat_chance", 3);
        set("chat_msg", ({
"烏老大喃喃道：白雲熊膽丸可真是好東西！\n",
        }) );
        set("wan_count", 1);
        setup();
}

string ask_me()
{
        mapping fam; 
        object ob;
        
        if( !(fam=query("family", this_player())) || fam["family_name"] != "靈鷲宮" )
                return RANK_D->query_respect(this_player()) + 
                "你怎敢要靈鷲宮之鎮派寶物呢？";

        if (query("wan_count") < 1)
                return "不好意思，已經有人捷足先登了，你下次再來吧。";

        addn("wan_count", -1);
        ob = new("/d/lingjiu/npc/obj/baiyunwan");
        ob->move(this_player());
        return "唉，看在你捨身救我的份上，這顆白雲熊膽丸就給你吧。";
}
