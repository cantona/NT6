inherit ROOM;

void create()
{
        set("short", "茅草屋");
        set("long", @LONG
這是一間簡陋的茅草屋，正對面是一張土炕，炕上只有一床
席子和一個竹枕頭。右面的一個大木架子上擺著近百種各樣的藥
材，滿屋充斥著刺鼻的藥味。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
        "east" : __DIR__"lu2",
]));

        setup();
        replace_program(ROOM);
}
