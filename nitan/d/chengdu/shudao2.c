inherit ROOM;

void create()
{
        set("short", "青石路" );
        set("long", @LONG
一條青石舖成的路，平坦寬闊，路的兩面。綠樹成蔭，來往的人
累了都到樹下去乘乘涼，歇歇腳，一些小販也乘機在這裡買點吃喝的
東西。從這裡向南看去，隱約可以看見奔騰的長江。
LONG );
        set("exits", ([
                  "east" : __DIR__"shudao1",
                  "southwest" : __DIR__"shudao3",
           ]));

        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("objects", ([
                "/d/beijing/npc/girl2" : 1,
        ]));
        set("coor/x", -160);
        set("coor/y", -170);
        set("coor/z", -60);
        setup();
        replace_program(ROOM);
}