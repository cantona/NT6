// yuhuayuan2.c 御花園

inherit ROOM;

void create()
{
        set("short", "御花園");
        set("long", @LONG
這裏是皇上賞花的御花園. 平日裏皇上時常會來這兒, 和貴妃娘娘
一起賞花品茗. 所以, 這兒是平常太監, 侍衞不能來的. 這裏的宮女多
是心靈手巧, 精通花道的. 放眼四顧, 滿目皆是似錦繁花, 你仔細分辨, 
竟然品目齊全, 大凡你想得的, 甚至你想都不敢想的, 這裏都有了. 你
不禁有些妒嫉起皇帝老兒來.
LONG
);
        set("outdoors", "huanggong");
        set("exits", ([
                "east"  : __DIR__"yihexuan",
                "north" : __DIR__"qinandian",
                "south" : __DIR__"yuhuayuan",
                "west"  : __DIR__"majuan",
        ]) );
        set("objects", ([
                __DIR__"npc/gongnv" : 1,
                __DIR__"obj/tuofengbai" : 1,
                __DIR__"obj/longzao" : 1,
                __DIR__"obj/zheyinhou" : 1,
        ]) );
	set("coor/x", -2820);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}