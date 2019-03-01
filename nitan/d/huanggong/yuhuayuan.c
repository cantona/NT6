// yuhuayuan.c 御花園

inherit ROOM;

void create()
{
        set("short", "御花園");
        set("long", @LONG
這裡是皇上賞花的御花園. 平日裡皇上時常會來這兒, 和貴妃娘娘
一起賞花品茗. 所以, 這兒是平常太監, 侍衛不能來的. 這裡的宮女多
是心靈手巧, 精通花道的. 放眼四顧, 滿目皆是似錦繁花, 你仔細分辨, 
竟然品目齊全, 大凡你想得的, 甚至你想都不敢想的, 這裡都有了. 你
不禁有些妒嫉起皇帝老兒來.
LONG
);
        set("outdoors", "huanggong");
        set("exits", ([
                "north" : __DIR__"yuhuayuan2",
                "south" : __DIR__"kunningmen",
                "northeast" : __DIR__"fubiting",
                "northwest" : __DIR__"chengruiting",
                "southeast" : __DIR__"wanchunting",
                "southwest" : __DIR__"qianqiuting",
        ]) );
        set("objects", ([
                __DIR__"npc/gongnv" : 2,
                __DIR__"obj/panlonghuai" : 1,
                __DIR__"obj/wolongsong" : 1,
                __DIR__"obj/luohanbai" : 1,
        ]) );
	set("coor/x", -2820);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}