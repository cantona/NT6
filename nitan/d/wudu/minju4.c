inherit ROOM;

void create()
{
        set("short", "民居");
        set("long", @LONG
這是一户普通的農家，屋裏沒有什麼象樣的擺設。牆邊擺放着一
些農具，屋正中擺着一張八仙桌，村長正拿着旱煙袋坐在桌邊抽着。 
LONG);

        set("exits", ([
                "south" : __DIR__"cun5",
        ]));
        set("objects", ([
                __DIR__"npc/cunzhang": 1,
        ]));

        setup();
        replace_program(ROOM);
}