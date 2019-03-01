//  Room:  /d/luoyang/wangdayuan.c

inherit  ROOM;

void  create  ()
{
        set("short",  "大院");
        set("long",  @LONG
你走進王家大院，院裡栽著幾叢老梅，枝幹甚是虯勁。院角門內小
庭院內，少不了身在洛陽的標志：幾盆挺名貴的牡丹。院子中停了不少
車馬，每一匹牲口都是鞍轡鮮明。“金刀王家”在洛陽的聲勢果是不凡。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south"  :  __DIR__"wangdatang",
                "west"   :  __DIR__"wangxiaoyuan",
                "out"    :  __DIR__"wanggate",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -7021);
	set("coor/y", 2169);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}