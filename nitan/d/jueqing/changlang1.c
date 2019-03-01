inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這是連接大廳和書房的長廊，雖不見花木，但也能聞到淡
淡的花香。
LONG);
        set("exits", ([
               "east" : __DIR__"dating",
               "west" : __DIR__"shufang",
        ]));

        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}