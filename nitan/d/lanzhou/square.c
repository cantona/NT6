//  Room:  /d/lanzhou/square.c

inherit  ROOM;

void  create  ()
{
        set("short",  "城隍廟廣場");
        set("long",  @LONG
西北第一大城，既是西北的經濟中心，也是文化中心。蘭州的文化
集各家豐採，既有傳統的釋、道、儒三家影響，也有回教的投影，比起
京城、揚州，細膩稍有不足，但飛揚之勢卻有過之。
    這裡是城隍廟前的一個廣場。適逢廟會，人群熙熙攘攘。廣場上賣
藝的、算命的、做小買賣的不停的打你錢包主意。東邊是本城的集市，
西邊則通往附近百裡僅有的貢院。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south" : __DIR__"road2",
                "north" : __DIR__"street2",
                "east"  : __DIR__"market",
                "west"  : __DIR__"cuiying",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "lanzhou");
        set("no_clean_up", 0);
	set("coor/x", -15750);
	set("coor/y", 3810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}