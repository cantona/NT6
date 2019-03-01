//Room: xiyuan.c

inherit ROOM;

void create ()
{
        set ("short", "戲院");
        set("long", @LONG
這裡屋深幽暗，屋子西端搭有一座精巧但已有點退色的戲台。戲
台兩邊掛有數盞明亮的燈籠。前幾排有些矮凳，後面是一些紅油茶桌
和寬背扶手椅。這裡以前是古戰場，在地上有個漆黑的洞，裡面傳出陣陣
嚎叫，感覺很詭異，你可以（down）跳下去探查探查。
LONG );
        set("exits", ([
                "south" : "/d/changan/liande-beikou",
                "down" : "/d/migong/shanlu",   
        ]));
        set("objects", ([
                "/d/changan/npc/xizi" : 1,
        ]));

        set("coor/x", -10680);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}