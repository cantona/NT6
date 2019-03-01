// mishuchu.c
// By haiyan

inherit ROOM;

void create()
{
        set("short", "報名處");
        set("long", @LONG
這裡是武林大會的報名處。如果你想參加一年一度的武林盛會一
顯身手，奪取武林五絕之名，可以在大會開始時在這裡報名。參加有
獎競猜的江湖人士也可以在這裡購買彩票參加競猜活動。
LONG );
        set("exits", ([
                "north" : "/d/city/wudao1",
        ]));
        set("objects", ([
                "/clone/npc/missyu" : 1,
        ]));
        set("no_fight", 1);
        setup();
        replace_program(ROOM);
}
