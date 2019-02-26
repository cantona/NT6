inherit ROOM;

void create()
{
        set("short", "民居");
        set("long", @LONG
這是一户普通的農家，屋裏沒有什麼象樣的擺設。牆邊擺放着一
些農具，除此只外四壁皆空，看來並不富裕。 
LONG);

        set("exits", ([
                "north" : __DIR__"cun2",
        ]));
        set("objects", ([
                __DIR__"npc/cunmin": 1,
                __DIR__"npc/cunfu": 1,
        ]));

        setup();
        replace_program(ROOM);
}