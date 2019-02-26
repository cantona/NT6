//Room: kezhan.c

inherit ROOM;

void create ()
{
        set ("short", "悦賓客棧");
        set("long", @LONG
這家客棧長安城裏最大的，最昂貴的客棧，也是花錢的客棧。你
若住在這客棧裏，只要你有足夠的錢，根本用不着走出客棧的門，就
可以獲得一切最好的享受。在這裏，只要你開口，就有人會將長安城
裏最好的菜，最出名的歌妓，最美的女人送到你屋裏來。牆上掛着一
個牌子。
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "north" : "/d/changan/qixiang1",
                "up": "/d/changan/kzsleep",
        ]));
        set("objects", ([ /* sizeof() == 1 */
                "/d/changan/npc/xiaoer" : 1,
        ]));
        set("no_fight", 1);
        set("resource", ([ /* sizeof() == 1 */
        "water" : 1,
        ]));

        set("coor/x", -10750);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if( !query_temp("rent_paid", me) && dir == "up" )
                return notify_fail("店小二滿臉堆笑地擋住了你：對不起，上面是客人的卧房，不是本店的客人，不能上去。\n");
        return ::valid_leave(me, dir);
}