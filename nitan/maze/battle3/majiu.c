inherit ROOM;

void create()
{
        set("short", "御馬監");
        set("long", @LONG
這裡是汴樑城皇宮內的御馬監，飼養著各地進貢來的名馬，幾個
太監在忙著給馬梳洗，清理草料。
LONG );
        set("indo0rs", "city2");
        set("no_fly",1);

        set("exits", ([
                "east" : __DIR__"hgdadao6",
        ]));

        set("objects", ([
                __DIR__"npc/zyma" :    1,
        ]));
                       
        setup();
}       

void init()
{
        object me = this_player();
        object ma;
        if (interactive(me) && me == WAR_D->query_marshal())
        {
                if (! objectp(ma = present("shizi ma", me))
                &&  ! objectp(ma = present("shizi ma", environment(me))))
                {
                        ma = new("/maze/battle3/npc/zyma");
                        ma->move(environment(me));
                }
        }
}
