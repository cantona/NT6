// bingqifang.c 兵器房

inherit ROOM;

void create()
{
        set("short", "兵器房");
        set("long", @LONG
這裡是華山派的兵器房，四周放這幾個兵器架，上面是華山派各
弟子平時練劍用的竹劍。
LONG );
        set("exits", ([
                "west" : __DIR__"square",
        ]));
        set("objects", ([ 
            "/clone/weapon/zhujian" : 4
        ]));
//      set("no_clean_up", 0);
        set("no_fight", 1);

        setup();
}
int valid_leave(object me, string dir)
{
        int i, j;
        object *inv;
        inv = all_inventory(me);
        i = sizeof(inv);
        for (i = 0; i < sizeof(inv); i++)
        {
                if( query("id", inv[i]) == "zhujian")j++;
        }
        if (j > 1)
                return notify_fail("這位" + RANK_D->query_respect(me) + "別那麼貪心，帶走一把竹劍就夠啦。\n");
        return ::valid_leave(me, dir);
}