// xiaodao2.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "林間小道");
        set("long", @LONG
這是一條長長的林間小道，從東邊一直通到西邊，一眼望去，看不
到路的盡頭。兩旁百花爭艷。令人留連忘返。南邊好象有香味散發出來，
北邊是個兵器房。
LONG );
        set("exits", ([ /* sizeof() == 4 */
                "south" : __DIR__"shantang",
                "east" : __DIR__"xiaodao1",
                "west" : __DIR__"xiuxis",
                "north" : __DIR__"bingqif",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xiaoyao");
        set("coor/x", 60);
        set("coor/y", -500);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}