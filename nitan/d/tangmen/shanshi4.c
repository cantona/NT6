//shanshi6


#include <ansi.h>
inherit ROOM;

int do_qiao(string arg);

void create ()
{
        set ("short", "山道");
        set ("long", @LONG
這裡是後山一條昏暗的山道。山道的兩旁已不象剛才那麼樹木繁
茂，反而是光禿禿的沒有一棵植物，這裡的山石竟發出深深的赤紅色
光澤，不知與處別的石頭有什麼不同，空氣中飄這一股腥臊的氣味，
可能有毒物潛伏在附近，離開這裡吧。
LONG);
        set("area","tangmen");
        set("outdoors", "tangmen");
        set("exits", ([
                "northup" : __DIR__"shanshi3",
                "southwest" : __DIR__"shanshi5",
        ]));
        set("shi", 5);
        setup();
}

void init()
{
        add_action("do_qiao","knock");
}

int do_qiao(string arg)
{
        object me, enemy;
       object weapon;
        int jingli_cost;

        me = this_player();
        weapon=query_temp("weapon", me);
        jingli_cost = (-1) * (10 + random(15));

        if ( !arg || ( arg != "shi" ) )
                return notify_fail("你想幹什麼？\n");

        if( !(query_temp("biao", me)) )
                        return notify_fail("你沒事做嗎？亂敲什麼呀！\n");
        if( !weapon || (query("id", weapon) != "hammer") )
                return notify_fail("你手上沒有鐵錘，難道用手？\n");
        if( query_temp("find", me) )
                return notify_fail("你已經找到一塊精鐵礦石了，沒有力氣再帶一塊！\n");

        if( query("jingli", me) <= (-jingli_cost) )
                return notify_fail("你太疲勞了，沒有精力再繼續敲鑿了。\n");

        if ( (int)query("shi") >= 1 )
        {
                message_vision(YEL"$N揚起手中的鐵錘重重的砸在道旁的山石上。\n"NOR, me);
                if( random(1+query("kar", me)-10) >= 3 )
                {
                        message_vision(HIG"$N聽到山石發出清脆的碎裂聲，終于給你敲下來了一大塊！\n$N低頭剛要抱起礦石，突然一只毒蠍從石後爬了出來！\n"NOR, me);
                        enemy = new(__DIR__"npc/xiezi");
                        enemy->move(this_object());
                        new(__DIR__"obj/kuangshi")->move(this_object());
                        enemy->kill_ob(me);
                        me->fight_ob(enemy);
                        set_temp("find", 1, me);
                }

                addn("jingli", jingli_cost, me);
                addn("shi",-1);
        }
        else
                return notify_fail("山道邊的山石都被砸碎了，沒有可以用的了。\n");

        return 1;
}

int valid_leave(object me, string dir)
{
        object ob;
        int true;
        if ( objectp( present("duxie", environment(me))) )
        {
                ob = present("duxie", environment(me));
                true = 1;
        }
        else 
                true = 0;
        if ( ( (dir == "southeast") || (dir == "northup") ) && objectp( present("kuang shi", me))  && true && living(ob))
                return notify_fail("毒蠍擋住了你離開的道路，看來只有殺了它才能走了！\n");
        else
                return ::valid_leave(me, dir);
}