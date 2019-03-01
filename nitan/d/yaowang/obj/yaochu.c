#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_wayao", "dig");
}

void create()
{
        set_name("藥鋤", ({"yao chu", "chu"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("no_drop","不要亂丟，這東西打到人會痛的！\n");
                set("no_put",1);
                set("long", "這是一把很重的藥鋤，你可以用它來挖藥（dig yao）。\n");
                set("value", 5000);
        }
        setup();
}

int do_wayao(string arg)
{       object ob;
        object me=this_player();
        if( me->is_busy() || query_temp("pending/exercising", me))return notify_fail("你現在正忙著呢。\n");
        if (!arg||arg!="yao") return notify_fail("你要挖什麼呢？！\n");
        if( (query("jing", me)<20))return notify_fail("你的精力不能集中，挖了也是白挖！\n");
        if( query("qi", me)<40)return notify_fail("你太累了，怎麼都拿不動這把藥鋤！\n");
        if (present("zhengui yaocai", environment(this_object()))||present("putong yaocai",environment(this_object()))) return notify_fail("別不知足,你已經挖到藥了！\n");
        if(environment(this_object()) != me)  return notify_fail("你是在看別人挖吧？\n");
        if( query_temp("wayao1", environment(me)) )
        {
        me->start_busy(random(3)+1);
        message_vision("$N揮動藥鋤“呼哧、呼哧”地在地上挖了起來,似乎在找什麼東西。\n",me);
        addn("jing", -10, me);
        addn("qi", -20, me);
        if(random(7)<3)
        {
        message_vision(YEL"$N挖了半天，終于把那顆藥材小心翼翼地掘了出來。\n"NOR,me);
        new(__DIR__"obj/yaocai")->move(me);
        addn_temp("wayao1", -1, environment(me));
        destruct(this_object());
        me->start_busy(1);
        }
      return 1;
   }
      else
        if( query_temp("wayao2", environment(me)) )
        {
        me->start_busy(1+random(4));
        message_vision(CYN"$N揮動藥鋤開始在地上挖了起來。\n"NOR,me);
        addn("kee", -20, me);
        addn("sen", -30, me);
             if(random(7)<4)
      {
        message_vision(YEL"$N挖了半天，終于把那顆藥材小心翼翼地掘了出來。\n"NOR,me);
//        new(__DIR__"obj/yaocai")->move(me);
        addn_temp("wayao2", -1, environment(me));
        destruct(this_object());
        me->start_busy(1);
      }
        return 1;
    }
      return notify_fail("這裡什麼都沒有,原來是你看花了眼。\n");
}