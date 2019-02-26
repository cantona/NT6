inherit ROOM;

void create()
{
        set("short", "後門");
        set("long", @LONG
這裏是藥王谷的一處后角門，門上掛着一把打鐵鎖好像很久
沒有開動過的樣子，看樣子很少有人來這裏。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"ssl4",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
