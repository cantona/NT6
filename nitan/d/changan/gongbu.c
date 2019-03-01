//Room: gongbu.c

inherit ROOM;

void create ()
{
        set ("short", "工部");
        set("long", @LONG
這裡是毗鄰南安大道的工部工廠集中地區，並沒有行政機構，但
是外地運來的各種珍貴資源都在這裡加工形成上好的用材，然後封存
入庫或是轉運各地。附近的工廠裡面盡是天下的能工巧匠。
LONG );
        set("exits",  ([ //sizeof() == 2
                "west"  : __DIR__"nanan-dadao",
                "north" : __DIR__"gongbu-tong",
                "south" : __DIR__"gongbu-shi",
        ]));

        set("coor/x", -10710);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}