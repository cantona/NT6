inherit ROOM;

void create()
{
        set("short", "當舖");
        set("long", @LONG
這是洛陽城裡最大的一家當舖了，素來以買賣公平著稱。門簾上繡了
個大大的“□“字，使人一目了然。當舖門口橫擺著一個五尺來高的櫃台，
將當舖內的一切當了個嚴嚴實實，上面擺著一個牌子 (paizi)。這裡成了
那些手頭不寬裕的人常來的地方。
LONG);
        set("no_clean_up", 0);
        set("no_fight", 1);
        set("exits", ([
                  "down" : __DIR__"cunchu",
                  "east" : __DIR__"sroad1",
        ]));
        set("item_desc", ([
                "paizi" : "公平交易\n
sell        賣 
buy         買
redeem      贖
value       估價
",
        ]));
        set("objects", ([
                __DIR__"npc/qi" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}