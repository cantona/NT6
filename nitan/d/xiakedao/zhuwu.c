// zhuwu.c

inherit ROOM;

void create()
{
        set("short", "竹屋");
        set("long", @LONG
這是一個用碗口粗大的竹子搭建的屋子，離地不足三尺。有一小
竹梯搭在門口。
LONG );
        set("exits", ([
                "east" : __DIR__"haibin",
                "enter": __DIR__"zhuwu2",
        ]));
        set("outdoors", "nanhai");
        setup();
        replace_program(ROOM);
}