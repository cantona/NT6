//Room: piandian.c

inherit ROOM;

void create ()
{
  set ("short", "偏殿");
        set("long", @LONG
偏殿裡氣氛寧靜，靈台高築，依次擺列著八菩薩的佛象。這裡香
火也是不斷，地上舖著一些蒲團。但見南面兩側一動也不動地盤坐著
兩名枯瘦的老僧，左首那僧臉色通紅，左手捏個拈花抉，右手合指朝
天；右首那僧卻臉色青綠，右手捏著拈花抉，左手合指朝天。二僧姿
式一模一樣，卻偏生左右相反。東邊殿門通向大雄寶殿，
LONG );

        set("exits", ([
                "east"    : "/d/changan/baodian",
        ]));

        set("objects", ([
                "/d/changan/npc/jingxuan" : 1,
                "/d/changan/npc/jingming" : 1,
        ]));

        set("coor/x", -10740);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}