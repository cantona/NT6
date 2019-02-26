// /d/lanzhou/yizhan.c

inherit  ROOM;

void  create  ()
{
        set  ("short",  "驛站");
        set  ("long",  @LONG
這裏是蘭州驛站。由於各個城市進出蘭州的物資傳送都要通過這裏，
因此驛站里人羣進進出出，一片忙碌的景象。站前豎着一溜石樁，綁着
一些驛馬和大車，幾個車伕正在四處招攬生意。
LONG);
        set("exits",  ([  //sizeof()  ==  4
                "east"  :  __DIR__"road1",
        ]));
        set("objects", ([
                "/clone/horse/zaohongma": 1,
                "/clone/horse/huangbiaoma": 1,
                "/clone/horse/ziliuma": 1,
        ]));

        set("no_clean_up",  0);
	set("coor/x", -15760);
	set("coor/y", 3780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}