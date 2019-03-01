//Room: /d/dali/hongsheng3.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","宏聖寺塔");
        set("long", @LONG
這裡是宏聖寺塔內部，四面牆壁上都辟有佛龕，龕內置佛像。抬
頭上望，可以看到中心柱、葫蘆頂、傘蓋、相輪及蓮花座托等。傘蓋
成八角形，角上掛有風鐸。
LONG );
        set("exits",([ /* sizeof() == 1 */
            "down"   : "/d/dali/hongsheng2",
            "up"     : "/d/dali/hongsheng4",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -19151);
	set("coor/y", -6821);
	set("coor/z", 39);
	setup();
}


int valid_leave(object me, string dir)
{
        int c_exp;
        int c_skill;
        me = this_player();
        if (!me) return 1;
        if (dir == "up" )
        {
                c_exp=query("combat_exp", me);
                c_skill = (int)me->query_skill("dodge",1);
                if( query("qi", me)>20 )
                {
                        me->receive_damage("qi", 20);
                        if (c_skill*c_skill*c_skill/10 < c_exp && c_skill<101)
                                me->improve_skill("dodge", (int)me->query_skill("dodge", 1) / 5);
                        tell_object(me,"你爬上一層樓，有些累了。\n");
                } else
                {
                        set("qi", 0, me);
                        tell_object(me,"你是在爬不動了。\n");
                        return 0;
                }
        }
        return 1;
}