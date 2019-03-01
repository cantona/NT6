// /d/beihai/dukou1.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "渡口");
        set("long", @LONG
這裡是一座渡口，專門負責擺渡遊客去湖中心的瓊島的。渡口是用
結實的木料建造的，還舖上了一層墊子。渡船也是很新的雙層遊船，坐
起來穩穩當當的。兩個船家分別坐在船頭很船尾，隨時準備開船了。
LONG
        );
        set("exits", ([
                "north"     : __DIR__"jiulongbi",
                "southwest" : __DIR__"xiaolu2",
                "northeast" : __DIR__"xitian",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -190);
        set("coor/y", 4080);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}