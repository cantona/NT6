//  Room:  /d/lanzhou/zhigong.c

inherit  ROOM;

void  create  ()
{
        set("short",  "至公堂");
        set("long",  @LONG
這裏是方圓百里僅有的貢院，為朝廷貢院應試之所。裏面不時傳來
學生們抑揚頓挫的讀書聲。據説本院建於光緒元年，牌匾上“至公堂”
三大個字還是陝甘總督左宗棠親手所題。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"cuiying",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -15760);
	set("coor/y", 3800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}