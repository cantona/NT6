//Room: dangpu.c

inherit ROOM;

void create ()
{
        set ("short", "蕭記當鋪");
        set("long", @LONG
這是長安城裏最大的一家當鋪了。素來以買賣公平著稱。門口掛
了一塊牌子 (paizi)。一個三尺高的櫃枱擋在你的面前，櫃枱後坐着
掌櫃的馮老闆，見你走了進來，一雙精明的眼睛上上下下打量着你。
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "north" : "/d/changan/qixiang3",
        ]));
        set("item_desc", ([
                "paizi" : "公平交易\n
sell        賣 
buy         買
pawn        當
expiate     贖
value       估價
",
        ]));

        set("objects", ([ /* sizeof() == 1 */
                "/d/changan/npc/wanxi" : 1,
        ]));

        set("no_fight", 1);
        set("coor/x", -10730);
	set("coor/y", 1950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}