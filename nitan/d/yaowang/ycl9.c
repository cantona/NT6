inherit ROOM;

void create()
{
        set("short", "羊腸小路");
        set("long", @LONG
這是一條蜿蜒曲折的小路，右面是一小片低矮的樹林，左面
是陡峭的山壁。地上滿是亂石子，有的還很尖利，看樣子這裏很
少有人來。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
  "southeast" : __DIR__"ycl8",
  "north" : __DIR__"houshan",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
