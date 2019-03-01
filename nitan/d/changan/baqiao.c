//  Room:  /d/changan/baqiao.c

inherit  ROOM;

void  create  ()
{
        set("short",  "灞橋");
        set("long",  @LONG
灞橋又叫霸橋，橫跨霸水。“始皇自送至灞上”、“沛公軍霸上”
指的就是這裡。唐人送客多到灞橋，折柳贈別，至此黯然，故又稱“消
魂橋”。春夏之交，翠柳低垂，冬則雪霽風寒，沙明石露，人稱“灞柳
風雪”，列為“關中八景”之一。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west" :  __DIR__"dong-chengmen",
                "east" :  __DIR__"road4",
        ]));
        set("outdoors", "guanzhong");
        set("no_clean_up", 0);
        set("coor/x", -10660);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}