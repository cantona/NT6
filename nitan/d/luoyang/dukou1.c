// Room:  /d/luoyang/dukou1.c
// Last modified by winder 2002.11.11
inherit  ROOM;

void  create  ()
{
        set("short", "洛水渡口");
        set("long",  @LONG
這是洛陽城郊的洛水渡口，靜靜的洛水由此向東，匯入滾滾黃河。
碼頭上正泊著一艘烏篷船。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"      : __DIR__"gongshu",
                "northwest" : __DIR__"luopu",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("coor/x", -480);
        set("coor/y", -40);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}