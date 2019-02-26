inherit ROOM;

void create()
{
        set("short", "當鋪");
        set("long", @LONG
這是洛陽城裏最大的一家當鋪了，素來以買賣公平着稱。門簾上繡了
個大大的“當“字，使人一目瞭然。當鋪門口橫擺着一個五尺來高的櫃枱，
將當鋪內的一切當了個嚴嚴實實，上面擺着一個牌子 (paizi)。這裏成了
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