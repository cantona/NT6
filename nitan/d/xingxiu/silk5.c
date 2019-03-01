// /d/xingxiu/silk4.c
// Last Modified by winder on Feb. 28 2001

inherit ROOM;

void create()
{
        set("short", "絲綢之路");
        set("long", @LONG
這是一條中原和西域之間的商道。西面是一望無際的大沙漠，傳說
那裡常有盜匪出沒。西北則通向一片連綿的山脈，東面就是通向中原的
路。路邊有一塊石碑(shibei)。
LONG );
        set("outdoors", "xiyu");
        set("exits", ([
                "southeast" : __DIR__"tugu",
                "west"      : __DIR__"shamo1",
                "northwest" : __DIR__"shanjiao",
                "southwest" : "/d/xueshan/caoyuan" ,
        ]));
        set("objects", ([
                __DIR__"npc/trader" : 1,
        ]));
        set("item_desc", ([
                "shibei" : "北至西域，東達中原。誰若西行，格殺勿論。白駝山主人啟。\n",
        ]));
        set("coor/x", -24000);
        set("coor/y", 1000);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_push", "push");
        add_action("do_push", "tui");
}

int valid_leave(object me, string dir)
{
        object ob;

        if ((dir == "west")&& !userp(me)) return 0;
        return ::valid_leave(me, dir);
        if( query_temp("wait_target", me) && 
                objectp(present("anran zi", environment(me))))
                return notify_fail("黯然子閃身攔在你面前，喝道：臨陣想溜？給我滾回來！\n");
        if( query_temp("xx_rob", me) && 
                objectp(ob = present("hubiao biaoshi", environment(me))) &&
                query("target", ob) == me )
                return notify_fail("護鏢鏢師閃身攔住你的去路，看來是想把你給廢了！\n");  
        if( query_temp("xx_rob", me) && objectp(present("shangdui",environment(me))) )
                return notify_fail("商隊在這裡呢，快搶(qiang)啊！\n");  
        return ::valid_leave(me, dir);
}

int do_push(string arg)
{
        object me = this_player();
        mapping fam;

        if( !arg || arg=="" ) return 0;
        if( arg=="shibei" )
        {
                if( (fam=query("family", me)) && fam["family_name"] == "丐幫" )
                {
                        message_vision("$N推開石碑，只見泥沙紛紛跌落，地面上露出一個小洞。\n", me);
                        message("vision", me->name() + "運起丐幫縮骨功，一彎腰往洞裡鑽了進去。\n", environment(me), ({me}) );
                        me->move("/d/gaibang/underxx");
                        message("vision", me->name() + "從洞裡走了進來。\n", environment(me), ({me}) );
                        return 1;
                }
                else return notify_fail("這麼小的洞，你鑽得進去嗎？\n");
        }
}        
