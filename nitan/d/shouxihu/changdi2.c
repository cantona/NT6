// Room: /yangzhou/changdi2.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short", "長堤春柳");
        set("long", @LONG
過虹橋，瘦西湖豁然開闊，西堤遍植楊柳，間以桃花。古有揚州宜
楊之説，傳説是因隋煬帝開運河，河堤植柳，而煬帝賜垂柳姓楊，故楊
柳之稱始於揚州。長堤柳絲拂水，柔情萬種，所謂“多情最是揚州柳”。
堤中臨水建有一亭，隱於柳蔭中。柳叢中點綴紅白桃花。桃紅柳綠，倒
影水中，宛若天境。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "north" : __DIR__"taohuawu",
                "south" : __DIR__"chunliuting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 0);
        set("coor/y", 33);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}