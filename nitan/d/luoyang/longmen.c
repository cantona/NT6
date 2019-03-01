//  Room:  /d/luoyang/longmen.c

inherit  ROOM;

void  create  ()
{
        set("short",  "龍門石窟");
        set("long",  @LONG
這裡就是著名的龍門石窟，凡來洛陽遊玩的遊客比來此觀摩。此處
的石窟造像，密布于兩岸的崖壁上，長達兩華裡。它和敦煌莫高窟、大
同雲崗石窟，合稱我國三大石窟藝術寶庫。此石窟開創于北魏孝文帝遷
都洛陽的公元四百九十三年前後，歷經東、西魏、北齊、隋、唐、北宋
等七個朝代四百多年的大規模營造，使兩邊山窟密如蜂窩。有古陽洞、
賓陽洞、藥方洞、潛溪寺、萬佛洞、奉先寺等多處景點。東香山也是唐
詩人白居易晚年寓居地，琵琶峰下蒼鬆翠柏中有白居易墓。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "eastup"    :  __DIR__"baiyuan",
                "westdown"  :  __DIR__"guandaos4",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6980);
	set("coor/y", 2060);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}