// he.c

#include <ansi.h>

inherit NPC;

mixed ask_back();

void create()
{
        set_name("何員外", ({ "he yuanwai", "he" }));
        set("shen_type", -1);

        set("gender", "男性" );
        set("age", 53);
        set("long", "何員外是揚州城裡的首富，和當地的官紳都有很深的交情。據說他還和桃花島有些關系。\n");
        set("combat_exp", 400);
        set("attitude", "friendly");
        set("inquiry", ([
                "桃花盛開" : (: ask_back :),
        ]));
        setup();

        carry_object(__DIR__"obj/choucloth")->wear();
}

/*
void init()
{
        object ob;
        mapping myfam;
        ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
*/

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        say("何員外奇怪地對你說道：“你這人怎麼隨隨便便地就跑到我的園子裡來？”\n");
}

mixed ask_back()
{
        object me;

        me = this_player();
        if( query("family/family_name", me) != "桃花島" )
        {
                message_vision("$N自顧自的幹活，好象沒有聽見$n在說什麼。\n",
                               this_object(), me);
                return -1;
        }

        message_sort("$N猛然抬起頭來，上上下下打量了一會"
                     "兒$n，眼角微微一動，立刻放下手中的"
                     "活計，從內室領出一只白雕，說道：你"
                     "乘坐這只白雕回桃花島吧。\n",
                     this_object(), me);

        tell_object(me, HIW "你坐上白雕飛了很久，越過大海，忽然眼前一亮，"
                    "你已經來到了桃花島。\n" NOR);
        me->move("/d/taohua/jingshe");
        return -1;
}