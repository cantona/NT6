//RJQJIGUAN.C

inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
這裏是一條祕道的盡頭，石牆之上嵌入兩盞油燈，火苗幽藍，向
北望去，黑暗中有些光亮。
LONG );
        set("exits", ([
                "north" : __DIR__"rjqmishi",
//                "down" : __DIR__"rjqmenlou1",
        ]));
//        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
//        replace_program(ROOM);
}

void init()
{
        object me;
        int q,d,eq;
        me=this_player();
        q=query("max_qi", me);
        d=(int)me->query_skill("dodge");
        if( (query("mingjiao", me) != 1) && (d <= 100) )
        {
                message_vision("$N只覺猶如利刃加身，噴血而出，渾身被射成刺蝟一般\n",me);
                eq=query("qi", me)-q+(q*d/100);
                set("qi", eq, me);
                set("eff_qi", eq, me);
        }
        if (eq<=0) me->die();
}
