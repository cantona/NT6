#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "正廳");
        set("long", @LONG
這裏是回春堂的正廳，寬敞的房間內放着幾張桌椅，每天都有藥王谷
的醫師在這裏坐堂，為人看病療傷。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"tingyuan",
        ]));

        set("objects", ([
                __DIR__"npc/yishi" : 1,
        ]));
        setup();
}

void init()
{
        add_action("do_zhiliao", "zhiliao"); //療傷
}

int do_zhiliao(string arg)
{
        object me, ob;
        int i, obj;
        me=this_player();
        i=( 100 - (int)me->query_skill("medical",1) );

        if( query("family/family_name", me) != "藥王谷" )
        {               
                return notify_fail("你不能在這裏給人療傷！\n");
        }

        if( !arg )
                return notify_fail("指令格式：zhiliao <ID> \n");

        if(!objectp(ob = present(arg, environment(me))))
                return notify_fail("這裏沒有這個人！\n");

        if( me->is_fighting() || me->is_busy() )
                return notify_fail("你正忙着呢！\n");

        if( ob->is_fighting() || ob->is_busy() )
                return notify_fail("他正忙着呢！\n");

        if( me==ob )
                return notify_fail("你不需要在這裏給自己療傷！\n");

        obj=(query("max_qi", ob)-query("eff_qi", ob));

        if( !query_temp("heal", ob)){
        message_vision ("$N得先交診金"+MONEY_D->price_str(obj*10)+"給唐訛化。\n", ob);
                return 1;
        }

        if( i<5 ) i=5;
        if( i>40 ) i=40;
        if( query("jingli", me) <= i )
                return notify_fail("你太累了，先休息一下吧！\n");

        message_vision ("$N為$n把了把脈，拿出一根銀針在$n穴位上紮了幾下。\n", me, ob);
        message_vision(WHT"$N吐出一口淤血，臉色看起來好多了。\n"NOR, ob);

        delete_temp("heal", ob);
        set("eff_qi",query("max_qi",  ob), ob);
        set("qi",query("max_qi",  ob), ob);
        me->improve_skill("medical", ((int)me->query_skill("medical",1)/2));
        addn("jingli", -i, me);
        me->start_busy(3);
        ob->start_busy(3);

        return 1;
}
