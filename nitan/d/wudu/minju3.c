inherit ROOM;

void create()
{
        set("short", "民居");
        set("long", @LONG
這是一戶普通的農家，屋裡沒有什麼象樣的擺設。牆邊擺放著一
些農具，除此只外四壁皆空，看來並不富裕。 
LONG);

        set("exits", ([
                "south" : __DIR__"cun4",
                "west" : __DIR__"minju8",
        ]));
        set("objects", ([
                __DIR__"npc/cuilan": 1,
        ]));

        setup();
        replace_program(ROOM);
}