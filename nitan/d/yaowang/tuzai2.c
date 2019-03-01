#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "屠宰場");
        set("long", @LONG
這裡是藥王谷的屠宰場，是專門用來屠宰藥王谷飼養的動物，
取藥材用的，你可以把動物捉到這裡，進行屠宰(sha)。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"tuzai1",
        ]));
        setup();
}

void init()
{
        add_action("do_sha", "sha");
}

int do_sha(string arg)
{
        object me, ob;
        int exp,pot;
        exp=8+random(12);
        pot=2+random(2);
        me=this_player();

        if( query("family/family_name", me) != "藥王谷" || me->query_skill("medical",1)<60 )
        {
                return notify_fail("你還不會取藥呢！不會殺動物？\n");
        }

        if( !arg || !objectp(ob = present(arg, environment(me))) )
                return notify_fail("指令格式：sha <ID> \n");

        if( !query("yaowang_zhuo", ob) )
                return notify_fail("這個東西不能在這裡殺！\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙著呢！\n");

        if(random(3))
        {
              message_vision(HIR"$N把$n按在屠宰槽上，一刀砍了下去。\n"NOR, me, ob);
              message_vision(HIR"結果刀從$n身上滑了下來，$N差點傷了自己。\n"NOR, me, ob);
                 me->start_busy(1+random(2));
              return 1;
            }
        me->improve_skill("medical", ((int)me->query_skill("healing",1)/10));
        message_vision(HIR"$N把$n按在屠宰槽上，一刀砍了下去。\n"NOR, me, ob);
        ob->die();
        addn("combat_exp", exp, me);
        me->improve_potential(pot);
      tell_object(me,HIC "在屠宰過程中你對「基本醫術」有了新的認識！\n" NOR);
              tell_object(me, HIC "你獲得了" + chinese_number(exp) + 
                      "點經驗和" + chinese_number(pot) + "點潛能。\n"NOR ); 
         me->start_busy(2);
        return 1;
}
