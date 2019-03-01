// bingqif.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "打鐵屋");
        set("long", @LONG
這裏是樹林深處的一間小石屋，看來是打造兵器的，屋子中有個大
火爐好燙的呢，屋中還有一張石几，上面擺放着一些早就已經打造好的
兵器。
LONG );
        set("exits", ([
                "south" : __DIR__"xiaodao2",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
               __DIR__"obj/blade": 2,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", 60);
        set("coor/y", -490);
        set("coor/z", 0);
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
                if( query("id", inv[i]) == "blade")j++;
        }
        if (j > 1)
                return notify_fail("這位" + RANK_D->query_respect(me) + "別那麼貪心，帶走一口鋼刀就夠啦。\n");
        return ::valid_leave(me, dir);
}