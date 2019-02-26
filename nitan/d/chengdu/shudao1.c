inherit ROOM;

void create()
{
        set("short", "青石路" );
        set("long", @LONG
一條青石鋪成的路，平坦寬闊，路的兩面。綠樹成蔭，來往的人
累了都到樹下去乘乘涼，歇歇腳，一些小販也乘機在這裏買點吃喝的
東西。
LONG );
        set("exits", ([
                "east" : "/d/jingzhou/nanshilu", 
                  "west" : __DIR__"shudao2",
           ]));

        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -150);
        set("coor/y", -170);
        set("coor/z", -60);
        setup();
        replace_program(ROOM);
}
