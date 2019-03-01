//lianparry.c                唐門練武場

inherit ROOM;

void init();
int do_lian(string);

void create ()
{
        set ("short", "練武場");
        set ("long", @LONG
這是一個寬敞的練武場。你的面前是百十個設計精巧的機關木頭
人，它們被擺放成一個八卦陣，只要有人走進陣中它們就會自動攻擊
不時的有人被打出陣來，這裡可以練練(jin)基本的招架功夫。
LONG);
        set("exits", ([
                "west" : __DIR__"nzlange3",
        ]));
        set("outdoors", "tangmen");
        setup();
}

void init()
{
        add_action("do_lian", "jin");
}

int do_lian(string arg)
{
        object me;
        int jingli_cost;
        int qi_cost;

        me = this_player();

        if ( !arg || ( arg != "zhen" ) )
                return notify_fail("你想幹什麼？\n");

        jingli_cost = (-1) * (5 + random(15));
        qi_cost = (-1) * (1 + random(5));

        if( query("qi", me) <= (-qi_cost) )
                return notify_fail("你太虛弱了，再練就要出人命了。\n");

        if( query("jingli", me) <= (-jingli_cost) )
                return notify_fail("你太疲勞了，沒有精力練功了。\n");

        if ( (int)me->query_skill("parry", 1) < 51 )  
        {
                write("你運氣于周身上下，小心翼翼的走進木人陣中，不一會兒就被打的鼻青臉腫！\n可是你對基本招架有了一點了解。\n");
                addn("jingli", jingli_cost, me);
                addn("qi", qi_cost, me);
                me->improve_skill("parry",(15+random(query("int", me)/2)));
        }
        else
                if ( (int)me->query_skill("parry", 1) < 101 )  
                {
                write("你運氣于四肢，邁步走進木人陣中，不斷擋開木人的襲擊！\n你對基本招架有了一些認識。\n");
                        addn("jingli", jingli_cost, me);
                        addn("qi", qi_cost, me);
                        me->improve_skill("parry",(20+random(query("int", me)/2)));
                }
                else
                        write("你甩手走進木人陣中，竟沒有一個木人能夠打中你的身體！\n你在這裡已經學不到什麼了！\n");
        return 1;
}