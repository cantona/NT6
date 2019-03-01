// Room: /guiyun/huating.c
// Date: Nov.18 1998 by Winder

inherit ROOM;

void create()
{
        set("short", "花廳");
        set("long", @LONG
這是一間四方型的廳亭，沒有牌匾，正面兩方木柱，柱上掛了幅缺
了半闕的『詩詞』(poem)。廳內擺設了幾張桌椅。一個丫環正
在抹拭桌面。
LONG );
        set("outdoors", "guiyun");
        set("exits", ([
                "west"  : __DIR__"zoulang8",
                "south" : __DIR__"zoulang7",
        ]));
        set("item_desc", ([
                "poem" :
"
      ┌─┐             ┌─┐
      │兵│             │  │
      │火│             │  │
      │有│             │  │
      │餘│             │  │
      │燼│             │  │
      │貧│             │  │
      │村│             │  │
      │才│             │  │
      │數│             │  │
      │家│             │  │
      └─┘             └─┘
",
        ]));
        set("objects", ([
                __DIR__"npc/xiaolan" : 1,
        ]));
        set("coor/x", 270);
        set("coor/y", -810);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}