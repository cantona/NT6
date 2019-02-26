inherit ROOM;

void create()
{
        set("short", "小月門");
        set("long", @LONG
這裏是過道的盡頭，東面是紅磚圍牆，正中是一扇小月門，
門口站着兩個小丫環。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "enter" : __DIR__"ssl1",
  "west" : __DIR__"tulu3",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
