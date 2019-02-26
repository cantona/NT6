inherit ROOM;

void create()
{
        set("short", "牢房");
        set("long", @LONG
這裏漆黑一片，你細細摸索。不久便摸到石門的縫隙，以肩
頭推去，石門竟絕不搖晃，不知有多重實。一個臉色蒼白的年輕
人，垂頭喪氣地坐在地上。
LONG );
        set("no_clean_up", 0);

        set("exits", ([
                "west" : __DIR__"laolang",
        ]));
        set("objects", ([ 
                __DIR__"npc/zhu" : 1,
        ])); 
        setup(); 
        replace_program(ROOM);
}
