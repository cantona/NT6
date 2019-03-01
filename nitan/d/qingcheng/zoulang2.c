// Room: /qingcheng/zoulang2.c
// Date: Aug. 10 1998 by Winder

inherit ROOM;
void create()
{
        set("short", "鬆風東廊");
        set("long", @LONG
這裡是鬆風觀中連貫操練場和東廂的走廊，鬆風觀高矗山頂，從走
廊望去，青山鳥寂，幽谷風生，漫天薄霧時時彌散在長林翠竹之間。自
古號稱：“青城天下幽”，不妨在此體味。這裡的南邊是書房，北邊是
兵器室，東邊一直關著門的是本派的庫房。
LONG );
        set("outdoors", "qingcheng");
        set("exits", ([
                "west"  : __DIR__"caochang",
                "south" : __DIR__"shufang",
                "north" : __DIR__"bingqishi",
        ]));
        set("objects", ([
                __DIR__"npc/hong" : 1,
        ]));
        set("coor/x", -8070);
        set("coor/y", -840);
        set("coor/z", 90);
        setup();
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if((!myfam || myfam["family_name"] != "青城派") && dir != "west" &&
                objectp(present("hong renxiong", environment(me))))
        return notify_fail("洪人雄攔住你說：此處乃本派禁地，請止步。\n");

        if( me->query_skill("qingming-xuangong", 1) < 10 && dir != "west" &&
                objectp(present("hong renxiong", environment(me))))
        return notify_fail("洪人雄攔住你：師父交代，內功未臻小成不得入內。\n");

        return ::valid_leave(me, dir);
}

void init()
{
        add_action("do_open", "open");
        add_action("do_open", "unlock");
}

void close_gate()
{
        object room;

        if(!( room = find_object(__DIR__"kufang")) )
                room = load_object(__DIR__"kufang");
        if(objectp(room))
        {
                delete("exits/east");
                message("vision","只聽乒地一聲，庫門自動關了起來。\n",this_object());
                message("vision","你腦海中閃過一個念頭：哎喲！又進不去了！\n", this_object());
                delete("exits/west", room);
                message("vision","只聽乒地一聲，庫門自動關了起來。\n",room);
                message("vision","你腦海中閃過一個念頭：壞了！出不去了！\n" , room);
        }
}

int do_open(string arg)
{
        object room;
        object ob;

        if (query("exits/east"))
                return notify_fail("庫門已經是開著了。\n");

        if (!arg || (arg != "men" && arg != "east" && arg != "door"))
                return notify_fail("你要開什麼？\n");
        if (!(ob = present("qingcheng key", this_player())))
                return notify_fail("你不會撬鎖。\n");
        message_vision("$N用一把鑰匙打開了庫門。結果用力過猛，把鑰匙拗斷了。\n", this_player());

        if(!( room = find_object(__DIR__"kufang")) )
                room = load_object(__DIR__"kufang");
        if(objectp(room))
        {
                set("exits/east", __DIR__"kufang");
                message_vision("$N使勁把庫門推了開來。\n",this_player());
                set("exits/west", __FILE__, room);
                message("vision","外面有人把庫門推開了。\n",room);
                remove_call_out("close_gate");
                call_out("close_gate", 10);
        }

        return 1;
}