inherit ROOM;

void create()
{
        set("short", "巖洞內");
        set("long", @LONG
這裏是巖洞內部，洞頂上懸掛着潔白的鐘乳石。
LONG );
        set("exits",([
                "out" : __DIR__"cave",
        ]));
        set("objects",([
                "/clone/beast/yanjingshe" : random(2),
                "/clone/beast/wangshe" : random(2),
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50000);
        set("coor/y", 20050);
        set("coor/z", 40);
        setup();
        replace_program(ROOM);
}