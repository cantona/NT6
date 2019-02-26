
inherit ROOM;

void create()
{
        set("short", "石子小路");
        set("long", @LONG
這是一條石子小路蜿蜒在青青的綠草地中，可能是經常有人
走動，路上的石子被磨得非常光亮。前面不遠是是一大片院落，
紅漆大門洞開，裏面影影吵吵的好像有不少人。
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
  "north" : __DIR__"fyuan",
  "south" : __DIR__"dmq",
  "west" : __DIR__"chalu",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
