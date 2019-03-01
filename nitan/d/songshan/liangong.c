// Room: /d/songshan/liangong.c 練功房
// Last Modified by Winder on Jul. 15 2001

inherit ROOM;

void create()
{
        set("short", "練功房");
        set("long", @LONG
這裡是嵩山派練功房，地下凌亂地放著幾個蒲團，幾位嵩山弟子正
盤膝坐在上面打坐。
LONG );
        set("exits", ([
                "east" : __DIR__"westpath2",
        ]));
        set("no_fight", 1);
        set("no_clean_up", 0);
        set("coor/x", -50);
        set("coor/y", 910);
        set("coor/z", 90);
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