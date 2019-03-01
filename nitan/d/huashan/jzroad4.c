// Room: /d/huashan/jzroad4.c

inherit ROOM;
void create()
{
        set("short", "中條山森林");
        set("long", @LONG
你走在中條山路上。路徑狹小，周圍茂密森林裡，傳來陣陣野獸
夜禽的嘶鳴，聽來讓人毛骨悚然。
LONG );
        set("exits", ([
                "westdown" : __DIR__"jzroad3",
                "southup"  : __DIR__"jzroad5",
        ]));
        set("outdoors", "huashan");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
