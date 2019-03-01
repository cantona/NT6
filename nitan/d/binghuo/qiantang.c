// Room: /binghuo/qiantang.c
// Date: Oct.28 1999 by Winder
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "錢塘江畔");
        set("long", @LONG
錢塘江到了六和塔下轉一個大彎，然後直向東流。該處和府城相
距不近，塔東三株大柳樹下系著一艘扁舟(zhou)。江船張有風帆，船
頭掛著兩盞碧紗燈籠。碧紗燈下，一個少女獨坐船頭，身穿淡綠衫子。
LONG );
        set("outdoors", "wangpan");
        set("no_clean_up", 0);
        set("item_desc", ([
                "zhou" : "一艘小舟，不妨進去(enter)看看。\n",
        ]));
        set("exits", ([
                "westup" : "/d/hangzhou/qiantang",
        ]));
        set("coor/x", 4080);
        set("coor/y", -1800);
        set("coor/z", -10);
        setup();
}

int do_enter(string arg)
{
        object me;
        mapping fam;

        me = this_player();
        if( !arg || arg=="" ) return 0;
        if( arg=="zhou" )
        {
               message("vision",
                        me->name() + "運起輕功，一縱身上了小舟。",
                        environment(me), ({me}) );
               me->move(__DIR__"zhou");
               message("vision",
                        me->name() + "從岸上躍上舟來。\n",
                        environment(me), ({me}) );
                        return 1;
        }
        else  return notify_fail("你想到哪去？\n");
}

void init()
{
        object me, dao, room, bai, ding;

        me = this_player();
        add_action("do_enter", "enter");
        room = get_object("/d/binghuo/wangpangu2");
        ding = present("chang jinpeng", room);

        if (objectp(ding)) 
                dao = present("tulong blade", ding);
        if (! dao)
        {
                ding = present("ding", room);
                if (objectp(ding)) 
                dao = present("tulong blade", ding);
        }

        if (objectp(dao))
        {
                room = get_object("/d/binghuo/wangpanshan");
                bai = present("bai guishou",room);
                if (objectp(bai)) tell_object(me, HIC "\n只見岸邊上泊滿了海船，所有的海船全部標記著天鷹教的標志。\n" NOR);

                if (objectp(bai)
                    && !query_temp("broadcast", bai )
                    && query("combat_exp", me)>1000000
                    && query("weiwang", me)>100000 )
                {
                        message("vision", HIR"\n【倚天屠龍】" NOR+WHT "白龜壽仰天一聲長笑。\n" NOR, all_interactive());
                        message("vision", HIR"\n【倚天屠龍】" NOR+WHT "白龜壽：我天鷹教得到屠龍寶刀，"
                                          WHT"今在王盤山島舉行揚刀立威大會。\n" NOR, all_interactive());
                        set_temp("broadcast", 1, bai);
                }
        }
}
