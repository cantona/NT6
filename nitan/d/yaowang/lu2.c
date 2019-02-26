inherit ROOM;

void create()
{
        set("short", "石子小路");
        set("long", @LONG
這是一條用小石子鋪成的小路，路邊開着讓人叫不上名字的
小紫花。東面是一片苗圃，隨風吹來陣陣奇怪的味道，西面不遠
是一所小茅草屋。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "west" : __DIR__"maowu",
  "east" : __DIR__"yaopu1",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
