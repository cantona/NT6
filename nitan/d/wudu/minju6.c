inherit ROOM;

void create()
{
        set("short", "民居");
        set("long", @LONG
這是一戶普通的農家，屋裡沒有什麼象樣的擺設。牆邊擺放著一
些農具，除此只外四壁皆空，看來並不富裕。後面似乎有一個小院。 
LONG);

        set("exits", ([
                "northwest" : __DIR__"cun6",
                "south" : __DIR__"minju10",
        ]));
        set("objects", ([
                __DIR__"npc/girl": 1,
        ]));

        setup();
        replace_program(ROOM);
}