// /d/xiakedao/shihole1.c 俠客島 石洞1

inherit ROOM;

int do_learn(string arg);
void create()
{
        set("short", "石洞");
        set("long", @LONG
這裡依次是六個石洞，各自通向四句詩的石室。後人研習「俠客
行」武功，悟出六句總綱，也分別刻在這裡。此洞一色青布帷幔，侍
立的弟子均是青衣長劍。正面壁上，粗隸刻著前四句詩的總綱「一劍
飛鴻」。
LONG );
        set("exits", ([
                "out"   : __DIR__"neiting",
                "enter" : __DIR__"shihole2",
                "north" : __DIR__"shiroom01",
                "south" : __DIR__"shiroom02",
                "east"  : __DIR__"shiroom03",
                "west"  : __DIR__"shiroom04",
        ]));
        set("objects", ([
                __DIR__"npc/wangwu": 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3090);
        set("coor/y", -25100);
        set("coor/z", 0);
        setup();
}
int valid_leave(object me, string dir)
{
        int i;
        object *inv;
        me = this_player();
        if(dir!="out")
        {
           if( query("score", me)<30000 )
           return notify_fail("你就這點江湖閱歷，回去歷練幾年再來吧！\n");
           if( query("weiwang", me) >= 20 )
           {
                inv = all_inventory(me);
                for(i=sizeof(inv)-1; i>=0; i--)
                   if( query("weapon_prop", inv[i]) && (query("equipped", inv[i]) == "wielded") )
                       if(objectp(present("wang", environment(me))) &&
                           living(present("wang", environment(me))))
                         return notify_fail("王五上前擋住你，朗聲說道：這位" +
                             RANK_D->query_respect(me) + "裡面是本島重地，不準比試武功。你可以進去，但不得手持兵刃。\n");
                return ::valid_leave(me, dir);
           }
           else
           {
                   if(objectp(present("wang wu", environment(me)))&&
                   living(present("wang", environment(me))))
                     return notify_fail("王五攔住你說道：裡面是本島重地，只有各派掌門及著名的俠客才能進去。\n" + RANK_D->query_rude(me) +"你還是回去吧。\n");
           }
        }
        return ::valid_leave(me, dir);
}