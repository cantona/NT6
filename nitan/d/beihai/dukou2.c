// /d/beihai/dukou2.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "渡口");
        set("long", @LONG
這裏是一座渡口，專門負責擺渡遊客離開瓊島去湖北面的。渡口是
用結實的木料建造的，還鋪上了一層墊子。渡船也是很新的雙層遊船，
坐起來穩穩當當的。兩個船家分別坐在船頭很船尾，隨時準備開船了。
LONG
        );
        set("exits", ([
                "southwest" : __DIR__"yilan",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -180);
        set("coor/y", 4110);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}