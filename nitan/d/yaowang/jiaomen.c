inherit ROOM;

void create()
{
        set("short", "後門");
        set("long", @LONG
這裡是藥王谷的一處後角門，門上掛著一把打鐵鎖好像很久
沒有開動過的樣子，看樣子很少有人來這裡。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "west" : __DIR__"ssl4",
]));

        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
