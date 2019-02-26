// /yubifeng/shimen.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "石門");
        set("long", @LONG
洞穴愈來愈窄，須得弓身而行方能通過，洞中到處是千年不化的尖
冰，有些處所的冰條如刀劍般鋒鋭突出。有時頭頂撞上了堅冰尖角，隱
隱生疼。通道盡頭，只見一塊圓形巨巖疊在另一塊圓巖上，兩塊巨巖封
住了去路，儼然一座石門。兩巖(yan)之間都是堅冰(bing)凝結。
LONG );
        set("exits", ([
                "south" : __DIR__"tongdao2",
        ]));
        set("objects", ([
                __DIR__"npc/huyidao" : 1,
                __DIR__"npc/hu-wife" : 1,
        ]));
        set("item_desc", ([
                "yan"  : "這是兩塊封閉通道的巨巖。\n",
                "bing" : "凍結巨巖的冰層，晶瑩剔透，看來不是一時一日而成。\n",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 6110);
        set("coor/y", 5130);
        set("coor/z", 0);
        setup();
}

void init()
{
        add_action("do_push", "tui");
        add_action("do_push", "push");
        add_action("do_burn", "use");
        add_action("do_burn", "burn");
        add_action("do_burn", "shao");
}

int do_burn(string arg)
{
        object ob, me = this_player();

        if( !arg || arg=="" ) return 0;
        if (!present("fire", me)) return 0;
        if (!objectp(ob = present("mu chai", me))) return 0;
        if( arg=="yan" )
        {
                message_vision("$N點起木柴，去燒二巖之間的堅冰。\n火焰越燒越大，冰化為水，只聽得叮釘之聲不絕，一塊塊碎冰落在地下。\n", me);
                destruct(ob);
                if( query("neili", me)>1000 )
                {
                        message_vision("眼見二巖之間的堅冰已融去大半，$N發力推擠，那巨巖幌了幾幌，竟慢慢轉將過去，露出一道空隙，宛似個天造地設的石門一般。\n", me);
                        set("exits", ([
                                "enter" : __DIR__"baozang",
                                "south" : __DIR__"tongdao2",
                        ]));
                }
                else
                {
                        message_vision("$N雙手在巨巖上運力一推，那巖石毫不動彈。\n", me);
                }
        }
        else
        {
                write("你要在這個冰窟窿裏點火幹什麼？\n");
        }
        return 1;
}

int do_push(string arg)
{
        object me = this_player();

        if (!arg || arg !="yan")
        {
                message_vision("這裏地方這麼小，推什麼呀！\n", me);
                return 1;
        }
        else
        {
                message_vision("$N伸手抵在巨巖上，運足內力就是這麼一推，結果紋絲不動。\n", me);
                return 1;
        }
}
