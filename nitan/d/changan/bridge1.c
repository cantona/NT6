//Room: bridge1.c

inherit ROOM;

void create ()
{
        set ("short", "金水橋");
        set("long", @LONG
金水橋是一條直通皇宮的大石橋，寬敞可容四馬並馳，建造得鬼
斧神工，氣勢磅礴，使人生起一夫當關萬夫莫敵的感覺。橋下有一條
清澈見底、蜿蜒地川流的小河，河水有時撞在石上，發出淙淙的流水
聲，悦耳動聽。橋北通向白虎街，南面是故皇宮。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "south" : "/d/changan/huanggong",
                "north" : "/d/changan/baihu2",
        ]));
        set("objects", 
        ([ //sizeof() == 2
                "/d/changan/npc/yulinjun" : 2,
                "/d/changan/npc/tongling1" : 1,
        ]));

        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1940);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}