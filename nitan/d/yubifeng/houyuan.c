// /yubifeng/baozang.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "後院");
        set("long", @long
這是莊主平時練功的地方，在這絕頂寒峯，幾乎寸草不生，只有幾
棵蒼松挺立在那裏。院內有一張石桌和幾張石凳。
long );
        set("exits", ([
                "south" : __DIR__"houting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 6120);
        set("coor/y", 5210);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}