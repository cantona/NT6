#include <ansi.h>
inherit ROOM;
string* npcs = ({
        __DIR__"npc/xiong",
        __DIR__"npc/he",
        __DIR__"npc/lu",
        __DIR__"npc/xie",
        __DIR__"npc/she",
});
void create()
{
        set("short", "飼養場");
        set("long",@LONG
這裡是藥王谷的飼養場，用于飼養一些可以取藥材的動物，你可以把動物
捉(zhuo)到屠宰場去殺了取藥。
LONG );
        set("exits", ([
                  "south" : __DIR__"syang",
        ]));
        set("objects", ([
        npcs[random(sizeof(npcs))] :random(2),
        npcs[random(sizeof(npcs))] :random(2),
        npcs[random(sizeof(npcs))] :random(2),
        npcs[random(sizeof(npcs))] :random(2),
        npcs[random(sizeof(npcs))] :random(2),
        ]) );
        setup();
}

void init()
{
        add_action("do_zhiliao", "zhuo");
}

int do_zhiliao(string arg)
{
        object me, ob;
          int lvl,exp,pot;
          exp=8+random(12);
          pot=2+random(6);
        me=this_player();
        lvl=me->query_skill("hunting");
        if( query("family/family_name", me) != "藥王谷"
         || lvl < 60 ) 
        {               return notify_fail("你還不會狩獵技巧呢！捉動物幹什麼？\n");
        }

        if( !arg || !objectp(ob = present(arg, environment(me))) )
                return notify_fail("指令格式：zhuo <ID> \n");

       if( query("owner", ob) == query("id", me) )
                   return notify_fail("你已經捉到"+ob->name()+"了！\n");

        if( query("owner", ob) && query("owner", ob) != query("id", me) )
                      return notify_fail(ob->name()+"已經是人家的了！\n");
        if( !query("yaowang_zhuo", ob) )
                return notify_fail("這個東西不能捉！\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙著呢！\n");
          if (random(lvl)>lvl*2/3)
        {       
        ob->set_leader(me);
        me->start_busy(2);
        message_vision("$N對$n召喚了兩聲，$n就乖乖得跟著$N。\n", me, ob);
                me->improve_skill("hunting",(query("int", me)/6));
                write(HIC "你在召喚過程中對于狩獵技巧有了些體會。\n" NOR);
                   set("owner",query("id",  me), ob);
                     addn("combat_exp", exp, me);
                     me->improve_potential(pot);
                     tell_object(me, HIC "你獲得了" + chinese_number(exp) + 
                             "點經驗和" + chinese_number(pot) + "點潛能。\n"NOR );
        }else 
        {       
        message_vision("$N對$n召喚了兩聲，$n根本就不理$N。\n", me, ob);
          me->start_busy(random(2));
        }

        return 1;
}
