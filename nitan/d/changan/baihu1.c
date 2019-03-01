//Room: baihu1.c

inherit ROOM;

void create ()
{
        set ("short", "白虎街");
        set("long", @LONG
白虎街是長安城中心大街，青石板路筆直的伸展出去，一路上行
人比肩，笙歌處處。景物之美，直如神仙境地。西邊是扶風道。北面
則是陰森森的大牢，有幾個獄卒百無聊賴的呆在門口。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "west" : "/d/changan/fufeng1",
                "east" : "/d/changan/baihu2",
        ]));

        set("objects", ([
                "/clone/npc/xunbu" : 2,
        ]));
        set("outdoors", "changan");
        set("no_fight", 1);
        set("coor/x", -10730);
	set("coor/y", 1940);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}