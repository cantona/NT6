inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這是個長廊，通向館主的卧室，這裏靜悄悄的，沒有什麼
人來，走廊兩邊爬滿了爬山虎，外面烈日，可是你走在走廊裏
只覺得一陣清涼。
LONG);
        set("no_fight", 1);
        set("exits", ([
               "south" : __DIR__"guofu_dating",
               "north" : __DIR__"guofu_huayuan",
        ]));
        set("objects", ([
           	__DIR__"npc/yahuan" : 1,
        ]));
        setup();
        replace_program(ROOM);
}