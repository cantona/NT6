//  Room:  /d/lanzhou/yangrouguan.c

inherit  ROOM;

void  create  ()
{
        set("short",  "羊肉館");
        set("long",  @LONG
這是蘭州城內最大的羊肉館，賣的全是從城外草原上拉來的剛宰殺
的活羊，又鮮又嫩。南來北往的客商，到此地打尖，無不到這兒來嚐嚐
鮮。更有不少附近寺院的喇嘛到這兒偷腥。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west"  : __DIR__"market",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/xiaoer" : 1,
        ]));
	set("coor/x", -15730);
	set("coor/y", 3810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}