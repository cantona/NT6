//Room: bridge2.c

inherit ROOM;

void create ()
{
        set ("short", "金水橋");
        set("long", @LONG
金水橋是一條直通皇宮的大石橋，寬敞可容四馬並馳，建造得鬼
斧神工，氣勢磅礡，使人生起一夫當關萬夫莫敵的感覺。橋下有一條
清澈見底、蜿蜒地川流的小河，河水有時撞在石上，發出淙淙的流水
聲，悅耳動聽。橋北通向故皇宮，南面是青龍街。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "south" : "/d/changan/qinglong2",
                "north" : "/d/changan/huanggong",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/yulinjun" : 2,
                "/d/changan/npc/tongling2" : 1,
        ]));

        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}