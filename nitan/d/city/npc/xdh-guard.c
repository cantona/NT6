//xdh_guard.c

inherit NPC;

#include <ansi.h>

int ask_xdh(object me, object ob);
void create()
{
        set_name("守衛",({"shou wei","guard"}) );
        set("long","這是一個年輕人，長的流裡流氣的。\n");
        set("title","小刀會幫眾");
        set("gender","男性");
        set("age",20);
        set("combat_exp",100);
        set("inquiry",([
                "小刀會" : (: ask_xdh :),
        ]) );
        setup();
}

int ask_xdh(object me, object ob)
{
        
        me=this_player();
        ob=this_object();
        if( query("bunch/bunch_name", me) != "小刀會" )
        {
                command("grin");
                tell_object(me,"小刀會守衛說：“是想投奔咱們小刀會吧？那就得守規矩。”\n");
                tell_object(me,HIB"小刀會守衛用黑布蒙上你的眼睛，帶著你七走八走，最後好象到了一
間屋子裡面。\n你蒙著的黑布也被人取了下來。\n"NOR);
                tell_room("$N被帶了進來。\n",me);
                me->move("/d/city/xdhzb");
                return 1;
        }
        if (good_bunch(me))
        {
                command("say 我們小刀會不歡迎你這種自命正派的人！請回吧。\n");
                return 1;
        }
        
        tell_object(me,"小刀會守衛奇怪道：“同為本幫兄弟，你何出此言啊？”\n");
        return 1;
}

        