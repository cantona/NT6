// yangfeng.h
#include <ansi.h>
int do_yang(string arg)
{
        object bee;
        object me,obj;
        int c,qufeng;

        me=this_player();
        seteuid(getuid());
        if(!arg)
                return notify_fail("你想養什麼？\n");
        if(arg != "yu bee" || arg != "yu bee")
                return notify_fail("你只能養玉蜂。\n");
        if( me->is_busy() || query_temp("marks/bee1", me) )
                return notify_fail("你正忙著呢。\n");
        if ( present("mi", me) )
                return notify_fail("你正拿著蜂蜜呢，還是先交給老頑童吧。\n");
//        bee=new("/d/baihuagu/npc/yubee");
//        bee->move(environment(this_player()));
//        me->set_leader(bee);
//        bee->set_leader(me);
        message_vision( HIY"$N打開一個蜂箱，裡面忽的飛出一群玉蜂。$N傻笑一聲，開始和蜜蜂玩耍。\n"NOR, me, obj);
        qufeng = me->query_skill("qufeng",1);
        c=20;
        if (wizardp(me)) c=3;
        else if (qufeng > 50 ) c = c * 50  / qufeng; // 200級就是 1/4
        me->apply_condition("yubee", c);
        set_temp("marks/bee1", 1, me);
        return 1;
}
int do_quit(string arg)
{
        write(query("name", this_player())+"，折騰個啥勁兒呀，專心養蜂吧！\n");
        return 1;
}