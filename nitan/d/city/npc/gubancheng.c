// npc: /d/city/npc/gubancheng.c
// Last Modified by Winder on Jul. 15 2000

#include <ansi.h>
inherit NPC;

void create()
{
        set_name( YEL "顧半城" NOR, ({"gu bancheng","gu","bancheng"}) );
        set("gender", "男性" );
        set("title", "顧家彩帛鋪老闆");
        set("age", 51);
        set("long", @LONG
顧老闆的生意很是紅火，店鋪裏全是人，看起來應該擴大店面了。有人
説是他的名字起得好，“半城”嘛，半個城的人都到他這裏來買布匹綢
緞，生意還能不好？不過，現在似乎他有把名字改成“全城”的打算。
LONG
        );
        set("chat_chance", 40);
        set("chat_msg", ({
                "顧老闆道：客官，看看這上好的湖綢吧！\n",
                "顧老闆道：揚州城是天下最繁華的地方啦，沒有啥這裏買不到的。\n",
                "顧老闆道：呵呵，小老兒這家店也就能餬口，您別聽他們瞎吹。\n",
                "顧老闆道：嗯，本府的程老爺，那真是愛民如子啊！\n",
        }));
        set("inquiry", ([
                "彩帛" : "您家要塊綢緞？隨便挑，隨便挑……\n",
                "here" : "這兒是揚州府，從這兒到東京和大理都很方便的。\n",
        ]) );
        set("attitude", "friendly");
        set("rank_info/respect", "老哥");
        set("rank_info/rude","老王八蛋");
        set("combat_exp",100);
        set_skill("unarmed", 5);
        setup();
        carry_object( "/clone/cloth/male-cloth")->wear();
}

void init()
{
        object ob = this_player();
        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        message_vision("顧老闆忙着給客人量布，一回頭，見有人進來，招呼一聲：“您稍等！”\n",ob);
        return;
}