// Room: /d/xiangyang/anfupailou.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "安撫府牌樓");
        set("long", @LONG
這裏是安撫使府前的一座牌樓，高達二丈，由黃玉製成，和東面
的將軍府屋頂的琉璃瓦在陽光的照耀下黃白掩映，金碧輝煌，令人目
為之眩，感覺分外巍峨莊嚴。你抬頭望去，但見牌樓上四個大金字『
安撫使府』。牌樓下站着兩派手那刀槍的宋兵，緊緊盯着每一個靠近
這兒的人。北面就是安撫府大院了。南面就是襄陽的中央廣場。
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);

        set("exits", ([
                "south" : __DIR__"guangchang",
                "north" : __DIR__"anfugate",
        ]));
        set("coor/x", -7820);
	set("coor/y", -760);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}