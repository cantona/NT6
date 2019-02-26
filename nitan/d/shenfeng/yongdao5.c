inherit ROOM;

void create()
{
            set("short", "甬道");
            set("long", @LONG
這裏玉室下密道的一道梯級。下了梯級再走十多丈路，前
面豁然開朗，竟是一大片平地。
LONG);
            set("exits", ([ 
                  "down" : __DIR__"feicui1",
                  "out" : __DIR__"yushi",
        ]));
            setup();
            replace_program(ROOM);
}