inherit ROOM;

void create()
{
        set("short", "墳墓內部");
        set("long", @LONG
你試着繼續往前走，遠處似乎有老鼠吱吱的叫聲，但有不是很真
切。由於光線太暗你只能看到模模糊糊的東西。
LONG );
        set("exits", ([
                "south" : __DIR__"sec2",
                "north" : __DIR__"tomb"
        ]));

        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}