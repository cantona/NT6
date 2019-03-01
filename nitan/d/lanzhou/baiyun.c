//  Room:  /d/lanzhou/baiyun.c

inherit  ROOM;

void  create  ()
{
        set("short",  "白雲觀");
        set("long",  @LONG
一座山門巍然屹立，下開三個拱形大門，氣勢雄偉。門額上鑲磚雕
牌匾，上書藍底金色三個大字------白雲觀。門前兩側左右巨槐掩映，
實為道家修身養性的絕佳去處。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south" : __DIR__"street1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -15740);
	set("coor/y", 3830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}