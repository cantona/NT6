//HSQTAN3.C

inherit ROOM;

void create()
{
        set("short", "深潭");
        set("long", @LONG
這裡是瀑布下的寒潭，水中幽暗無比，四周似乎有幾處出口，但
實在看不清是通向何處。水中冰冷刺骨，令人難以忍受，你只覺得氣
力在一點一點消失。
LONG );
        set("exits", ([
                "east" : __DIR__"hsqtan3",
                "west" : __DIR__"hsqtan2",
                "south" :__DIR__"hsqtan4",
                "north" :__DIR__"hsqtan3",
        ]));
        set("no_clean_up", 0);
        setup();
}

void init()
{
        object me;
        int meqi,meneili,decqi,mq;
        me=this_player();
        meqi=query("qi", me);
        meneili=query("neili", me);
        mq=query("max_qi", me);
        decqi=(int)(mq/(random(4)+5+meneili/200));
        meqi=meqi-decqi;
        set("neili", 0, me);
        if( meqi>0)set("qi", meqi, me);
        else me->die();
}
