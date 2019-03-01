inherit ROOM;

void create()
{
        set("short", "小溪");
        set("long", @LONG
冰塊閃耀之中，忽見夾雜有花瓣飄流，溪水芳香，當是上
遊有花之故，沿溪水向上遊行去。漸行溪流漸大。沙漠中的河
流大都上遊水大，到下遊水流逐漸被沙漠吸幹，終于消失。但
見溪旁樹木也漸漸多了。
LONG);
        set("outdoors", "gaochang");
        set("exits", ([
                  "north" : __DIR__"lake3",
                  "south" : __DIR__"lake1",
        ]));

        setup();
        replace_program(ROOM);
}