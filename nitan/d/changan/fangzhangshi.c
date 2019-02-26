//Room: fangzhangshi.c

inherit ROOM;

void create ()
{
        set ("short", "方丈室");
        set("long", @LONG
方丈室很是樸素，房中除了一個木榻和一個書桌之外，再就別無
他物。書桌上放着幾本關於佛經的書籍，還有一個破舊的木魚。木榻
上疊有幾方棉布薄換。西面通往大雄寶殿。
LONG );
        set("exits", 
        ([ //sizeof() == 1
                "west" : "/d/changan/baodian",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/huitong" : 1,
        ]));
        
        set("coor/x", -10720);
	set("coor/y", 1890);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}