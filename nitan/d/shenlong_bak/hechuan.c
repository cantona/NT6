// Room: /d/shenlong/hechuan.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;

void create()
{
        set("short", "河船");
        set("long", @LONG
這是一艘裝飾華麗的河船，艙中佈置得尤如名門閨房。你走了其中
便是到了苗家一般，不油得暗暗驚訝不已。四周迷漫着奇異藥氣，你感
覺四肢發軟雙眼渾濁。
LONG
        );
        set("exits", ([
                "out" : "/d/forest/bank2",
        ]));
        set("objects", ([
                __DIR__"npc/lan" : 1,
        ]));
        set("outdoors", "shenlong");
        setup();
}

void init()
{
        object me = this_player();
        int lose, period, lvl;

        if( interactive(me = this_player()) )
        {
                if( lvl = me->query_skill("force", 1) > 149 ) return;

                write("糟糕！你中毒了！你一提氣便覺艱難。\n");
                lose = 140 - lvl;
                if( lose < 0 ) lose = 0;
                lose += 10;

                addn_temp("apply/damage", -lose, me);
                addn_temp("apply/attack", -lose, me);
                addn_temp("apply/dodge", -lose, me);

                period = 1000 / (5 + me->query_skill("force", 1));
                if( period < 1 ) period = 1;
                period += random(period);

                call_out("recover", period, me, lose);
        }
}
        
void recover(object me, int lose)
{
         addn_temp("apply/damage", lose, me);
         addn_temp("apply/attack", lose, me);
         addn_temp("apply/dodge", lose, me);
         write("你運功片刻，終於將餘毒逼出感到全身舒坦。\n");
}
