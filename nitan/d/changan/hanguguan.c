//  Room:  /d/changan/hanguguan.c

inherit  ROOM;

void  create  ()
{
        set("short",  "函谷關");
        set("long",  @LONG
這裡就是古函古關。它東起崤山，西接潼津，關設谷中。當年強秦
一隅之地，制關東六國而不敢稍動，最後橫掃天下，就是因為它據此，
進可攻，退可守，乃天下形勝之處。老子西出化胡，也是在此留下兩冊
道德經，千載以下，後人仍研讀不盡。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"  :  __DIR__"road1",
                "west"  :  __DIR__"road2",
        ]));
        set("outdoors",  "guanzhong");
        set("no_clean_up", 0);
        set("coor/x", -10610);
	set("coor/y", 1920);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}